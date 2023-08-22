#ifndef RAW_HID_COMMAND_H
#define RAW_HID_COMMAND_H
#pragma once

#include "quantum.h"
#include "raw_hid_message.h"

typedef struct {
    void (*execute)(raw_hid_request *request, raw_hid_response *response);
} raw_hid_command;

raw_hid_command* command_registry[256]; // Using the maximum value of uint8_t for simplicity

#endif // RAW_HID_COMMAND_H
