//keymap_ansi.h
#pragma once

#include "quantum.h"

typedef struct {
    uint16_t keycode;
    const char *ansi_escape;
    const char *ansi_escape_shifted;
} keycode_ansi_escape_dict_entry;

typedef struct {
    const char *ansi_escape;
    uint16_t keycode;
    bool shifted;
} ansi_escape_keycode_entry;

const char *keycode_to_escape_sequence(uint16_t keycode, int shift);
uint16_t    escape_sequence_to_keycode(const char *escape_sequence, bool *shift_needed);

