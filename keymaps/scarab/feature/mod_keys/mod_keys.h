//mod_keys.h
#pragma once
#include "quantum.h"
#include "action.h"

typedef struct {
    uint16_t keycode;
    uint16_t mod_keycode;
    uint8_t modifier;
} custom_mod_key_t;

void process_custom_shift_keys(uint16_t keycode, keyrecord_t *record, void *data);
void process_custom_option_keys(uint16_t keycode, keyrecord_t *record, void *data);
bool process_custom_mod_keys(uint16_t keycode, keyrecord_t *record);
