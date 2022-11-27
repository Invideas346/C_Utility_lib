#ifndef __LOG_H__
#define __LOG_H__

#include <stdarg.h>
#include "string_struct.h"

#define LOG_DEFAULT_LOGFILE "logfile.txt"

/**
 * @brief This enum represents all available log levels.
 */
typedef enum LOG_LEVEL {
    INFO = 0,
    TRACE = 1,
    DEBUG = 2,
    WARNING = 3,
    ERROR = 4
} LOG_LEVEL;

/**
 * @brief Returns a string representation of the passed in log level.
 * This function is used in the log_msg and log_msg_str function.
 *
 * @param level
 * @param out_str
 */
void log_level_to_string(LOG_LEVEL level, char** out_str);

/**
 * @brief Initializes a isoleted instance of the logger struct in the file log.c.
 *
 * @param logfile
 */
void log_init(const char* logfile);
/**
 * @brief Deinitializes the isoleted instance of the logger struct in the file log.c.
 * To reuse the logger it has to be initialized once again.
 */
void log_deinit(void);

/**
 * @brief Enables the logger. This feature can be used to enable the logger at runtime.
 */
void log_enable(void);
/**
 * @brief Disables the logger. This feature can be used to disable the logger at runtime.
 */
void log_disable(void);

/**
 * @brief Logs a message to the terminal and also writes to the spcified logfile.
 * The logfile is specified when the logger gets initialized.
 *
 * @param msg
 * @param level
 * @param ...
 */
void log_msg(const char* msg, LOG_LEVEL level, ...);
/**
 * @brief Logs a message to the terminal and also writes to the spcified logfile.
 * The logfile is specified when the logger gets initialized.
 *
 * @param msg
 * @param level
 * @param ...
 */
void log_msg_str(String* msg, LOG_LEVEL level, ...);

/**
 * @brief Checks whether the logger is active.
 *
 * @return uint8_t
 */
uint8_t logger_is_enabled(void);

/**
 * @brief Checks whether the logger is initialized.
 *
 * @return uint8_t
 */
uint8_t logger_is_initialized(void);

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

#define LOG_IS_ENABLED()     (void*) 0
#define LOG_IS_INITIALIZED() (void*) 0
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

#define LOG_IS_ENABLED()     logger_is_enabled()
#define LOG_IS_INITIALIZED() logger_is_initialized()
#endif

#endif  //__LOG_H__