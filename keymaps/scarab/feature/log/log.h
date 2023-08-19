#ifndef LOG_H
#define LOG_H

#include "quantum.h"
#include "eeprom.h"
#include "print.h"

typedef enum {
    LOG_LEVEL_ERROR,   // Lowest value, logs only errors
    LOG_LEVEL_INFO,    // Logs informational messages and errors
    LOG_LEVEL_DEBUG    // Highest value, most verbose logging level
} log_level_t;

void log_init(void);
void set_log_level(log_level_t level);

void log_key_event(log_level_t level, char *event, uint16_t keycode, keyrecord_t *record);
void log_event(log_level_t level, char *event);
void log_string(log_level_t level, char *string);
void log_int(log_level_t level, int integer);

#endif // LOG_H
