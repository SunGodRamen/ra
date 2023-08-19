#include "custom_raw_hid.h"

void raw_hid_receive(uint8_t *data, uint8_t length) {
    log_data(data, length, "Received raw hid data: ");
    uint8_t response = PASS;
    send_raw_hid_message(STATUS, 0x00, &response, 1);
}

void send_raw_hid_message(uint8_t message_code, uint8_t sub_code, uint8_t *data, uint8_t length) {
    HIDMessage message;
    message.message_code = message_code;
    message.command_code = sub_code;
    for (uint8_t i = 0; i < length && i < 62; i++) {
        message.data[i] = data[i];
    }
    raw_hid_send_with_log((uint8_t*)&message, length + 2);
}

#define KC_RAW_HID KC_A
bool raw_mode = false;
static deferred_token raw_mod_token;

bool process_record_raw_hid(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_RAW_HID) {
        handle_raw_hid_key(record);
        return false;
    }
    if (raw_mode) {
        if (handle_launch_applications(keycode, record)) {
            return false;
        }
    }
    return true;
}

uint32_t check_raw_mod_hold(uint32_t trigger_time, void *cb_arg) {
    // If this callback is executed, it means RAW_MOD was held for longer than TAPPING_TERM
    raw_mode = true;
    log_event(LOG_LEVEL_INFO, "Entering raw mode");
    return 0;  // Returning 0 to ensure callback doesn't repeat
}

void handle_raw_hid_key(keyrecord_t *record) {
    if (record->event.pressed) {
        raw_mod_token = defer_exec(TAPPING_TERM, check_raw_mod_hold, NULL);
    } else {
        if (raw_mode) {
            raw_mode = false;
            log_event(LOG_LEVEL_INFO, "Exiting raw mode");
        } else {
            if (raw_mod_token != INVALID_DEFERRED_TOKEN) {
                cancel_deferred_exec(raw_mod_token);
                tap_code(KC_RAW_HID);
            }
        }
    }
}

bool handle_launch_applications(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_V:
            if (record->event.pressed) {
                log_event(LOG_LEVEL_DEBUG, "Launching VS Code");
                uint8_t app = VS_CODE;
                send_raw_hid_message(COMMAND, LAUNCH, &app, 1);
                return true;
            }
            break;
        case KC_C:
            if (record->event.pressed) {
                log_event(LOG_LEVEL_DEBUG, "Launching Chrome");
                uint8_t app = CHROME;
                send_raw_hid_message(COMMAND, LAUNCH, &app, 1);
                return true;
            }
            break;
    }
    return false;
}

void raw_hid_send_with_log(uint8_t *message, uint8_t length){
    raw_hid_send(message, length);
    log_data(message, length, "Sent raw hid data: ");
}

void log_data(uint8_t *data, uint8_t length, char* message) {
    log_event(LOG_LEVEL_DEBUG, message);
    for (uint8_t i = 0; i < length; i++) {
        log_int(LOG_LEVEL_DEBUG, data[i]);
        log_string(LOG_LEVEL_DEBUG, ", ");
    }
    log_string(LOG_LEVEL_DEBUG, "\n");
}
