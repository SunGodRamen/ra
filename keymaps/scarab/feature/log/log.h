#ifndef LOG_H
#define LOG_H

#include "quantum.h"
#include <stdarg.h>
#include <stdio.h>
#include "eeprom.h"
#include "print.h"

#define BUFFER_SIZE 256

typedef enum {
    LOG_LEVEL_ERROR,   // Lowest value, logs only errors
    LOG_LEVEL_INFO,    // Logs informational messages and errors
    LOG_LEVEL_DEBUG    // Highest value, most verbose logging level
} log_level_t;

void log_init(void);
void set_log_level(log_level_t level);

void write_log_format(log_level_t level, const char* format, ...);

#endif // LOG_H
