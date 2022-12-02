#include <thread.h>
#include <stdlib.h>
#include <log.h>
#include <stdarg.h>

static void* thread_func_wrapper(void* thread)
{
    Thread* t = (Thread*) thread;
#if linux
    t->tid = gettid();
    pthread_mutex_unlock(&t->mutex);
#elif win32
#endif
    LOG_INFO("New thread created with id %d", t->tid);
    void* return_data = t->func_ptr(t->args);
    return return_data;
}

inline static void assign_error_code(THREAD_ERROR_CODE* error_code, THREAD_ERROR_CODE value)
{
    if(error_code != NULL) *error_code = value;
}

static void start(Thread* thread, THREAD_ERROR_CODE* error_code)
{
#if linux
    thread->ptid = getpid();
    pthread_mutex_lock(&thread->mutex);
    int pthread_error_code =
        pthread_create(&thread->thread_handle, NULL, thread_func_wrapper, (void*) thread);
#elif win32
#endif
    assign_error_code(error_code, THREAD_OK);
}
static void attach(Thread* thread, void* (*func)(void*), void** args, THREAD_ERROR_CODE* error_code)
{
}
static void join(Thread* thread, THREAD_ERROR_CODE* error_code)
{
#if linux
    pthread_join(thread->thread_handle, NULL);
#elif win32
#endif
    LOG_INFO("Thread with id %d joined", thread->tid);
}
static void terminate(Thread* thread, THREAD_ERROR_CODE* error_code) {}
static uint8_t is_finished(Thread* thread, THREAD_ERROR_CODE* error_code) {}

static void assign_methods(Thread* thread)
{
    thread->start = start;
    thread->attach = attach;
    thread->join = join;
    thread->terminate = terminate;
    thread->is_finished = is_finished;
}

Thread* init_thread_heap(THREAD_ERROR_CODE* error_code)
{
    Thread* thread = (Thread*) malloc(sizeof(Thread));
    thread->is_initialized = FALSE;
    assign_methods(thread);
    thread->func_ptr = NULL;
    thread->tid = INVALD_THREADID;
    thread->ptid = INVALD_THREADID;
    pthread_mutex_init(&thread->mutex, NULL);
    thread->is_initialized = TRUE;
    return thread;
}
Thread* init_thread_heap_func(void* (*func_ptr)(void**), THREAD_ERROR_CODE* error_code)
{
    Thread* thread = (Thread*) malloc(sizeof(Thread));
    thread->is_initialized = FALSE;
    assign_methods(thread);
    thread->func_ptr = func_ptr;
    thread->tid = INVALD_THREADID;
    thread->ptid = INVALD_THREADID;
    pthread_mutex_init(&thread->mutex, NULL);
    thread->is_initialized = TRUE;
    return thread;
}
Thread init_thread_stack()
{
    Thread thread;
    thread.is_finished = FALSE;
    assign_methods(&thread);
    thread.func_ptr = NULL;
    thread.tid = INVALD_THREADID;
    thread.ptid = INVALD_THREADID;
    pthread_mutex_init(&thread.mutex, NULL);
    thread.is_initialized = TRUE;
    return thread;
}
Thread init_thread_stack_func(void* (*func_ptr)(void**) )
{
    Thread thread;
    thread.is_finished = FALSE;
    assign_methods(&thread);
    thread.func_ptr = func_ptr;
    thread.tid = INVALD_THREADID;
    thread.ptid = INVALD_THREADID;
    pthread_mutex_init(&thread.mutex, NULL);
    thread.is_initialized = TRUE;
    return thread;
}

// TODO: There are multiple ways to solve this issue.
// 1. pass in an array with the size of every argument the size and a pointer onto the data
// 2. pass in an linked list. The linked list struct would have to be adapted to also store the object_size in each node
void** thread_pack_data(uint32_t item_count, void* arg, ...)
{
    void** data = NULL;
    va_list args;
    va_start(args, arg);
    if(arg == NULL) {
        LOG_WARNING("Invalid arguments!");
        return NULL;
    }
    data = malloc(item_count + 1 * sizeof(void*));
    if(data == NULL) {
        LOG_WARNING("Failed to allocate memory for data");
        return NULL;
    }
    data[0] = arg;
    for(uint32_t i = 1; i < item_count + 1; i++) {
        data[i] = va_arg(args, void*);
    }
    va_end(args);
    return data;
}