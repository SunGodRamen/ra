//feature_manager.h
#pragma once

#include "quantum.h"

enum custom_keycodes {
    KC_CUSTOM = SAFE_RANGE,

    X_INCR,
    X_TARE,
    X_DECR,
    X_VALU,

    T_MODE,
    T_STRT,
    T_STOP,
    T_LAP,
    T_RST,
    T_KEYSET,

    T_FLOW,

    M_DOT,
    M_DASH,

    M_FWRD,
    M_BACK,

    CUSTOM_END_RANGE
};

typedef bool (*custom_key_fn_t)(uint16_t keycode, keyrecord_t *record, void *data);

typedef struct {
    uint16_t keycode;
    custom_key_fn_t fn;
    void *data;
} custom_key_t;

bool process_custom_keys(uint16_t keycode, keyrecord_t *record);

void process_custom_matrix_scan(void);
void process_keyboard_init(void);
