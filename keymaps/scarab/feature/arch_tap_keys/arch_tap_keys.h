#pragma once

#include "quantum.h"
#include "feature/feature_manager.h"

bool macro_iterator_forward(uint16_t keycode, keyrecord_t *record, void *data);
bool macro_iterator_backward(uint16_t keycode, keyrecord_t *record, void *data);
bool track_key_press(uint16_t keycode, keyrecord_t *record);
