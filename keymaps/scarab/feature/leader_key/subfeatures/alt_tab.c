#include "alt_tab.h"

#define ALT_TAB_TIMEOUT 800

static deferred_token alt_tab_token;
bool alt_tabbing = false;

uint32_t alt_tab_timeout_deferred(uint32_t trigger_time, void *cb_arg) {
    (void)trigger_time; // Suppress unused variable warning
    (void)cb_arg;       // Suppress unused variable warning

    if (alt_tabbing) {
        unregister_code(KC_RALT);
        alt_tabbing = false;
        write_log_format(LOG_LEVEL_DEBUG, "alt_tab: timeout\n");
    }
    return 0; // Don't repeat this callback
}

bool leader_record_alt_tab(uint16_t keycode, keyrecord_t *record) {
    if (alt_tabbing) {
        extend_deferred_exec(alt_tab_token, ALT_TAB_TIMEOUT); // Reset the timer

        switch (keycode) {
            case KC_U:
            case KC_N:
                if (record->event.pressed) {
                    tap_code(KC_TAB);
                }
                write_log_format(LOG_LEVEL_DEBUG, "alt_tab\n");
                return false;

            case KC_O:
            case KC_H:
                if (record->event.pressed) {
                    register_code(KC_RSFT);
                    tap_code(KC_TAB);
                    unregister_code(KC_RSFT);
                }
                write_log_format(LOG_LEVEL_DEBUG, "shift,alt_tab\n");
                return false;

            default:
                cancel_deferred_exec(alt_tab_token); // Cancel the callback
                unregister_code(KC_RALT);
                alt_tabbing = false;
                write_log_format(LOG_LEVEL_INFO, "cancel,alt_tab\n");
                return true;
        }
    }
    return true;
}

bool leader_sequence_alt_tab(void) {
    if (leader_sequence_one_key(LD_2, KC_O) || leader_sequence_one_key(LD_2, KC_H)
     || leader_sequence_one_key(LD_2, KC_N) || leader_sequence_one_key(LD_2, KC_U)) {
        if (!alt_tabbing) {
            register_code(KC_RALT);
            alt_tabbing = true;

            // Set a deferred execution to handle the timeout
            alt_tab_token = defer_exec(ALT_TAB_TIMEOUT, alt_tab_timeout_deferred, NULL);
            write_log_format(LOG_LEVEL_DEBUG, "alt_tab: start\n");
        } else {
            // If already alt_tabbing, extend the callback's timer
            extend_deferred_exec(alt_tab_token, ALT_TAB_TIMEOUT);
            write_log_format(LOG_LEVEL_DEBUG, "alt_tab: extend\n");
        }

        if (leader_sequence_one_key(LD_2, KC_U) || leader_sequence_one_key(LD_2, KC_N)) {
            tap_code(KC_TAB);
            write_log_format(LOG_LEVEL_DEBUG, "alt_tab: lead KC_J\n");
        } else if (leader_sequence_one_key(LD_2, KC_O) || leader_sequence_one_key(LD_2, KC_H)) {
            register_code(KC_RSFT);
            tap_code(KC_TAB);
            unregister_code(KC_RSFT);
            write_log_format(LOG_LEVEL_DEBUG, "alt_tab: lead KC_K\n");
        }
        return true;
    }
    return false;
}
