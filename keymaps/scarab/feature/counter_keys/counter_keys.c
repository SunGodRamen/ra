#include "counter_keys.h"

static int16_t counter = 1;

static bool incr_is_held = false;
static bool decr_is_held = false;
static bool number_key_pressed = false;

bool process_counter_key(uint16_t keycode, keyrecord_t *record) {
    write_log_format(LOG_LEVEL_INFO, "process_counter_key: keycode = %u, pressed = %s\n", keycode, record->event.pressed ? "true" : "false");

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
        write_log_format(LOG_LEVEL_INFO, "tare_action: Counter reset to %d\n", counter);
        return false;
    }
    return true;
}

bool incr_action(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        incr_is_held = true;
        number_key_pressed = false;
        write_log_format(LOG_LEVEL_INFO, "incr_action: Key pressed");
    } else {
        incr_is_held = false;
        if (!number_key_pressed) {
            counter++;
            write_log_format(LOG_LEVEL_INFO, "incr_action: Counter incremented to %d\n", counter);
        }
        write_log_format(LOG_LEVEL_INFO, "incr_action: Key released");
    }
    return true;
}

bool decr_action(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        decr_is_held = true;
        number_key_pressed = false;
        write_log_format(LOG_LEVEL_INFO, "decr_action: Key pressed\n");
    } else {
        decr_is_held = false;
        if (!number_key_pressed) {
            counter--;
            write_log_format(LOG_LEVEL_INFO, "decr_action: Counter decremented to %d\n", counter);
        }
        write_log_format(LOG_LEVEL_INFO, "decr_action: Key released\n");
    }
    return true;
}

bool valu_action(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        send_integer_as_keycodes(counter);
        write_log_format(LOG_LEVEL_INFO, "valu_action: Sent counter value %d\n", counter);
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
        write_log_format(LOG_LEVEL_INFO, "incr_action with number key: Counter incremented to %d\n", counter);
        return false;
    } else if (decr_is_held) {
        counter -= number_value;
        number_key_pressed = true;
        write_log_format(LOG_LEVEL_INFO, "decr_action with number key: Counter decremented to %d\n", counter);
        return false;
    }

    return true;
}
