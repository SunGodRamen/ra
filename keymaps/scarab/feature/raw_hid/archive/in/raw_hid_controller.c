#include "raw_hid_core.h"

bool is_raw_hid_response(uint8_t *data, uint8_t length);
void parse_raw_hid_response(uint8_t *data, uint8_t length, raw_hid_response *response);
void parse_raw_hid_request(uint8_t *data, uint8_t length, raw_hid_request *request);

void convert_raw_hid_response_to_byte_array(raw_hid_response response, uint8_t *message, uint8_t *length);
void convert_raw_hid_request_to_byte_array(raw_hid_request request, uint8_t *message, uint8_t *length);
void log_data(uint8_t *data, uint8_t length, uint8_t loglevel, char* message);

void raw_hid_receive(uint8_t *data, uint8_t length) {
    log_data(data, length, LOG_LEVEL_DEBUG, "Received raw hid data: ");
    if (is_raw_hid_response(data, length)) {
        raw_hid_response response;
        parse_raw_hid_response(data, length, &response);
        add_raw_hid_response_to_buffer(response);
    } else {
        raw_hid_request request;
        parse_raw_hid_request(data, length, &request);
        if (!add_raw_hid_request_to_buffer(request)) {
            respond_with_error(request.request_id, "Buffer overflow: too many raw hid requests");
        }
    }
    return;
}

bool is_raw_hid_response(uint8_t *data, uint8_t length) {
    // If the data length is too short to contain a status code, return false.
    if (length < 1) {
        log_event(LOG_LEVEL_ERROR, "Data length is too short to contain a status code");
        return false;
    }

    // Check if the status code exists within the range of response status codes.
    switch (data[1]) {
        case INFO:
        case SUCCESS:
        case CLIENT_ERROR:
        case SERVER_ERROR:
            return true;
        default:
            return false;
    }
}

void parse_raw_hid_response(uint8_t *data, uint8_t length, raw_hid_response *response) {
    response->request_id = data[0];
    response->status_code = data[1];
    memcpy(response->status_message, data + 2, sizeof(response->status_message));
    memcpy(response->body, data + 2 + sizeof(response->status_message), sizeof(response->body));
}

void parse_raw_hid_request(uint8_t *data, uint8_t length, raw_hid_request *request) {
    request->request_id = data[0];
    request->message_code = data[1];
    memcpy(request->headers, data + 2, sizeof(request->headers));
    memcpy(request->uri, data + 2 + sizeof(request->headers), sizeof(request->uri));
    memcpy(request->body, data + 2 + sizeof(request->headers) + sizeof(request->uri), sizeof(request->body));
}

void send_raw_hid_response(raw_hid_response response) {
    uint8_t message[MAX_MESSAGE_LENGTH];
    uint8_t length;
    convert_raw_hid_response_to_byte_array(response, message, &length);
    raw_hid_send(message, length);
    log_data(message, length, LOG_LEVEL_DEBUG, "Sent raw hid response: ");
}

void respond_with_error(uint8_t request_id, char *error_message) {
    raw_hid_response response;
    response.request_id = request_id;
    response.status_code = SERVER_ERROR;
    memcpy(response.status_message, error_message, sizeof(response.status_message));
    send_raw_hid_response(response);
}

void send_raw_hid_request(raw_hid_request request) {
    uint8_t message[MAX_MESSAGE_LENGTH];
    uint8_t length;
    convert_raw_hid_request_to_byte_array(request, message, &length);
    raw_hid_send(message, length);
    log_data(message, length, LOG_LEVEL_DEBUG, "Sent raw hid request: ");
}

void convert_raw_hid_response_to_byte_array(raw_hid_response response, uint8_t *message, uint8_t *length) {
    memset(message, 0, MAX_MESSAGE_LENGTH);

    *message = response.status_code;
    memcpy(message + 1, response.status_message, sizeof(response.status_message));
    memcpy(message + 1 + sizeof(response.status_message), response.body, sizeof(response.body));

    *length = 1 + sizeof(response.status_message) + sizeof(response.body);
}

void convert_raw_hid_request_to_byte_array(raw_hid_request request, uint8_t *message, uint8_t *length) {
    memset(message, 0, MAX_MESSAGE_LENGTH);

    *message = request.message_code;
    memcpy(message + 1, request.headers, sizeof(request.headers));
    memcpy(message + 1 + sizeof(request.headers), request.uri, sizeof(request.uri));
    memcpy(message + 1 + sizeof(request.headers) + sizeof(request.uri), request.body, sizeof(request.body));

    *length = 1 + sizeof(request.headers) + sizeof(request.uri) + sizeof(request.body);
}

void log_data(uint8_t *data, uint8_t length, uint8_t loglevel, char* message) {
    log_event(loglevel, message);
    for (uint8_t i = 0; i < length; i++) {
        log_int(loglevel, data[i]);
        log_string(loglevel, i < length - 1 ? ", " : "\n");
    }
}
