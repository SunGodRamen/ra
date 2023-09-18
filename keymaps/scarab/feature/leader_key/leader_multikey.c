#include "leader_multikey.h"

typedef bool (*leader_func)(void);

//IDEAS;
// copy paste
// app focus
// mouse
// function
// tab navigation
// window navigation
// direct file access
// swap hands
// dynamic lead time per start key

leader_func sequences_0[] = {
    leader_sequence_hotkeys,
};

leader_func sequences_1[] = {
    leader_sequence_alt_tab,
    leader_sequence_app_focus,
};

leader_func sequences_2[] = {
    leader_sequence_logging_level,
    leader_sequence_reboot,
};

void leader_end_user(uint16_t leaderkey) {
    switch(leaderkey) {
        case LEAD_0:
            for (int i = 0; i < ARRAY_SIZE(sequences_0); i++) {
                if (sequences_0[i]()) {
                    return;
                }
            }
            break;
        case LEAD_1:
            for (int i = 0; i < ARRAY_SIZE(sequences_1); i++) {
                if (sequences_1[i]()) {
                    return;
                }
            }
            break;
        case LEAD_2:
            for (int i = 0; i < ARRAY_SIZE(sequences_2); i++) {
                if (sequences_2[i]()) {
                    return;
                }
            }
            break;
        default:
            break;
    }
    // Log timeout if no sequence matched
    write_log_format(LOG_LEVEL_INFO, "leader_sequence timeout\n");
}

bool process_record_leader(uint16_t keycode, keyrecord_t *record) {
    if (!leader_record_alt_tab(keycode, record)) {
        write_log_format(LOG_LEVEL_INFO, "leader_record_alt_tab\n");
        return false;
    }
    return true;
}

bool leader_sequence_cancel(void) {
    if (leader_sequence_one_key(LS_) ||
        leader_sequence_one_key(NV_SPC))
    {
        write_log_format(LOG_LEVEL_INFO, "leader_sequence cancel\n");
        return true;
    }
    return false;
}

bool leader_sequence_logging_level(void) {
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

bool leader_sequence_reboot(void) {
    // Reboot
    if (leader_sequence_two_keys(R_, B_)) {
        write_log_format(LOG_LEVEL_INFO, "leader_sequence reboot\n");
        reset_keyboard();
        return true;
    }
    return false;
}

bool leader_sequence_app_focus(void) {
    //VSCode
    if (leader_sequence_one_key(KC_V)) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code16(KC_V);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
        return true;
    }
    //Chrome
    if (leader_sequence_one_key(KC_C)) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code16(KC_C);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
        return true;
    }
    //Terminal:WSL
    if (leader_sequence_one_key(KC_L)) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        tap_code16(KC_L);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
        return true;
    }
    //Terminal:QMK
    if (leader_sequence_one_key(KC_Q)) {
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
    if (leader_sequence_one_key(KC_P)) {
        register_code(LS_);
        register_code(KC_LCTL);
        tap_code16(KC_P);
        unregister_code(KC_LCTL);
        unregister_code(LS_);
        return true;
    }
    // VSCode OPEN
    if (leader_sequence_one_key(KC_O)) {
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
    if (leader_sequence_one_key(KC_E)) {
        register_code(KC_LGUI);
        tap_code16(KC_E);
        unregister_code(KC_LGUI);
        return true;
    }
    return false;
}
