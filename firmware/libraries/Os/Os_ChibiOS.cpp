
#include"Os.h"
#include"ch.h"


os_task_t * OsCreateTask(void (*pEntryPoint)(void*), void* arg, os_pri_t pri, size_t stack, const char * name)
{
  thread_t * tp;
  tprio_t prio;

  // convert to ChibiOS priority scheme
  prio = (pri-OS_PRI_NORMAL) + NORMALPRIO;

  tp = chThdCreateFromHeap(
      NULL /* default heap */,
      stack,
      prio,
      (tfunc_t) pEntryPoint,
      arg);

  if (name) tp->p_name = name;

  return (void*)tp;
}

bool OsDestroyTask(os_task_t * pTask)
{
  (void)(pTask);
  // why would you want to do that in a real-time system?
  return false;
}

void * OsAlloc(size_t size)
{
  return chHeapAlloc(NULL, size);
}

void OsFree(void * p)
{
  chHeapFree(p);
}

void OsZero(void * p, size_t len)
{
  for (size_t i=0; i<len; i++)
  {
    ((uint8_t*)p)[i] = 0;
  }
}

void OsCopy(void * dst, const void * src, size_t len)
{
  /*
   * TODO: how to do more efficiently,
   * without using unsafe memcpy ?
   */
  for (size_t i=0;i<len; i++)
  {
    ((uint8_t*)dst)[i] = ((uint8_t*)src)[i];
  }
}

#ifdef OS_USE_POOL

struct os_pool_state_t
{
  os_pool_state_t(size_t size, size_t n)
  {
    buf = OsAlloc(size*n);
    pool = new MemoryPool();
    chPoolInit(pool,size,NULL);
    chPoolLoadArray(pool,buf,n);
    free = n;
  }
  size_t size;
  size_t n;
  size_t free;
  MemoryPool * pool;
  void * buf;
};

#define POOL_STATE ((os_pool_state_t*)state)

OsPool::OsPool(size_t size, size_t n)
{
  state = new os_pool_state_t(size,n);
}

void * OsPool::Alloc()
{
  void* obj = chPoolAlloc(POOL_STATE->pool);
  if (obj) POOL_STATE->free--;
  return obj;
}

void OsPool::Free(void * ptr)
{
  POOL_STATE->free++;
  chPoolFree(POOL_STATE->pool,ptr);
}

size_t OsPool::Left()
{
  return POOL_STATE->free;
}

#endif

void OsAssert(bool pred, const char * msg)
{
  (void) msg;
  if (!pred)
  {
    while(1);
  }
}

void OsSleepMs(int ms)
{
  //TODO: ms=0 means yield.
  chThdSleepMilliseconds(ms);
}

//#define ST2MS(n) ((((n) - 1UL) / (CH_FREQUENCY / 1000UL)) + 1UL)

unsigned int OsGetMs() 
{
  return ST2MS(chVTGetSystemTime());
}


/*** Mutual Exclusion ***/
os_lock_t * OsCreateLock()
{
  mutex_t * mtx = (mutex_t*) OsAlloc(sizeof(mutex_t));
  chMtxObjectInit(mtx);
  return (os_lock_t*)mtx;
}
void OsLock(os_lock_t * lock)
{
  chMtxLock((mutex_t*)lock);
  return;
}
void OsUnlock(os_lock_t * lock)
{
  (void)(lock);
  chMtxUnlock((mutex_t*)lock);
  return;
}

void OsSysLock()
{
  chSysLock();
}
void OsSysUnlock()
{
  chSysUnlock();
}



/* OsQueue implementation */


struct os_ch_queue_state
{
  os_ch_queue_state(int len) {
    mbox = new mailbox_t();
    msg_buf = (msg_t*)OsAlloc(sizeof(msg_t)/*32bit*/*len);
    chMBObjectInit(mbox,msg_buf,len);
    this->len = len;
  }
  msg_t * msg_buf;
  mailbox_t * mbox;
  int len;
};

#define Q_STATE ((os_ch_queue_state*)state)

/*** Queues ***/
OsQueue::OsQueue(
    int len, /**< maximum number of items */
    const char * name /**< null-terminated name of queue (up to 8 chars) */
    )
{
  (void) name;
  state = (void*)new os_ch_queue_state(len);
}


/**
 * Enqueue item, blocking if queue full and timeout_ms > 0
 * @retval true if item enqueued successfully
 */
bool OsQueue::Enqueue(
  void * item, /**< pointer to item to enqueue (only pointer is enqueued) */
  int timeout_ms /**< ms to wait if positive. May also be OS_INFINITE or OS_NOWAIT. */
  )
{
  OsAssert(item!=NULL,"OsQueue::Enqueue: Item must be non-null.");
  msg_t r = chMBPost(Q_STATE->mbox,(msg_t)item,
      (timeout_ms==0)?TIME_IMMEDIATE:MS2ST(timeout_ms));
  return (r == MSG_OK);
}

/**
 * Equivalent to Enqueue(item,0)
 */
bool OsQueue::TryEnqueue(
  void * item /**< pointer to item to enqueue */
  )
{
  return Enqueue(item,0);
}

/**
 * Dequeue item, blocking if none available and timeout_ms > 0
 * @return pointer to item or NULL upon timeout
 */
void * OsQueue::Dequeue(
  int timeout_ms /**< ms to wait if positive. May also be OS_INFINITE or OS_NOWAIT. */
  )
{
  msg_t item;
  msg_t r = chMBFetch(Q_STATE->mbox,&item,
      (timeout_ms==0)?TIME_IMMEDIATE:MS2ST(timeout_ms));
  if (r != MSG_OK) 
  {
    return NULL;
  }
  else 
  {
    return (void*)item;
  }
}

void * OsQueue::TryDequeue()
{
  return Dequeue(0);
}

