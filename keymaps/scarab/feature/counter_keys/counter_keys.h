// counter_keys.h
#ifndef COUNTER_KEYS_H
#define COUNTER_KEYS_H
#pragma once

#include "../feature_key.h"

#include "../keymap_ascii/keymap_ascii.h"
#include "../log/log.h"

#include "quantum.h"

// works for now, need a better way to do this
// dont know the safe range if more than one feature is used
enum counter_keycodes {
    X_TARE = 0x1000,
    X_INCR,
    X_DECR,
    X_VALU,
};

extern const feature_key_t counter_keys[];

bool process_counter_key(uint16_t keycode, keyrecord_t *record);
bool tare_action(uint16_t keycode, keyrecord_t *record);
bool incr_action(uint16_t keycode, keyrecord_t *record);
bool decr_action(uint16_t keycode, keyrecord_t *record);
bool valu_action(uint16_t keycode, keyrecord_t *record);

bool handle_number_key_tap(uint16_t keycode, keyrecord_t *record);

#endif // COUNTER_KEYS_H
