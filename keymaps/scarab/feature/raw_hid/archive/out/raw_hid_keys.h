#ifndef RAW_HID_KEYS_H
#define RAW_HID_KEYS_H
#pragma once

#include "quantum.h"
// #include "../in/raw_hid_controller.h"
#include "../common/raw_hid_message.h"
// #include "raw_hid_mappings.h"
#include "../../log/log.h"


bool process_record_raw_hid(uint16_t keycode, keyrecord_t *record);
uint32_t check_raw_mod_hold(uint32_t trigger_time, void *cb_arg);
void handle_raw_mode_key(keyrecord_t *record);
bool handle_raw_modified_key(uint16_t keycode, keyrecord_t *record);

#endif // RAW_HID_KEYS_H
