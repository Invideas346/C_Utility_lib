#include <log.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <typedef.h>
#if linux
#include <pthread.h>
#define LOCK_MUTEX()   pthread_mutex_lock(&logger.log_mutex)
#define UNLOCK_MUTEX() pthread_mutex_unlock(&logger.log_mutex)
#elif win32
#endif

void log_level_to_string(LOG_LEVEL level, char** out_str)
{
    switch(level) {
        case INFO: {
            const char* log_str = "[INFO]";
            const uint32_t size = strlen(log_str);
            *out_str = malloc(size);
            strncpy(*out_str, log_str, size);
            (*out_str)[size] = 0;
            break;
        }
        case TRACE: {
            const char* log_str = "[TRACE]";
            const uint32_t size = strlen(log_str);
            *out_str = malloc(size);
            strncpy(*out_str, log_str, size);
            (*out_str)[size] = 0;
            break;
        }
        case DEBUG: {
            const char* log_str = "[DEBUG]";
            const uint32_t size = strlen(log_str);
            *out_str = malloc(size);
            strncpy(*out_str, log_str, size);
            (*out_str)[size] = 0;
            break;
        }
        case WARNING: {
            const char* log_str = "[WARNING]";
            const uint32_t size = strlen(log_str);
            *out_str = malloc(size);
            strncpy(*out_str, log_str, size);
            (*out_str)[size] = 0;
            break;
        }
        case ERROR: {
            const char* log_str = "[ERROR]";
            const uint32_t size = strlen(log_str);
            *out_str = malloc(size);
            strncpy(*out_str, log_str, size);
            (*out_str)[size] = 0;
            break;
        }
        default: {
            const char* log_str = "[NOT IMPLEMENTED]";
            const uint32_t size = strlen(log_str);
            *out_str = malloc(size);
            strncpy(*out_str, log_str, size);
            (*out_str)[size] = 0;
            break;
        }
    }
}

typedef struct Logger {
    char* logfile;
    uint8_t enabled;
    uint8_t is_initialized;
#if linux
    pthread_mutex_t log_mutex;
#elif win32
#endif
} Logger;

static Logger logger;

void log_init(const char* logfile)
{
    logger.is_initialized = FALSE;
    if(logfile == NULL) {
        fprintf(stderr, "logfile location is null!");
        return;
    }
    logger.logfile = malloc(strlen(logfile));
    strcpy(logger.logfile, logfile);
    pthread_mutex_init(&logger.log_mutex, NULL);
    logger.is_initialized = TRUE;
    log_enable();
}

void log_deinit(void)
{
    if(!logger.is_initialized) {
        fprintf(stderr, "Logger not yet intialized");
        return;
    }
    LOCK_MUTEX();
    log_disable();
    UNLOCK_MUTEX();
}

void log_enable(void)
{
    if(!logger.is_initialized) {
        fprintf(stderr, "Logger not yet intialized");
        return;
    }
    LOCK_MUTEX();
    logger.enabled = TRUE;
    UNLOCK_MUTEX();
}

void log_disable(void)
{
    if(!logger.is_initialized) {
        fprintf(stderr, "Logger not yet intialized");
        return;
    }
    LOCK_MUTEX();
    logger.enabled = FALSE;
    UNLOCK_MUTEX();
}

void log_msg(const char* msg, LOG_LEVEL level, ...)
{
    if(!logger.is_initialized) {
        fprintf(stderr, "Logger not yet intialized");
        return;
    }
    LOCK_MUTEX();
    char print_msg[256];
    char* level_str;
    log_level_to_string(level, &level_str);
    sprintf(print_msg, "%s - %s\n", level_str, msg);
    va_list list;
    va_start(list, level);
    vfprintf(stderr, print_msg, list);
    FILE* fp = fopen(logger.logfile, "a");
    if(fp == NULL) {
        fprintf(stderr, "Could not open logfile %s", logger.logfile);
        UNLOCK_MUTEX();
        return;
    }
    vfprintf(fp, print_msg, list);
    fclose(fp);

    va_end(list);
    free(level_str);
    UNLOCK_MUTEX();
}

void log_msg_str(String* msg, LOG_LEVEL level, ...)
{
    if(!logger.is_initialized) {
        fprintf(stderr, "Logger not yet intialized");
        return;
    }
    LOCK_MUTEX();
    char print_msg[256];
    char* level_str;
    log_level_to_string(level, &level_str);
    sprintf(print_msg, "%s - %s\n", level_str, msg->value);
    va_list list;
    va_start(list, level);
    vfprintf(stderr, print_msg, list);

    FILE* fp = fopen(logger.logfile, "a");
    if(fp == NULL) {
        fprintf(stderr, "Could not open logfile %s", logger.logfile);
        UNLOCK_MUTEX();
        return;
    }
    vfprintf(fp, print_msg, list);
    fclose(fp);

    va_end(list);
    free(level_str);
    UNLOCK_MUTEX();
}

uint8_t logger_is_enabled(void) { return logger.enabled; }

uint8_t logger_is_initialized(void) { return logger.is_initialized; }