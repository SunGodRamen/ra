//counter_keys.c
#include "counter_keys.h"

static int16_t counter = 1;

static bool incr_is_held = false;
static bool decr_is_held = false;
static bool number_key_pressed = false;

bool process_counter_key(uint16_t keycode, keyrecord_t *record){
    log_key_event(LOG_LEVEL_INFO, "process_counter_key", keycode, record);
    switch (keycode) {
        case X_INCR:
            return incr_action(keycode, record);
        case X_TARE:
            return tare_action(keycode, record);
        case X_DECR:
            return decr_action(keycode, record);
        case X_VALU:
            return valu_action(keycode, record);
        case KC_1:
        case KC_2:
        case KC_3:
        case KC_4:
        case KC_5:
        case KC_6:
        case KC_7:
        case KC_8:
        case KC_9:
            return handle_number_key_tap(keycode, record);
        default:
            return true;
    }
}

bool tare_action(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        counter = 1;
        log_event(LOG_LEVEL_INFO, "tare_action");
        return false;
    }
    return true;
}

bool incr_action(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        incr_is_held = true;
        number_key_pressed = false;
        log_event(LOG_LEVEL_INFO, "incr_action.press");
    } else {
        incr_is_held = false;
        if (!number_key_pressed) {
            counter++;
            log_int(LOG_LEVEL_INFO, counter);  // Log the current value of the counter.
            log_event(LOG_LEVEL_INFO, "incr_action.tap");
        }
        log_event(LOG_LEVEL_INFO, "incr_action.release");
    }
    return true;
}

bool decr_action(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        decr_is_held = true;
        number_key_pressed = false;
        log_event(LOG_LEVEL_INFO, "decr_action.press");
    } else {
        decr_is_held = false;
        if (!number_key_pressed) {
            counter--;
            log_int(LOG_LEVEL_INFO, counter);  // Log the current value of the counter.
            log_string(LOG_LEVEL_INFO, "decr_action.tap - counter decremented");
        }
        log_event(LOG_LEVEL_INFO, "decr_action.release");
    }
    return true;
}

bool valu_action(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        send_integer_as_keycodes(counter);
        log_int(LOG_LEVEL_INFO, counter);  // Log the current value of the counter.
        log_event(LOG_LEVEL_INFO, "valu_action - sent counter value");
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
        log_string(LOG_LEVEL_INFO, "incr_action with number key - counter incremented");
        return false;  // Suppress number key output when incr is held
    } else if (decr_is_held) {
        counter -= number_value;
        number_key_pressed = true;
        log_string(LOG_LEVEL_INFO, "decr_action with number key - counter decremented");
        return false;  // Suppress number key output when decr is held
    }

    return true;
}

