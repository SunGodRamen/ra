// counter_keys.h
#ifndef COUNTER_KEYS_H
#define COUNTER_KEYS_H
#pragma once

#include QMK_KEYBOARD_H

// Add the following function declarations
bool tare_action(uint16_t keycode, keyrecord_t *record, void *data);
bool incr_action(uint16_t keycode, keyrecord_t *record, void *data);
bool decr_action(uint16_t keycode, keyrecord_t *record, void *data);
bool valu_action(uint16_t keycode, keyrecord_t *record, void *data);

bool handle_number_key_tap(uint16_t keycode, keyrecord_t *record);

#endif // COUNTER_KEYS_H
