# Timer Keys

Timer Keys is a custom feature for QMK firmware that provides timer functionality for your keyboard. It allows you to start, stop, reset, and display a timer on your keyboard. Additionally, it offers a key repeat feature based on a timer.

## Features

- Timer mode for starting, stopping, and resetting a timer
- Display the timer in MM:SS format
- Key repeat feature based on a timer
- Customizable keycodes for timer control

## Usage

To use Timer Keys, include the `timer_keys.c` and `timer_keys.h` files in your keymap folder or a shared feature folder. Add the required code snippets to your keymap, rules.mk, and config.h files.

### Keymap

Include the Timer Keys header file and define the custom keycodes for the timer control keys in your keymap.c file.

```c
#include "timer_keys.h"

enum custom_keycodes {
    // ... (other custom keycodes)
    T_MODE,
    T_STRT,
    T_STOP,
    T_LAP,
    T_RST,
    T_KEYSET,
};

Define the Timer Keys action functions in the custom_timer_keys array and set the NUM_CUSTOM_TIMER_KEYS variable.

const custom_timer_key_t custom_timer_keys[] = {
    {T_MODE, t_mode_action},
    {T_STRT, t_start_action},
    {T_STOP, t_stop_action},
    {T_LAP,  t_lap_action},
    {T_RST,  t_reset_action},
    {T_KEYSET, t_keyset_action},
};
uint8_t NUM_CUSTOM_TIMER_KEYS = sizeof(custom_timer_keys) / sizeof(custom_timer_key_t);

Call the process_timer_keys function in the process_record_user function.

bool process_record_user(uint16_t keycode, keyrecord_t* record) {

#ifdef PROCESS_TIMER_KEYS
    if (!process_timer_keys(keycode, record)) {
        return false;
    }
#endif

    return true;
}

Call the process_timer_scan function in the matrix_scan_user function.

void matrix_scan_user(void) {

#ifdef PROCESS_TIMER_KEYS
    process_timer_scan();
#endif
}

### Rules.mk
Add the timer_keys.c file to the SRC variable in your rules.mk file.

SRC += timer_keys.c

### Config.h
Define PROCESS_TIMER_KEYS in your config.h file.

#pragma once
#define PROCESS_TIMER_KEYS

## Customization
You can customize the timer keys and their actions by modifying the custom_timer_keys array and the associated action functions in timer_keys.c.

To change the timer and display update intervals, modify the timer_interval and display_interval variables in timer_keys.c.

## License
This project is released under the terms of the MIT License. See the LICENSE file for more information.

