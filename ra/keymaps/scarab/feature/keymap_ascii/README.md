# Keymap ASCII

Keymap ASCII is a custom library for QMK firmware that enables you to send ASCII characters, strings, and integers as keycodes. It provides utility functions to convert ASCII characters to QMK keycodes and vice versa.

## Features

- Convert ASCII characters to QMK keycodes
- Convert QMK keycodes to ASCII characters
- Send ASCII characters as keycodes
- Send integers as keycodes
- Send strings as keycodes

## Usage

To use the Keymap ASCII library, include the `keymap_ascii.c` and `keymap_ascii.h` files in your keymap folder or a shared feature folder. Add the required code snippets to your keymap, rules.mk, and config.h files.

### Keymap

Include the Keymap ASCII header file in your keymap.c file.

```c
#include "keymap_ascii.h"

Use the provided utility functions in your keymap to send ASCII characters, strings, or integers as keycodes.

send_ascii_char('A');
send_string_as_keycodes("Hello, world!");
send_integer_as_keycodes(123);

## Rules.mk
Add the keymap_ascii.c file to the SRC variable in your rules.mk file.

SRC += keymap_ascii.c

## Functions
The Keymap ASCII library provides the following utility functions:
char keymap_key_to_ascii(uint16_t keycode, bool shift):
    Converts a QMK keycode to an ASCII character considering the shift state.
void send_ascii_char(char ascii_char):
    Sends an ASCII character as a keycode.
void send_integer_as_keycodes(int16_t integer):
    Sends an integer as a sequence of keycodes.
void send_string_as_keycodes(const char *string):
    Sends a string as a sequence of keycodes.
uint16_t ascii_to_keymap_key(char ascii):
    Converts an ASCII character to a QMK keycode.

## License
This project is released under the terms of the MIT License. See the LICENSE file for more information.
