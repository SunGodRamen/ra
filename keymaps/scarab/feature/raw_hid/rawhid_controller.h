#ifndef RAWHID_CONTROLLER_H
#define RAWHID_CONTROLLER_H
#pragma once

#include "quantum.h"
#include "raw_hid.h"
#include "message_protocol.h"
#include "request_uri.h"
#include "../../aliases.h"
#include "../log/log.h"
#include "stdbool.h"
#include "stdint.h"

typedef void (*raw_hid_receive_callback_t)(uint8_t *data, uint8_t length);

extern raw_hid_receive_callback_t raw_hid_receive_callback;
void set_raw_hid_receive_callback(raw_hid_receive_callback_t new_callback);

void raw_hid_receive_wrapper(uint8_t *data, uint8_t length);
void raw_hid_send_wrapper(uint8_t *data, uint8_t length);
bool process_record_raw_hid(uint16_t keycode, keyrecord_t* record);
void log_raw_hid_message(uint8_t *data, uint8_t length);
void encode_keyrecord(uint8_t *data, uint16_t keycode, keyrecord_t *record);

#endif // RAWHID_CONTROLLER_H
