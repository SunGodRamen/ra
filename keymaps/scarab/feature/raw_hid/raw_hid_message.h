#ifndef RAW_HID_MESSAGE_H
#define RAW_HID_MESSAGE_H
#pragma once

// 64 bytes is the maximum size of a raw HID message
#define MAX_MESSAGE_LENGTH RAW_EPSIZE
typedef struct {
    uint8_t request_id;
    uint8_t message_code;
    uint8_t headers[4];
    uint8_t uri[16];
    uint8_t body[MAX_MESSAGE_LENGTH - 22];
} raw_hid_request;

typedef struct {
    uint8_t request_id;
    uint8_t status_code;
    uint8_t status_message[16];
    uint8_t body[MAX_MESSAGE_LENGTH - 18];
} raw_hid_response;

enum message_codes {
    _GET = 0x20,          // Retrieve data from the host
    _POST = 0x21,         // Create a new record or event on the host
    _PUT = 0x22,          // Update a record on the host
    _PATCH = 0x23,        // Update a record property on the host
    _DELETE = 0x24,       // Delete a record on the host
    _CONNECT = 0x25,      // Establish a connection to the host
};

enum status_codes {
    INFO = 0x11,          // Informational status codes
    SUCCESS = 0x12,       // Success status codes
    CLIENT_ERROR = 0x14,  // Client error status codes
    SERVER_ERROR = 0x15,  // Server error status codes
};

enum header_codes {
    LENGTH = 0x30,        // The length of the body
    CONTENT = 0x31,       // The type of the body
}

enum content_codes {
    BYTE = 0x40,          // A single byte
    STRING = 0x41,        // A string of bytes
    MULTIPART = 0x42,     // A multipart message
}

#endif // RAW_HID_MESSAGE_H
