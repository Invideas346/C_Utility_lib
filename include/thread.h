#ifndef __THREAD_H__
#define __THREAD_H__

#include <typedef.h>

#if linux
#include <sys/types.h>
#include <pthread.h>
#elif win32
#include <windows.h>
#endif

#define INVALD_THREADID (uint32_t) UINT32_MAX

typedef enum THREAD_ERROR_CODE {
    THREAD_OK = 0,
    THREAD_GENERAL_ERROR = 1,
    THREAD_NOT_INTIALIZED = 2 | THREAD_GENERAL_ERROR,
    THREAD_MEMORY_ALLOCATION_ERROR = 3 | THREAD_GENERAL_ERROR,
} THREAD_ERROR_CODE;

typedef struct Thread Thread;

/**
 * @brief This struct represents a thread object which can be pused to create new
 * threads and manage those from the current line-of-execution
 */
typedef struct Thread {
    uint32_t tid;
    uint32_t ptid;
    void* args;
    pthread_mutex_t mutex;
#if linux
    pthread_t thread_handle;
#elif win32
#endif

    void* (*func_ptr)(void* args);

    void (*start)(Thread* thread, THREAD_ERROR_CODE* error_code);
    void (*attach)(Thread* thread, void* (*func)(void*), void* args, THREAD_ERROR_CODE* error_code);
    void (*join)(Thread* thread, THREAD_ERROR_CODE* error_code);
    void (*terminate)(Thread* thread, THREAD_ERROR_CODE* error_code);
    uint8_t (*is_finished)(Thread* thread, THREAD_ERROR_CODE* error_code);

    uint8_t is_initialized;
} Thread;

/**
 * @brief Creates a new thread struct on the heap.
 *
 * @return Thread*
 */
Thread* init_thread_heap(THREAD_ERROR_CODE* error_code);
/**
 * @brief Creates a new thread struct on the heap.
 *
 * @param func_ptr
 * @return Thread*
 */
Thread* init_thread_heap_func(void* (*func_ptr)(void*), THREAD_ERROR_CODE* error_code);
/**
 * @brief Creates a new thread struct on the stack.
 *
 * @return Thread
 */
Thread init_thread_stack();
/**
 * @brief Creates a new thread struct on the stack.
 *
 * @param func_ptr
 * @return Thread*
 */
Thread init_thread_stack_func(void* (*func_ptr)(void*) );

/**
 * @brief This function packs all passed in arguments in order as they were passed in into a array.
 * This is necessary because pthread needs all arguments to be consecutivly stored in memory.
 *
 * @param arg The first argument to be packed
 * @return void*
 */
void* thread_pack_data(void* arg, ...);

#endif  // __THREAD_H__