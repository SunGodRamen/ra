#include "rawhid_controller.h"

// Define constants for message types
#define MSG_TYPE_PING 0x01
#define MSG_TYPE_PONG 0x02
#define MSG_TYPE_KEY_EVENT 0x03

raw_hid_receive_callback_t raw_hid_receive_callback = NULL;
void extract_and_convert_timestamp(uint8_t *data, uint64_t *timestamp);

void set_raw_hid_receive_callback(raw_hid_receive_callback_t new_callback) {
    raw_hid_receive_callback = new_callback;
}

// Handles incoming raw HID messages
void raw_hid_receive(uint8_t *data, uint8_t length) {
    raw_hid_receive_wrapper(data, length);
}

void raw_hid_receive_wrapper(uint8_t *data, uint8_t length) {
    write_log_format(LOG_LEVEL_DEBUG, "Received data: \n");
    log_raw_hid_message(data, length);
    if (length >= 1 && data[0] == MSG_TYPE_PING) {
        // uint8_t pong_data[RAW_EPSIZE] = {0};
        // pong_data[0] = MSG_TYPE_PONG;
        // raw_hid_send_wrapper(pong_data, RAW_EPSIZE);
    }
    uint64_t timestamp;
    extract_and_convert_timestamp(data, &timestamp);
    write_log_format(LOG_LEVEL_DEBUG, "Timestamp: %llu\n", timestamp);
    if (raw_hid_receive_callback != NULL) {
        // Process data and send event type and data to callback
        raw_hid_receive_callback(data, length);
    }
    return;
}

// Sends raw HID messages with logging
void raw_hid_send_wrapper(uint8_t *data, uint8_t length) {
    write_log_format(LOG_LEVEL_DEBUG, "Sending data: \n");
    log_raw_hid_message(data, length);
    raw_hid_send(data, length);
}

// Helper function to send raw HID requests based on URIs
void send_raw_hid_request(uint64_t uri) {
    // Initialize data_buffer with zeros
    uint8_t data_buffer[MESSAGE_SIZE_BYTES] = {0};

    // Encode the request message into the data_buffer
    encode_request(data_buffer, uri);

    // Send the data_buffer through the raw HID interface
    raw_hid_send_wrapper(data_buffer, MESSAGE_SIZE_BYTES);  // Assuming RAW_EPSIZE is equal to MESSAGE_SIZE_BYTES
}

// Processes key events for raw HID communication
bool process_record_raw_hid(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        switch (keycode) {
            case RAW1:
                write_log_format(LOG_LEVEL_DEBUG, "%s\n", "GET_TIMESTAMP");
                send_raw_hid_request(URI_GET_TIME);
                break;
            case RAW2:
                write_log_format(LOG_LEVEL_DEBUG, "%s\n", "GET_RANDOM_NUMBER");
                send_raw_hid_request(URI_GET_RANDOM_NUMBER);
                break;
            case RAW3:
                write_log_format(LOG_LEVEL_DEBUG, "%s\n", "GET_SERVER_NAME");
                send_raw_hid_request(URI_GET_SERVER_NAME);
                break;
            default:
                // write_log_format(LOG_LEVEL_DEBUG, "RAWHID keycode: 0x%04X\n", keycode);
                // uint8_t data[RAW_EPSIZE] = {0};
                // encode_keyrecord(data, keycode, record); // Assuming you have a function to encode the keyrecord
                // raw_hid_send_wrapper(data, RAW_EPSIZE);
                break;
        }
    }
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

// Logs raw HID messages
void log_raw_hid_message(uint8_t *data, uint8_t length) {
    char buffer[length * 3 + 1];  // Each byte becomes "XX ", and one more for '\0'
    for (int i = 0; i < length; i++) {
        snprintf(&buffer[i * 3], 4, "%02X ", data[i]);  // Writes 3 characters at a time, plus null-terminator
    }
    write_log_format(LOG_LEVEL_DEBUG, "%s\n", buffer);
}

void extract_and_convert_timestamp(uint8_t *data, uint64_t *timestamp) {
    write_log_format(LOG_LEVEL_DEBUG, "Inside extract_and_convert_timestamp: Initial value: %llu\n", *timestamp);
    *timestamp = 0;
    for (int i = 15; i >= 8; i--) {
        *timestamp <<= 8;
        *timestamp |= data[i];
    }
    write_log_format(LOG_LEVEL_DEBUG, "Inside extract_and_convert_timestamp: Final value: %llu\n", *timestamp);
}
