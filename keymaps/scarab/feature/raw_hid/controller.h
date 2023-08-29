#ifndef SEND_PACKET_H
#define SEND_PACKET_H
#pragma once

#include "quantum.h"
#include "raw_hid.h"
#include "../log/log.h"
#include "stdbool.h"
#include "stdint.h"

void raw_hid_send_user(uint8_t *data, uint8_t length);
void raw_hid_receive_user(uint8_t *data, uint8_t length);
bool process_record_raw_hid(uint16_t keycode, keyrecord_t* record);
void log_raw_hid_message(uint8_t *data, uint8_t length);
void encode_keyrecord(uint8_t *data, uint16_t keycode, keyrecord_t *record);

#endif // SEND_PACKET_H
