#include "raw_hid_keys.h"

#define KC_RAW_HID KC_A
bool raw_mode = false;
static deferred_token raw_mod_token;

bool handle_raw_modified_key(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        for (int i = 0; i < sizeof(hidkeyMappings) / sizeof(raw_hid_mapping); i++) {
            if (hidkeyMappings[i].keycode == keycode) {
                log_event(LOG_LEVEL_DEBUG, hidkeyMappings[i].description);
                build_raw_hid_message(hidkeyMappings[i].message, , NULL, 0);
                return true;
            }
        }
    }
    return false;
}

bool process_record_raw_hid(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_RAW_HID) {
        handle_raw_hid_key(record);
        return false;
    }
    if (raw_mode && handle_launch_applications(keycode, record)) {
        return false;
    }
    return true;
}

uint32_t check_raw_mod_hold(uint32_t trigger_time, void *cb_arg) {
    raw_mode = true;
    log_event(LOG_LEVEL_INFO, "Entering raw mode");
    return 0;
}

void handle_raw_mode_key(keyrecord_t *record) {
    if (record->event.pressed) {
        raw_mod_token = defer_exec(TAPPING_TERM, check_raw_mod_hold, NULL);
    } else {
        if (raw_mode) {
            raw_mode = false;
            log_event(LOG_LEVEL_INFO, "Exiting raw mode");
        } else if (raw_mod_token != INVALID_DEFERRED_TOKEN) {
            cancel_deferred_exec(raw_mod_token);
            tap_code(KC_RAW_HID);
        }
    }
}
