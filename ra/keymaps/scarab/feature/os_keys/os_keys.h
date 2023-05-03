// os_keys.h
#pragma once
#include "quantum.h"
#include "feature/feature_manager.h"
#include "os_detection.h"

typedef void (*custom_os_func_t)(uint16_t keycode, keyrecord_t *record, uint16_t data);

typedef struct {
    uint16_t keycode;
    custom_os_func_t os_function;
    uint16_t data;
    os_variant_t os;
} custom_os_key_t;

extern custom_os_key_t custom_os_keys[];
extern uint8_t NUM_CUSTOM_OS_KEYS;

enum os_keycodes {
    OS_KEY = CUSTOM_END_RANGE,
    OS_END_RANGE
};

bool process_custom_os_keys(uint16_t keycode, keyrecord_t *record);
void swap_key(uint16_t keycode, keyrecord_t *record, uint16_t data);
void swap_control_and_gui_on_windows_and_linux(void);
