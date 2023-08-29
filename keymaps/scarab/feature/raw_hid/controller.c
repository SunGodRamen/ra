#include "controller.h"

// Define constants for message types
#define MSG_TYPE_PING 0x01
#define MSG_TYPE_PONG 0x02
#define MSG_TYPE_KEY_EVENT 0x03

// Function declarations
void log_raw_hid_message(uint8_t *data, uint8_t length);
void encode_keyrecord(uint8_t *data, uint16_t keycode, keyrecord_t *record);

// Handles incoming raw HID messages
void raw_hid_receive(uint8_t *data, uint8_t length) {
    raw_hid_receive_user(data, length);
    return;
}

// Sends raw HID messages with logging
void raw_hid_send_user(uint8_t *data, uint8_t length) {
    log_string(LOG_LEVEL_DEBUG, "Sending data: ");
    log_raw_hid_message(data, length);
    raw_hid_send(data, length);
}

// Processes key events for raw HID communication
bool process_record_raw_hid(uint16_t keycode, keyrecord_t* record) {
    uint8_t data[RAW_EPSIZE] = {0};
    encode_keyrecord(data, keycode, record);
    raw_hid_send_user(data, RAW_EPSIZE);
    return true;
}

// Encodes a key record into a data array
void encode_keyrecord(uint8_t *data, uint16_t keycode, keyrecord_t *record) {
    data[0] = MSG_TYPE_KEY_EVENT;
    data[1] = (uint8_t)(keycode & 0xFF);
    data[2] = (uint8_t)((keycode >> 8) & 0xFF);
    data[3] = record->event.pressed ? 1 : 0;
    data[4] = record->event.key.row;
    data[5] = record->event.key.col;
}

// Handles custom logic for received raw HID messages
void raw_hid_receive_user(uint8_t *data, uint8_t length) {
    log_string(LOG_LEVEL_DEBUG, "Received data: ");
    log_raw_hid_message(data, length);

    if (length >= 1 && data[0] == MSG_TYPE_PING) {
        uint8_t pong_data[RAW_EPSIZE] = {0};
        pong_data[0] = MSG_TYPE_PONG;
        raw_hid_send_user(pong_data, RAW_EPSIZE);
    }
}

// Logs raw HID messages
void log_raw_hid_message(uint8_t *data, uint8_t length) {
    for (int i = 0; i < length; i++) {
        log_int(LOG_LEVEL_DEBUG, data[i]);
        log_string(LOG_LEVEL_DEBUG, " ");
    }
    log_string(LOG_LEVEL_DEBUG, "\n");
}
