#include "raw_hid_manager.h"

uint8_t next_request_id = 0;

void new_raw_hid_request(raw_hid_request request) {
    request.request_id = next_request_id;
    // Store the sent request in the buffer
    add_to_sent_requests(request);
}

void handle_raw_hid_response(raw_hid_response response) {
    raw_hid_request request;
    // get the request context that this response is for
    if(get_sent_request_by_id(response.request_id, &request)) {
        // call function that correlates to the request and response data

    }
}

void handle_raw_hid_request(raw_hid_request request, raw_hid_response *response) {
    raw_hid_command *cmd = command_registry[request.message_code];
    if (cmd) {
        cmd->execute(&request, response);
    } else {
        log_event(LOG_LEVEL_ERROR, "Unknown raw hid message code:");
        log_int(LOG_LEVEL_ERROR, request.message_code);
        response->status_code = CLIENT_ERROR;
    }
    add_to_sent_responses(*response);
}
