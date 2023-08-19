#include "leader_key.h"

void leader_end_user(void) {

    if (leader_sequence_alt_tab()) {
        log_event(LOG_LEVEL_INFO, "leader_sequence_alt_tab");
        return;
    }

    if (leader_sequence_log()) {
        log_event(LOG_LEVEL_INFO, "leader_sequence_log");
        return;
    }

    if (leader_sequence_macros()) {
        log_event(LOG_LEVEL_INFO, "leader_sequence_macro");
        return;
    }

    if (leader_sequence_hotkeys()) {
        log_event(LOG_LEVEL_INFO, "leader_sequence_hotkey");
        return;
    }

    // press LSFT to cancel
    if (leader_sequence_one_key(KC_LSFT)) {
        log_event(LOG_LEVEL_INFO, "leader_sequence cancel");
        return;
    }

    // if not handled above, send enter
    tap_code16(KC_ENT);
    log_event(LOG_LEVEL_INFO, "leader_sequence default");
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
            case KC_K:
                if (record->event.pressed) {
                    tap_code(KC_TAB);
                }
                log_event(LOG_LEVEL_DEBUG, "alt_tab: KC_K");
                return false;

            case KC_J:
                if (record->event.pressed) {
                    register_code(KC_RSFT);
                    tap_code(KC_TAB);
                    unregister_code(KC_RSFT);
                }
                log_event(LOG_LEVEL_DEBUG, "alt_tab: KC_J");
                return false;

            default:
                cancel_deferred_exec(alt_tab_token); // Cancel the callback
                unregister_code(KC_RALT);
                alt_tabbing = false;
                log_event(LOG_LEVEL_INFO, "alt_tab: cancelled");
                return true;
        }
    }
    return true;
}

bool leader_sequence_alt_tab(void) {
    if (leader_sequence_one_key(KC_K) || leader_sequence_one_key(KC_J)) {
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

        if (leader_sequence_one_key(KC_J)) {
            tap_code(KC_TAB);
            log_event(LOG_LEVEL_DEBUG, "alt_tab: lead KC_J");
        } else if (leader_sequence_one_key(KC_K)) {
            register_code(KC_RSFT);
            tap_code(KC_TAB);
            unregister_code(KC_RSFT);
            log_event(LOG_LEVEL_DEBUG, "alt_tab: lead KC_K");
        }
        return true;
    }
    return false;
}

bool leader_sequence_log(void) {

    // Logging Level
    // Log level: Off
    if (leader_sequence_one_key(KC_0)) {
        debug_enable=false;
        return true;
    }

    // Log Level: Debug
    if (leader_sequence_one_key(KC_1)) {
        debug_enable=true;
        set_log_level(LOG_LEVEL_DEBUG);
        return true;
    }

    // Log Level: Info
    if (leader_sequence_one_key(KC_2)) {
        debug_enable=true;
        set_log_level(LOG_LEVEL_INFO);
        return true;
    }

    // Log Level: Error
    if (leader_sequence_one_key(KC_3)) {
        debug_enable=true;
        set_log_level(LOG_LEVEL_ERROR);
        return true;
    }

    return false;
}

bool leader_sequence_hotkeys(void) {
    // VSCode Cmd
    if (leader_sequence_one_key(KC_P)) {
        register_code(KC_LSFT);
        register_code(KC_LCTL);
        tap_code16(KC_P);
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        return true;
    }
    return false;
}

void repeat(uint16_t keycode, int rep) {
    for (int n = rep; n > 0; n--) {
        register_code16(keycode);
        unregister_code16(keycode);
    }
}

bool leader_sequence_macros(void) {
    // EMAIL
    if (leader_sequence_two_keys(KC_E, KC_G)) {
        SEND_STRING("AVONS394@gmail.com");
        return true;
    }

    // CODE SHORTHAND
    // IF
    if (leader_sequence_two_keys(KC_I, KC_F)) {
        send_string("if (  ) {  }");
        repeat(KC_LEFT, 7);
        return true;
    }
    // FOR
    if (leader_sequence_two_keys(KC_F, KC_R)) {
        send_string("for (  ) {  }");
        repeat(KC_LEFT, 7);
        return true;
    }
    // INT I IN
    if (leader_sequence_three_keys(KC_I, KC_N, KC_T)) {
        send_string("int i=0; i< ; i++");
        repeat(KC_LEFT, 6);
        return true;
    }
    // FALSE
    if (leader_sequence_one_key(KC_F)) {
        send_string("false");
        return true;
    }
    // TRUE
    if (leader_sequence_one_key(KC_T)) {
        send_string("true");
        return true;
    }
    // SHEBANG
    if (leader_sequence_two_keys(KC_S, KC_H)) {
        send_string("#!/usr/bin/env ");
        return true;
    }
    // SSH KEYGEN
    if (leader_sequence_three_keys(KC_S, KC_S, KC_H)) {
        send_string("ssh-keygen -t ed25519 -C ");
        tap_code16(KC_DQUO);
        tap_code16(KC_DQUO);
        tap_code16(KC_LEFT);
        return true;
    }
    // GIT PUSH
    if (leader_sequence_two_keys(KC_G, KC_P)) {
        send_string("git push");
        return true;
    }
    return false;
}
