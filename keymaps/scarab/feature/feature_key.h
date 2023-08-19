#ifndef FEATURE_KEY_H
#define FEATURE_KEY_H
#pragma once

#include "quantum.h"

// feature keys are structured as a keycode and a function pointer
// the function pointer takes a keycode and a keyrecord and returns a bool
typedef bool (*feature_key_fn_t)(uint16_t keycode, keyrecord_t *record);
typedef struct {
    uint16_t keycode;
    feature_key_fn_t fn;
} feature_key_t;

#endif // FEATURE_KEY_H
