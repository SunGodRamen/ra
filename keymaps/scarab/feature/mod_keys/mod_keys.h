//mod_keys.h
#ifndef MOD_KEYS_H
#define MOD_KEYS_H

#pragma once
#include "quantum.h"
#include "feature/log/log.h"

typedef struct {
    uint16_t keycode;
    uint16_t mod_keycode;
    uint8_t modifier;
} custom_mod_key_t;

bool process_record_mod_keys(uint16_t keycode, keyrecord_t *record);

#endif
