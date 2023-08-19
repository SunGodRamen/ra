// keymap_ascii.h
#ifndef KEYMAP_ASCII_H
#define KEYMAP_ASCII_H
#pragma once

#include "quantum.h"

char keymap_key_to_ascii(uint16_t keycode, bool shift);
uint16_t ascii_to_keymap_key(char ascii);
void send_integer_as_keycodes(int16_t integer);
void send_string_as_keycodes(const char *string);

#endif // KEYMAP_ASCII_H
