# Counter Keys

Counter Keys is a custom feature for QMK firmware that provides a counter functionality for your keyboard. It allows you to increment, decrement, reset (tare), and display the counter value on your keyboard.

## Features

- Counter mode for incrementing, decrementing, and resetting the counter
- Display the counter value as keycodes
- Customizable keycodes for counter control

## Usage

To use Counter Keys, include the `counter_keys.c` and `counter_keys.h` files in your keymap folder or a shared feature folder. Add the required code snippets to your keymap, rules.mk, and config.h files.

### Keymap

Include the Counter Keys header file and define the custom keycodes for the counter control keys in your keymap.c file.

```c
#include "counter_keys.h"

enum custom_keycodes {
    // ... (other custom keycodes)
    X_TARE,
    X_INCR,
    X_DECR,
    X_VALU,
};

Define the Counter Keys action functions in the custom_counter_keys array and set the NUM_CUSTOM_COUNTER_KEYS variable.

const custom_counter_key_t custom_counter_keys[] = {
    {X_TARE, tare_action},
    {X_INCR, incr_action},
    {X_DECR, decr_action},
    {X_VALU, valu_action},
};
uint8_t NUM_CUSTOM_COUNTER_KEYS = sizeof(custom_counter_keys) / sizeof(custom_counter_key_t);

Call the process_counter_keys function in the process_record_user function.

bool process_record_user(uint16_t keycode, keyrecord_t* record) {

#ifdef PROCESS_COUNTER_KEYS
    if (!process_counter_keys(keycode, record)) {
        return false;
    }
#endif

    return true;
}

## Rules.mk
Add the counter_keys.c file to the SRC variable in your rules.mk file.

SRC += counter_keys.c

## Config.h
Define PROCESS_COUNTER_KEYS in your config.h file.

#pragma once
#define PROCESS_COUNTER_KEYS

## Customization
You can customize the counter keys and their actions by modifying the custom_counter_keys array and the associated action functions in counter_keys.c.

## License
This project is released under the terms of the MIT License. See the LICENSE file for more information.
