#ifndef RAW_HID_MESSAGE_BUFFER_H
#define RAW_HID_MESSAGE_BUFFER_H
#pragma once

#include "quantum.h"
#include "raw_hid_message.h"
#include "feature/log/log.h"

#define MAX_BUFFERED_REQUESTS_OUT 8
#define MAX_BUFFERED_REQUESTS_IN 8

extern raw_hid_request sent_requests[MAX_BUFFERED_REQUESTS_OUT];
extern uint8_t num_sent_requests;
extern raw_hid_response sent_responses[MAX_BUFFERED_REQUESTS_IN];
extern uint8_t num_sent_responses;

extern raw_hid_response received_responses[MAX_BUFFERED_REQUESTS_OUT];
extern uint8_t num_received_responses;
extern raw_hid_request received_requests[MAX_BUFFERED_REQUESTS_IN];
extern uint8_t num_received_requests;

void add_to_sent_requests(raw_hid_request request);
void add_to_received_requests(raw_hid_request request);
void add_to_sent_responses(raw_hid_response response);
void add_to_received_responses(raw_hid_response response);

bool get_next_received_request(raw_hid_request *request);
bool get_next_received_response(raw_hid_response *response);
bool get_sent_request_by_id(uint8_t request_id, raw_hid_request *request);

#endif // RAW_HID_MESSAGE_BUFFER_H
