
#include"Os.h"
#include<cstdlib>
#include<stdio.h>
#include<cassert>
#include<pthread.h>
#include<unistd.h>
#include<time.h>
#include<queue>


void OsHalt()
{
  assert(false);
}

/***
 * We need to do a little dance here because pthread_create
 *  expects the task function to return a void* but our pEntryPoint is straight void.
 ***/
struct os_task_unix_t
{
  pthread_t t;
  void (*pEntryPoint)(void*);
  void * arg;
};
static void * os_pthread_wrap(void * pthread_arg)
{
  os_task_unix_t * s = (os_task_unix_t*) pthread_arg;
  s->pEntryPoint(s->arg);
  return NULL;
}

os_task_t * OsCreateTask(void (*pEntryPoint)(void*), void* arg, os_pri_t pri, size_t stack, const char * name)
{
  (void) stack;
  (void) name;
  (void) pri;
  int retval;
  os_task_unix_t * s = new os_task_unix_t();
  s->pEntryPoint = pEntryPoint;
  s->arg = arg;
  if ((retval = pthread_create(&s->t,NULL,os_pthread_wrap,s)) != 0)
  {
    printf("ERROR: OsCreateTask: pthread_create failed %d\n",retval);
    return NULL;
  }
  pthread_detach(s->t);
  return (os_task_t*) s;
}

bool OsDestroyTask(os_task_t * pTask)
{
  (void)(pTask);
  // why would you want to do that in a real-time system?
  // WARNING: this doesn't actually stop the thread, just frees mem.
  delete (os_task_unix_t*) pTask;
  return true;
}

void * OsAlloc(size_t size)
{
  return malloc(size);
}

void OsFree(void * p)
{
  free(p);
}

void OsZero(void * p, size_t len)
{
  for (int i=0; i<len; i++)
  {
    ((uint8_t*)p)[i] = 0;
  }
}

void OsCopy(void * dst, const void * src, size_t len)
{
  memcpy(dst,src,len);
}

/**
 * Memory Pool implementation on Unix is
 * simply using heap Alloc/Free.
 * We don't worry about fragmentation
 * like we do on embedded target.
 **/

/*static*/ class os_pool_state_t
{
  public:
  os_pool_state_t(size_t size, size_t n)
  {
    //buf = OsAlloc(size*n);
    //pool = new MemoryPool();
    //chPoolInit(pool,size,NULL);
    //chPoolLoadArray(pool,buf,n);
    //free = n;
    this->size=size;
    this->n=n;
    free = n;
  }
  size_t size;
  size_t n;
  size_t free;
};

#define POOL_STATE ((os_pool_state_t*)state)

OsPool::OsPool(size_t size, size_t n)
{
  state = (void*) new os_pool_state_t(size,n);
}

void * OsPool::Alloc()
{
  return OsAlloc(POOL_STATE->size);
}

void OsPool::Free(void * ptr)
{
  OsFree(ptr);
}

size_t OsPool::Left()
{
  return 1;
}


void OsAssert(bool pred, const char * msg)
{
  if (!pred)
  {
    printf("Failed assertion: %s\n",msg);
    OsHalt();
  }
}

void OsSleepMs(int ms)
{
  usleep(ms*1000);
}

#ifdef CLOCK_UPTIME_PRECISE
// freebsd
#define OS_UNIX_CLOCK_SOURCE  CLOCK_UPTIME_PRECISE
#else
// linux
#define OS_UNIX_CLOCK_SOURCE  CLOCK_MONOTONIC_RAW
#endif

unsigned int OsGetMs() 
{
  static unsigned int starttime = 0;
  struct timespec tp;
  clock_gettime(OS_UNIX_CLOCK_SOURCE,&tp);
  unsigned int ms = tp.tv_nsec/1000000 + tp.tv_sec*1000;
  if (starttime == 0) starttime = ms;
  return ms - starttime;
}


/*** Mutual Exclusion ***/
os_lock_t * OsCreateLock()
{
  pthread_mutex_t * m = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
  int rv = pthread_mutex_init(m,NULL);
  if (rv!=0)
  {
    printf("OsCreateLock Error: %d\n",rv);
    OsFree(m);
    return NULL;
  }
  return (os_lock_t*) m;
}
void OsLock(os_lock_t * lock)
{
  int rv = pthread_mutex_lock((pthread_mutex_t*)lock);
  if (rv!=0)
  {
    printf("OsLock Error: %d\n",rv);
  }
  return;
}
void OsUnlock(os_lock_t * lock)
{
  int rv = pthread_mutex_unlock((pthread_mutex_t*)lock);
  if (rv!=0)
  {
    printf("OsUnlock Error: %d\n",rv);
  }
  return;
}

void OsSysLock()
{
}

void OsSysUnlock()
{
}

struct os_unix_queue_state
{
  os_unix_queue_state(int len) {
    lock = OsCreateLock();
    this->len = len;
  }
  std::queue<void*> q;
  os_lock_t * lock;
  int len;
};

#define Q_STATE ((os_unix_queue_state*)state)

/*** Queues ***/
OsQueue::OsQueue(
    int len, /**< maximum number of items */
    const char * name /**< null-terminated name of queue (up to 8 chars) */
    )
{
  state = (void*)new os_unix_queue_state(len);
}


/**
 * Enqueue item, blocking if queue full and timeout_ms > 0
 * @retval true if item enqueued successfully
 */
bool OsQueue::Enqueue(
  void * item, /**< pointer to item to enqueue */
  int timeout_ms /**< ms to wait if positive. May also be OS_INFINITE or OS_NOWAIT. */
  )
{
  OsAssert(item!=NULL,"OsQueue::Enqueue: Item must be non-null.");

  unsigned int t0 = OsGetMs();
  while (true)
  {
    if (TryEnqueue(item))
    {
      return true;
    }
    /** WARNING: don't use this for anything serious b/c of rollover issue **/
    else if ((OsGetMs() - t0) > timeout_ms)
    {
      return false;
    }
    else
    {
      OsSleepMs(1);
    }
  }
}

/**
 * Equivalent to Enqueue(item,0)
 */
bool OsQueue::TryEnqueue(
  void * item /**< pointer to item to enqueue */
  )
{
  OsAssert(item!=NULL,"OsQueue::Enqueue: Item must be non-null.");

  bool status;
  OsLock(Q_STATE->lock);
  if (Q_STATE->q.size() >= Q_STATE->len)
  {
    status = false;
  }
  else
  {
    Q_STATE->q.push(item);
    status = true;
  }
  OsUnlock(Q_STATE->lock);
  return status;
}

/**
 * Dequeue item, blocking if none available and timeout_ms > 0
 * @return pointer to item or NULL upon timeout
 */
void * OsQueue::Dequeue(
  int timeout_ms /**< ms to wait if positive. May also be OS_INFINITE or OS_NOWAIT. */
  )
{
  unsigned int t0 = OsGetMs();
  void * rv;
  while (true)
  {
    if ((rv=TryDequeue())!=NULL)
    {
      return rv;
    }
    /** WARNING: don't use this for anything serious b/c of rollover issue **/
    else if ((OsGetMs() - t0) > timeout_ms)
    {
      return NULL;
    }
    else
    {
      OsSleepMs(1);
    }
  }
}


void * OsQueue::TryDequeue()
{
  void * rv;
  OsLock(Q_STATE->lock);
  if (Q_STATE->q.size() == 0)
  {
    rv = NULL;
  }
  else
  {
    rv = Q_STATE->q.front();
    Q_STATE->q.pop();
  }
  OsUnlock(Q_STATE->lock);
  return rv;
}

