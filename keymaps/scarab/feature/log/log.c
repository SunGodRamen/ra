#include "log.h"

// EEPROM address to store the log level
#define LOG_LEVEL_EEPROM_ADDR 0

log_level_t current_log_level = LOG_LEVEL_DEBUG;

void set_log_level(log_level_t level) {
    #ifdef CONSOLE_ENABLE
    dprintf("Setting log level to %d\n", level);
    #endif
    current_log_level = level;
    eeprom_update_byte((uint8_t *)LOG_LEVEL_EEPROM_ADDR, level);
}

log_level_t get_log_level(void) {
    return (log_level_t)eeprom_read_byte((uint8_t *)LOG_LEVEL_EEPROM_ADDR);
}

void log_init(void) {
    current_log_level = get_log_level();
}

// Helper function to check the log level
static bool should_log(log_level_t level) {
    #ifdef CONSOLE_ENABLE
    return current_log_level <= level;
    #else
    return false;
    #endif
}

void log_key_event(log_level_t level, char *event, uint16_t keycode, keyrecord_t *record) {
    if (should_log(level)) {
        dprintf("%5u; %s: 0x%04X %s\n", record->event.time, event, keycode, record->event.pressed ? "pressed" : "released");
    }
}

void log_int(log_level_t level, int integer) {
    if (should_log(level)) {
        dprintf("%d", integer);
    }
}

void log_event(log_level_t level, char *event) {
    if (should_log(level)) {
        dprintf("%5u; %s\n", timer_read(), event);
    }
}

void log_string(log_level_t level, char *string) {
    if (should_log(level)) {
        dprintf("%s", string);
    }
}
