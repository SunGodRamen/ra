//textflow_keys.c
#include "feature/textflow/textflow_keys.h"

// Variables to keep track of interpreter mode and statement
static bool interpreter_mode = false;
static char textflow_buffer[256] = {0};
static uint8_t textflow_buffer_pos = 0;

// Action function for T_FLOW
bool textflow_action(uint16_t keycode, keyrecord_t *record, void *data) {
    if (record->event.pressed) {
      interpreter_mode = !interpreter_mode;

      if (!interpreter_mode) {
        int result = parse_textflow_buffer();
        if (result != INT_MIN) {
            snprintf(textflow_buffer, sizeof(textflow_buffer), "%d\n", result);
            // send_string(textflow_buffer);
        }
        memset(textflow_buffer, 0, sizeof(textflow_buffer));
        textflow_buffer_pos = 0;
      }
    }
    return false;
}

// This function processes the statement input when the interpreter mode is active.
bool handle_statement_input(uint16_t keycode, keyrecord_t *record) {
    // If the interpreter mode is not active, return true
    if (!interpreter_mode) return true;

    if (interpreter_mode && record->event.pressed) {
        if (keycode == KC_BSPC) {
            // Remove the last character from the buffer
            if (textflow_buffer_pos > 0) {
                textflow_buffer_pos--;
                textflow_buffer[textflow_buffer_pos] = '\0';
            }
        } else {
            bool shift_pressed = (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) != 0;
            char c = keymap_key_to_ascii(keycode, shift_pressed);
            if (c != '?' && c && textflow_buffer_pos < sizeof(textflow_buffer) - 1) {
                textflow_buffer[textflow_buffer_pos++] = c;
            }
        }
        return false;
    }

    return true;
}


int parse_textflow_buffer(void) {
    Node *syntax_tree = parse(textflow_buffer);
    print_tree(syntax_tree, 0);

    // Interpret the syntax tree and print the result
    Value result_value = interpret_node(syntax_tree);
    char result_str[32];
    print_value(&result_value, result_str);
    printf("\nResult: %s\n", result_str);

    free_tree(syntax_tree);

    return result_value.number_value;
}


