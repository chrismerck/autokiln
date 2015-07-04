/*
 * Operating System Abstraction Layer
 * Copyright (c) 2014 Chris Merck
 */

#ifndef __OS_H__
#define __OS_H__

#include<stdint.h>
#include<cstring>

/*** Timeouts ***/
#define OS_INFINITE (-1) /* equiv to chibios TIME_INFINITE */
#define OS_NOWAIT (0)    /* equiv to chibios TIME_IMMEDIATE */

/*** System State ***/
void OsHalt();
void OsAssert(bool pred, const char * msg);

/*** Tasks ***/
enum os_pri_t
{
  OS_PRI_LOWEST,
  OS_PRI_BELOW_NORMAL,
  OS_PRI_NORMAL,
  OS_PRI_ABOVE_NORMAL,
  OS_PRI_HIGHEST, 
};
typedef void os_task_t;
os_task_t* OsCreateTask(void (*pEntryPoint)(void*), void* arg, 
    os_pri_t pri, size_t stack, const char * name);
bool OsDestroyTask(void * os_task_t);

/*** Timer Tasks ***/
void OsTimerInit();
enum os_timer_type_t
{
  OS_TIMER_UNALLOC = 0,
  OS_TIMER_ONESHOT,
  OS_TIMER_PERIODIC,
};
typedef void os_timer_t;
os_timer_t* OsCreateTimer(void (*pEntryPoint)(void*), void* arg,
    os_timer_type_t type, unsigned int period_ms);
void OsDestroyTimer(os_timer_t * timer);

/*** Memory ***/
void * OsAlloc(size_t size);
void OsFree();
void OsZero(void * p, size_t len);
void OsCopy(void * dst, const void * src, size_t len);
class OsPool {
  public:
    /* create a new memory pool */
    OsPool(size_t size, size_t n);
    /* allocate item from pool 
     * returns NULL if pool full
     */
    void * Alloc();
    /* free item into pool */
    void Free(void * ptr);
    /* number of free slots left */
    size_t Left();
  private:
    void * state;
};


/*** Timing ***/
void OsSleepMs(int ms);
unsigned int OsGetMs();

/*** Mutual Exclusion ***/
typedef void os_lock_t;
os_lock_t * OsCreateLock();
void OsLock(os_lock_t * lock);
void OsUnlock(os_lock_t * lock);
void OsSysLock(); 
void OsSysUnlock();

/*** Queues ***/
class OsQueue
{
public:
  OsQueue(
    int len, /**< maximum number of items > 0 */
    const char * name
    );

  /**
   * Enqueue item, blocking if queue full and timeout_ms > 0
   * @retval true if item enqueued successfully
   */
  bool Enqueue(
    void * item, /**< pointer to item to enqueue */
    int timeout_ms /**< ms to wait if positive. May also be OS_INFINITE or OS_NOWAIT. */
    );

  bool TryEnqueue(void*item);

  /**
   * Dequeue item, blocking if none available and timeout_ms > 0
   * @return pointer to item or NULL upon timeout
   */
  void * Dequeue(
    int timeout_ms /**< ms to wait if positive. May also be OS_INFINITE or OS_NOWAIT. */
    );

  void * TryDequeue();

private:

  /** for hiding platform-specific implementation */
  void * state;
};

#endif // __OS_H__
