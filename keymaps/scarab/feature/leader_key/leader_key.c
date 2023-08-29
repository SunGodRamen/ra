#include "leader_key.h"

void leader_end_user(void) {
    #ifdef FEATURE_FLAG_DYNAMIC_MACRO_OVERRIDE
    if (leader_sequence_dynamic_macro()) {
        log_event(LOG_LEVEL_INFO, "leader_sequence_dynamic_macro");
        return;
    }
    #endif

    if (leader_sequence_alt_tab()) {
        log_event(LOG_LEVEL_INFO, "leader_sequence_alt_tab");
        return;
    }

    if (leader_sequence_system()) {
        log_event(LOG_LEVEL_INFO, "leader_sequence_system");
        return;
    }

    if (leader_sequence_app_focus()) {
        log_event(LOG_LEVEL_INFO, "leader_sequence_app_focus");
        return;
    }

    if (leader_sequence_hotkeys()) {
        log_event(LOG_LEVEL_INFO, "leader_sequence_hotkey");
        return;
    }

    // press LSFT or SPACE to cancel
    if (leader_sequence_one_key(LD_1, LS_) || leader_sequence_one_key(LD_2, LS_) || leader_sequence_one_key(LD_3, LS_)
            || leader_sequence_one_key(LD_1, NV_SPC) || leader_sequence_one_key(LD_2, NV_SPC) || leader_sequence_one_key(LD_3, NV_SPC)) {
        log_event(LOG_LEVEL_INFO, "leader_sequence cancel");
        return;
    }

    // if not handled above
    log_event(LOG_LEVEL_INFO, "leader_sequence timeout");
    return;
}

bool process_record_leader(uint16_t keycode, keyrecord_t *record) {
    if (!leader_record_alt_tab(keycode, record)) {
        log_event(LOG_LEVEL_DEBUG, "leader_record_alt_tab");
        return false;
    }
    return true;
}

static deferred_token alt_tab_token;
bool alt_tabbing = false;
int alt_tab_term = 800;

uint32_t alt_tab_timeout_callback(uint32_t trigger_time, void *cb_arg) {
    (void)trigger_time; // Suppress unused variable warning
    (void)cb_arg;       // Suppress unused variable warning

    if (alt_tabbing) {
        unregister_code(KC_RALT);
        alt_tabbing = false;
        log_event(LOG_LEVEL_DEBUG, "alt_tab: timeout");
    }
    return 0; // Don't repeat this callback
}

bool leader_record_alt_tab(uint16_t keycode, keyrecord_t *record) {
    if (alt_tabbing) {
        extend_deferred_exec(alt_tab_token, alt_tab_term); // Reset the timer

        switch (keycode) {
            case KC_U:
            case KC_N:
                if (record->event.pressed) {
                    tap_code(KC_TAB);
                }
                log_event(LOG_LEVEL_DEBUG, "alt_tab");
                return false;

            case KC_O:
            case KC_H:
                if (record->event.pressed) {
                    register_code(KC_RSFT);
                    tap_code(KC_TAB);
                    unregister_code(KC_RSFT);
                }
                log_event(LOG_LEVEL_DEBUG, "shift,alt_tab");
                return false;

            default:
                cancel_deferred_exec(alt_tab_token); // Cancel the callback
                unregister_code(KC_RALT);
                alt_tabbing = false;
                log_event(LOG_LEVEL_INFO, "cancel,alt_tab");
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
            alt_tab_token = defer_exec(alt_tab_term, alt_tab_timeout_callback, NULL);
            log_event(LOG_LEVEL_DEBUG, "alt_tab: start");
        } else {
            // If already alt_tabbing, extend the callback's timer
            extend_deferred_exec(alt_tab_token, alt_tab_term);
            log_event(LOG_LEVEL_DEBUG, "alt_tab: extend");
        }

        if (leader_sequence_one_key(LD_2, KC_U) || leader_sequence_one_key(LD_2, KC_N)) {
            tap_code(KC_TAB);
            log_event(LOG_LEVEL_DEBUG, "alt_tab: lead KC_J");
        } else if (leader_sequence_one_key(LD_2, KC_O) || leader_sequence_one_key(LD_2, KC_H)) {
            register_code(KC_RSFT);
            tap_code(KC_TAB);
            unregister_code(KC_RSFT);
            log_event(LOG_LEVEL_DEBUG, "alt_tab: lead KC_K");
        }
        return true;
    }
    return false;
}

bool leader_sequence_system(void) {

    // Logging Level
    // Log level: Off
    if (leader_sequence_one_key(LD_3, KC_0)) {
        debug_enable=false;
        return true;
    }

    // Log Level: Debug
    if (leader_sequence_one_key(LD_3, KC_1)) {
        debug_enable=true;
        set_log_level(LOG_LEVEL_DEBUG);
        return true;
    }

    // Log Level: Info
    if (leader_sequence_one_key(LD_3, KC_2)) {
        debug_enable=true;
        set_log_level(LOG_LEVEL_INFO);
        return true;
    }

    // Log Level: Error
    if (leader_sequence_one_key(LD_3, KC_3)) {
        debug_enable=true;
        set_log_level(LOG_LEVEL_ERROR);
        return true;
    }

    // Reboot
    if (leader_sequence_two_keys(LD_3, R_, B_)) {
        reset_keyboard();
        return true;
    }

    return false;
}

bool leader_sequence_app_focus(void) {
    //VSCode
    if (leader_sequence_one_key(LD_1, KC_V)) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code16(KC_V);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
        return true;
    }
    //Chrome
    if (leader_sequence_one_key(LD_1, KC_C)) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code16(KC_C);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
        return true;
    }
    //Terminal:WSL
    if (leader_sequence_one_key(LD_1, KC_L)) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code16(KC_L);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
        return true;
    }
    //Terminal:QMK
    if (leader_sequence_one_key(LD_1, KC_Q)) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code16(KC_Q);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
        return true;
    }
    return false;
}

bool leader_sequence_hotkeys(void) {
    // VSCode CMD
    if (leader_sequence_one_key(LD_1, KC_P)) {
        register_code(LS_);
        register_code(KC_LCTL);
        tap_code16(KC_P);
        unregister_code(KC_LCTL);
        unregister_code(LS_);
        return true;
    }
    // VSCode OPEN
    if (leader_sequence_one_key(LD_1, KC_O)) {
        register_code(KC_LCTL);
        tap_code16(KC_K);
        unregister_code(KC_LCTL);
        wait_ms(100);
        register_code(KC_LCTL);
        tap_code16(KC_O);
        unregister_code(KC_LCTL);
        return true;
    }

    // Explorer
    if (leader_sequence_one_key(LD_1, KC_E)) {
        register_code(KC_LGUI);
        tap_code16(KC_E);
        unregister_code(KC_LGUI);
        return true;
    }
    return false;
}
