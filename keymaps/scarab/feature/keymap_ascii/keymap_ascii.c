// keymap_ascii.c
#include "keymap_ascii.h"

static const uint16_t ascii_keycodes[] = {
    // Keycodes for ASCII symbols from ' ' (32) to '~' (126)
    KC_SPACE, KC_1, KC_QUOTE, KC_3, KC_4, KC_5, KC_7, KC_QUOTE,
    KC_9, KC_0, KC_8, KC_EQUAL, KC_COMMA, KC_MINUS, KC_DOT, KC_SLASH,
    KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_SEMICOLON, KC_EQUAL,
    KC_COMMA, KC_MINUS, KC_DOT, KC_SLASH, KC_2, KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G,
    KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S, KC_T, KC_U,
    KC_V, KC_W, KC_X, KC_Y, KC_Z, KC_LEFT_BRACKET, KC_BACKSLASH, KC_RIGHT_BRACKET, KC_6, KC_MINUS, KC_GRAVE,
    // New keycodes for navigation and editing keys starting from 128
    KC_LEFT, KC_RIGHT, KC_BSPC, KC_DEL
};

char keymap_key_to_ascii(uint16_t keycode, bool shift) {
    if (keycode >= KC_A && keycode <= KC_Z) {
        return (shift ? 'A' : 'a') + (keycode - KC_A);
    }

    if (keycode >= KC_1 && keycode <= KC_0) {
        if (shift) {
            static const char shift_nums[] = "!@#$%^&*()";
            return shift_nums[(keycode - KC_1 + 1) % 10];
        } else {
            return '0' + ((keycode - KC_1 + 1) % 10);
        }
    }


    switch (keycode) {
        case KC_SPACE:      return '\t';
        case KC_TAB:        return '\t';
        case KC_DOT:        return shift ? '>' : '.';
        case KC_COMMA:      return shift ? '<' : ',';
        case KC_SLASH:      return shift ? '?' : '/';
        case KC_SEMICOLON:  return shift ? ':' : ';';
        case KC_QUOTE:      return shift ? '"' : '\'';
        case KC_GRAVE:      return shift ? '~' : '`';
        case KC_MINUS:      return shift ? '_' : '-';
        case KC_EQUAL:      return shift ? '+' : '=';
        case KC_LBRC:       return shift ? '{' : '[';
        case KC_RBRC:       return shift ? '}' : ']';
        case KC_LPRN:       return shift ? '(' : '(';
        case KC_RPRN:       return shift ? ')' : ')';
        case KC_BACKSLASH:  return shift ? '|' : '\\';
        case LOPT_T(KC_O):  return shift ? 'O' : 'o';
        case LCMD_T(KC_U):  return shift ? 'U' : 'u';
        case LCTL_T(KC_E):  return shift ? 'E' : 'e';
        case LSFT_T(KC_TAB):      return '\t';
        case LT(1,KC_SPACE):      return ' ';
    }

    return '?';
}

void send_ascii_char(char ascii_char) {
    uint16_t keycode = ascii_to_keymap_key(ascii_char);
    if (keycode != KC_NO) {
        bool shift = (ascii_char != keymap_key_to_ascii(keycode, false));
        if (shift) {
            register_code(KC_LSFT);
        }
        tap_code(keycode);
        if (shift) {
            unregister_code(KC_LSFT);
        }
    }
}


void send_integer_as_keycodes(int16_t integer) {
    if (integer < 0) {
        send_ascii_char('-');
        integer = -integer;
    }
    if (integer == 0) {
        send_ascii_char('0');
        return;
    }
    char buffer[6]; // Maximum 5 digits for int16_t plus null terminator
    uint8_t len = snprintf(buffer, sizeof(buffer), "%d", integer);
    for (uint8_t i = 0; i < len; ++i) {
        send_ascii_char(buffer[i]);
    }
}

void send_string_as_keycodes(const char *string) {
    for (const char *p = string; *p; p++) {
        send_ascii_char(*p);
    }
}

uint16_t ascii_to_keymap_key(char ascii) {
    if (ascii >= 'A' && ascii <= 'Z') {
        return KC_A + (ascii - 'A');
    }

    if (ascii >= 'a' && ascii <= 'z') {
        return KC_A + (ascii - 'a');
    }

    if (ascii >= '1' && ascii <= '9') {
        return KC_1 + (ascii - '1');
    }

    if (ascii == '0') {
        return KC_0;
    }

    if (ascii >= ' ' && ascii <= '~') {
        return ascii_keycodes[ascii - ' '];
    }

        // Handle new ASCII codes for navigation and editing keys
    switch (ascii) {
        case 128: return KC_LEFT;
        case 129: return KC_RIGHT;
        case 130: return KC_BSPC;
        case 131: return KC_DEL;
    }

    return KC_NO; // Indicates an unsupported character
}
