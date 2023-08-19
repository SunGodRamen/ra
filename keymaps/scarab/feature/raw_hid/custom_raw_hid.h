#ifndef raw_hid_receiver_h
#define raw_hid_receiver_h

#include "quantum.h"
#include "raw_hid.h"

#include "raw_hid_message.h"
#include "feature/log/log.h"

void raw_hid_receive(uint8_t *data, uint8_t length);
void send_raw_hid_message(uint8_t message_code, uint8_t sub_code, uint8_t *data, uint8_t length);
bool process_record_raw_hid(uint16_t keycode, keyrecord_t *record);

uint32_t check_raw_mod_hold(uint32_t trigger_time, void *cb_arg);
void handle_raw_hid_key(keyrecord_t *record);
bool handle_launch_applications(uint16_t keycode, keyrecord_t *record);

void log_data(uint8_t *data, uint8_t length, char* message);
void raw_hid_send_with_log(uint8_t *message, uint8_t length);

#endif
