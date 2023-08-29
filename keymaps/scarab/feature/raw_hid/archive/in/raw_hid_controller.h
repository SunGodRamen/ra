#ifndef RAW_HID_CONTROLLER_H
#define RAW_HID_CONTROLLER_H
#pragma once

#include "quantum.h"
#include "raw_hid.h"

#include <string.h>

#include "raw_hid_message.h"
#include "raw_hid_message_buffer.h"
#include "feature/log/log.h"

void raw_hid_receive(uint8_t *data, uint8_t length);
void send_raw_hid_response(raw_hid_response response);
void send_raw_hid_request(raw_hid_request request);

#endif
