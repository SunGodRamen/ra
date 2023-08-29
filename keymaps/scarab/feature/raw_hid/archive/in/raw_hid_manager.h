#ifndef RAW_HID_MANAGER_H
#define RAW_HID_MANAGER_H
#pragma once

#include "quantum.h"
#include "raw_hid_message.h"
#include "raw_hid_controller.h"
#include "raw_hid_message_buffer.h"
#include "raw_hid_command.h"
#include "../log/log.h"

void new_raw_hid_request(raw_hid_request request);
void handle_raw_hid_response(raw_hid_response response);
void handle_raw_hid_request(raw_hid_request request, raw_hid_response *response);

#endif // RAW_HID_MANAGER_H
