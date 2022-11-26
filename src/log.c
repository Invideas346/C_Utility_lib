#include <log.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <typedef.h>

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
} Logger;

static Logger logger;

void log_init(const char* logfile)
{
    if(logfile == NULL) {
        fprintf(stderr, "logfile location is null!");
        return;
    }
    logger.logfile = malloc(strlen(logfile));
    strcpy(logger.logfile, logfile);
    log_enable();
}

void log_deinit(void) { log_disable(); }

void log_enable(void) { logger.enabled = TRUE; }

void log_disable(void) { logger.enabled = FALSE; }

void log_msg(const char* msg, LOG_LEVEL level, ...)
{
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
        return;
    }
    vfprintf(fp, print_msg, list);
    fclose(fp);

    va_end(list);
    free(level_str);
}

void log_msg_str(String* msg, LOG_LEVEL level, ...)
{
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
        return;
    }
    vfprintf(fp, print_msg, list);
    fclose(fp);

    va_end(list);
    free(level_str);
}