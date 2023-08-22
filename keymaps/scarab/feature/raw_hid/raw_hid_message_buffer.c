#include "raw_hid_message_buffer.h"

// read from the controller
raw_hid_request sent_requests[MAX_BUFFERED_REQUESTS_OUT];
uint8_t num_sent_requests = 0;
raw_hid_response sent_responses[MAX_BUFFERED_REQUESTS_IN];
uint8_t num_sent_responses = 0;

// read from the manager
raw_hid_response received_responses[MAX_BUFFERED_REQUESTS_OUT];
uint8_t num_received_responses = 0;
raw_hid_request received_requests[MAX_BUFFERED_REQUESTS_IN];
uint8_t num_received_requests = 0;

void add_to_sent_requests(raw_hid_request request) {
    if (num_sent_requests >= MAX_BUFFERED_REQUESTS_OUT) {
        log_event(LOG_LEVEL_ERROR, "Buffer overflow: too many sent raw hid requests");
        return;
    }
    sent_requests[num_sent_requests++] = request;
}

void add_to_sent_responses(raw_hid_response response) {
    if (num_sent_responses >= MAX_BUFFERED_REQUESTS_OUT) {
        log_event(LOG_LEVEL_ERROR, "Buffer overflow: too many sent raw hid responses");
        return;
    }
    sent_responses[num_sent_responses++] = response;
}

void add_to_received_responses(raw_hid_response response) {
    if (num_received_responses >= MAX_BUFFERED_REQUESTS_IN) {
        log_event(LOG_LEVEL_ERROR, "Buffer overflow: too many received raw hid responses");
        return;
    }
    received_responses[num_received_responses++] = response;
}

bool add_to_received_requests(raw_hid_request request) {
    if (num_received_requests >= MAX_BUFFERED_REQUESTS_IN) {
        log_event(LOG_LEVEL_ERROR, "Buffer overflow: too many received raw hid requests");
        return false;
    }
    received_requests[num_received_requests++] = request;
    return true;
}

bool get_next_received_request(raw_hid_request *request) {
    if (num_received_requests == 0) {
        return false;  // No request in the buffer
    }
    *request = received_requests[0];

    // Shift the buffer left
    memmove(received_requests, received_requests + 1,
            (MAX_BUFFERED_REQUESTS_IN - 1) * sizeof(raw_hid_request));
    num_received_requests--;
    return true;
}

bool get_next_received_response(raw_hid_response *response) {
    if (num_received_responses == 0) {
        return false;  // No response in the buffer
    }
    *response = received_responses[0];

    // Shift the buffer left
    memmove(received_responses, received_responses + 1,
            (MAX_BUFFERED_REQUESTS_OUT - 1) * sizeof(raw_hid_response));
    num_received_responses--;
    return true;
}

bool get_sent_request_by_id(uint8_t request_id, raw_hid_request *request) {
    for (uint8_t i = 0; i < MAX_BUFFERED_REQUESTS_OUT; i++) {
        if (sent_requests[i].request_id == request_id) {
            *request = sent_requests[i];
            // shift the buffer
            memmove(sent_requests + i, sent_requests + i + 1,
                    (MAX_BUFFERED_REQUESTS_OUT - 1) * sizeof(raw_hid_request));
            return true;
        }
    }
    log_event(LOG_LEVEL_ERROR, "Request ID not found in sent requests buffer");
    return false;
}

