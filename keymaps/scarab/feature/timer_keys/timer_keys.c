#include "timer_keys.h"
#include "quantum.h"
#include "feature/textflow/textflow_common.h"
#include "feature/keymap_ascii/keymap_ascii.h"

// Variables to keep track of timer status
static uint32_t timestamp     = 0;
static bool     timer_running = false;
static bool     timer_mode    = false;

// Timer intervals for updating timer and display
static uint16_t timer_interval = 1000;
uint16_t last_timer_update = 0;
static uint16_t display_interval = 1000;
uint16_t last_display_update = 0;

// New variables for T_KEYSET functionality
static uint16_t repeat_keycode = KC_NO;
static uint32_t repeat_interval = 0;
static bool     repeat_mode = false;
static bool     keyset_listening = false;

// Action functions for each timer key
bool t_mode_action(uint16_t keycode, keyrecord_t *record, void *data) {
    if (record->event.pressed) {
        if (timer_mode) {
            delete_formatted_timestamp();
        }
        timer_mode = !timer_mode;
        if (timer_mode) {
            send_string_as_keycodes(write_formatted_timestamp(timestamp));
        }
    }
    return false;
}

bool t_start_action(uint16_t keycode, keyrecord_t *record, void *data) {
    if (record->event.pressed) {
        timer_running = !timer_running;
    }
    return false;
}

bool t_stop_action(uint16_t keycode, keyrecord_t *record, void *data) {
    if (record->event.pressed) {
        timer_running = false;
    }
    return false;
}

bool t_reset_action(uint16_t keycode, keyrecord_t *record, void *data) {
    if (record->event.pressed) {
        timestamp = 0;
        if (timer_mode) {
            delete_formatted_timestamp();
            send_string_as_keycodes(write_formatted_timestamp(timestamp));
        }
    }
    return false;
}

bool t_lap_action(uint16_t keycode, keyrecord_t *record, void *data) {
    if (record->event.pressed) {
        if (timer_mode) {
            delete_formatted_timestamp();
            send_string_as_keycodes(write_formatted_timestamp(timestamp));
            tap_code(KC_ENT);
            send_string_as_keycodes(write_formatted_timestamp(timestamp));
        } else {
            send_string_as_keycodes(write_formatted_timestamp(timestamp));
        }
    }
    return false;
}

bool t_keyset_action(uint16_t keycode, keyrecord_t *record, void *data) {
    if (record->event.pressed) {
        if (repeat_mode) {
            repeat_mode = false;
            repeat_keycode = KC_NO;
            repeat_interval = 0;
        } else if (keyset_listening) {
            // If already listening for key to repeat, do nothing
        } else {
            timer_mode = true;
            timer_running = true;
            timestamp = 0;
            send_string_as_keycodes(write_formatted_timestamp(timestamp));
            keyset_listening = true;
        }
    }
    return false;
}

void update_timestamp(void) {
    timestamp++;
}

char *write_formatted_timestamp(uint32_t timestamp) {
    uint16_t minutes = timestamp / 60;
    uint16_t seconds = timestamp % 60;

    static char buf[9]; // "MM:SS\0"
    snprintf(buf, sizeof(buf), "%02u:%02u", minutes, seconds);
    return buf;
}

void delete_formatted_timestamp(void) {
    for (int i = 0; i < 5; i++) {
        tap_code(KC_BSPC);
    }
}

void process_timer_scan(void) {
    if (timer_running && timer_elapsed(last_timer_update) > timer_interval) {
        last_timer_update = timer_read();
        update_timestamp();
    }
    if (timer_running && timer_mode && timer_elapsed(last_display_update) > display_interval) {
        last_display_update = timer_read();

        delete_formatted_timestamp();

        // Send the new timestamp string
        send_string_as_keycodes(write_formatted_timestamp(timestamp));
    }

    // Repeat behavior for T_KEYSET
    if (repeat_mode && timer_elapsed(last_display_update) > repeat_interval) {
        last_display_update = timer_read();
        tap_code(repeat_keycode);
    }
}

