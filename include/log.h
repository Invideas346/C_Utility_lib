#ifndef __LOG_H__
#define __LOG_H__

#include <stdarg.h>
#include "string_struct.h"

#define LOG_DEFAULT_LOGFILE "logfile.txt"

typedef enum LOG_LEVEL {
    INFO = 0,
    TRACE = 1,
    DEBUG = 2,
    WARNING = 3,
    ERROR = 4
} LOG_LEVEL;

void log_level_to_string(LOG_LEVEL level, char** out_str);

void log_init(const char* logfile);
void log_deinit(void);

void log_enable(void);
void log_disable(void);

void log_msg(const char* msg, LOG_LEVEL level, ...);
void log_msg_str(String* msg, LOG_LEVEL level, ...);

#ifdef NO_LOG
#define LOG_INIT()   (void*) 0
#define LOG_DEINIT() (void*) 0

#define LOG_ENABLE()  (void*) 0
#define LOG_DISABLE() (void*) 0

#define LOG_INFO(msg, ...)    (void*) 0
#define LOG_TRACE(msg, ...)   (void*) 0
#define LOG_DEBUG(msg, ...)   (void*) 0
#define LOG_WARNING(msg, ...) (void*) 0
#define LOG_ERROR(msg, ...)   (void*) 0

#define LOG_INFO_STR(msg, ...)    (void*) 0
#define LOG_TRACE_STR(msg, ...)   (void*) 0
#define LOG_DEBUG_STR(msg, ...)   (void*) 0
#define LOG_WARNING_STR(msg, ...) (void*) 0
#define LOG_ERROR_STR(msg, ...)   (void*) 0
#else
#define LOG_INIT()   log_init(LOG_DEFAULT_LOGFILE)
#define LOG_DEINIT() log_deinit(void)

#define LOG_ENABLE()  log_enable()
#define LOG_DISABLE() log_disable()

#define LOG_INFO(msg, ...)    log_msg(msg, INFO, ##__VA_ARGS__)
#define LOG_TRACE(msg, ...)   log_msg(msg, TRACE, ##__VA_ARGS__)
#define LOG_DEBUG(msg, ...)   log_msg(msg, DEBUG, ##__VA_ARGS__)
#define LOG_WARNING(msg, ...) log_msg(msg, WARNING, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...)   log_msg(msg, ERROR, ##__VA_ARGS__)

#define LOG_INFO_STR(msg, ...)    log_msg_str(msg, INFO, ##__VA_ARGS__)
#define LOG_TRACE_STR(msg, ...)   log_msg_str(msg, TRACE, ##__VA_ARGS__)
#define LOG_DEBUG_STR(msg, ...)   log_msg_str(msg, DEBUG, ##__VA_ARGS__)
#define LOG_WARNING_STR(msg, ...) log_msg_str(msg, WARNING, ##__VA_ARGS__)
#define LOG_ERROR_STR(msg, ...)   log_msg_str(msg, ERROR, ##__VA_ARGS__)
#endif

#endif  //__LOG_H__