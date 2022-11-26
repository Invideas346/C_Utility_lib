#ifndef __THREAD_H__
#define __THREAD_H__

#if linux
#include <pthread.h>
#elif win32
#include <windows.h>
#endif

/**
 * @brief This struct represents a thread object which can be pused to create new
 * threads and manage those from the current line-of-execution
 */
typedef struct Thread {
    uint32_t pid;
    uint32_t ppid;

    void* func_ptr;
} Thread;

#endif  // __THREAD_H__