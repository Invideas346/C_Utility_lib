#ifndef __THREAD_H__
#define __THREAD_H__

#if linux
#include <pthread.h>
#elif win32
#include <windows.h>
#endif

struct Thread {};

typedef struct Thread Thread;

#endif  // __THREAD_H__
