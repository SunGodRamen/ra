#include "message_protocol.h"

// This function interprets the message type
void interpret_message(const uint8_t* buffer, MessageType* result) {
    uint8_t flags = buffer[0];

    if (flags == 0) {
        *result = REQUEST_MESSAGE;
        return;
    }
    if (flags & 0x01) {
        *result = RESPONSE_MESSAGE;
    }
    else {
        *result = CONFIRM_MESSAGE;
    }
}

// This function encodes common fields into the first 8 bytes
static void encode_common_fields(uint8_t* buffer, uint16_t request_id, uint16_t status_code, uint8_t flags) {
    buffer[0] = flags;
    buffer[1] = (request_id >> 8) & 0xFF;
    buffer[2] = request_id & 0xFF;
    buffer[3] = (status_code >> 8) & 0xFF;
    buffer[4] = status_code & 0xFF;
}

// This function encodes a confirmation message
void encode_confirmation(uint8_t* buffer, uint16_t request_id, uint16_t status_code) {
    encode_common_fields(buffer, request_id, status_code, 0x01);
}

// This function encodes a request message
void encode_request(uint8_t* buffer, uint64_t uri) {
    encode_common_fields(buffer, 0, 0, 0);
    for (int i = 0; i < 8; i++) {
        buffer[8 + i] = (uri >> (i * 8)) & 0xFF;
    }
}

// This function encodes a response message
void encode_response(uint8_t* buffer, uint16_t request_id, uint64_t data) {
    encode_common_fields(buffer, request_id, 0, 0x01);
    for (int i = 0; i < 8; i++) {
        buffer[8 + i] = (data >> (i * 8)) & 0xFF;
    }
}

// This function extracts the URI from a request message
void extract_request_uri(const uint8_t* buffer, uint64_t* uri) {
    *uri = 0;
    for (int i = 0; i < 8; i++) {
        *uri |= ((uint64_t)buffer[8 + i]) << (i * 8);
    }
}

// This function extracts the request_id and data from a response message
void extract_request_id_and_data(const uint8_t* buffer, uint16_t* request_id, uint64_t* data) {
    *request_id = ((uint16_t)buffer[1] << 8) | buffer[2];
    *data = 0;
    for (int i = 0; i < 8; i++) {
        *data |= ((uint64_t)buffer[8 + i]) << (i * 8);
    }
}
