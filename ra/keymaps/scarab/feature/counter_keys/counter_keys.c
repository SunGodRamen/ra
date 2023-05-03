//counter_keys.c
#include "counter_keys.h"
#include "quantum.h"
#include "feature/keymap_ascii/keymap_ascii.h"

static int16_t counter = 1;

static bool incr_is_held = false;
static bool decr_is_held = false;
static bool number_key_pressed = false;

bool tare_action(uint16_t keycode, keyrecord_t *record, void *data) {
    if (record->event.pressed) {
        counter = 1;
        return false;
    }
    return true;
}

bool incr_action(uint16_t keycode, keyrecord_t *record, void *data) {
    if (record->event.pressed) {
        incr_is_held = true;
        number_key_pressed = false;
    } else {
        incr_is_held = false;
        if (!number_key_pressed) {
            counter++;
        }
    }
    return true;
}

bool decr_action(uint16_t keycode, keyrecord_t *record, void *data) {
    if (record->event.pressed) {
        decr_is_held = true;
        number_key_pressed = false;
    } else {
        decr_is_held = false;
        if (!number_key_pressed) {
            counter--;
        }
    }
    return true;
}

bool valu_action(uint16_t keycode, keyrecord_t *record, void *data) {
    if (record->event.pressed) {
        send_integer_as_keycodes(counter);
        return false;
    }
    return true;
}

bool handle_number_key_tap(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    int16_t number_value = keycode - KC_1 + 1;
    if (incr_is_held) {
        counter += number_value;
        number_key_pressed = true;
    } else if (decr_is_held) {
        counter -= number_value;
        number_key_pressed = true;
    } else {
        return true;
    }
    return false;
}
