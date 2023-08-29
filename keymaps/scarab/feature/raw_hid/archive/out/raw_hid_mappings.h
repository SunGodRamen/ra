#ifndef RAW_HID_MAPPINGS_H
#define RAW_HID_MAPPINGS_H
#pragma once

#include "quantum.h"
#include "../common/raw_hid_message.h"

typedef struct {
    uint16_t keycode;
    raw_hid_request message;
    char* description;
} raw_hid_req_mapping;

const raw_hid_mapping hidkeyMappings[] = {
    {KC_V, { _POST, {LENGTH, 0x02, CONTENT, _BYTE}, {APP, TOGGLE}, {VS_CODE}}, "Toggle VS Code"},
    {KC_C, { _POST, {LENGTH, 0x02, CONTENT, _BYTE}, {APP, TOGGLE}, {VS_CODE}}, "Toggle Chrome"},
};

#endif // RAW_HID_MAPPINGS_H
