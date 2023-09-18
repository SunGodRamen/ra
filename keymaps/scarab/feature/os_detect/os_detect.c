#include "os_detect.h"

os_variant_t os = OS_UNSURE;

char* os_to_string(os_variant_t os);
bool swap_ctl_gui(uint16_t keycode, keyrecord_t *record);

bool process_record_os(uint16_t keycode, keyrecord_t *record) {
    if (os == OS_UNSURE) {
        os = detected_host_os();
        write_log_format(LOG_LEVEL_INFO, "Detected OS: %s\n", os_to_string(os));
    }

    if (!swap_ctl_gui(keycode, record)) {
        return false;
    }

    return true;
}

bool swap_ctl_gui(uint16_t keycode, keyrecord_t *record) {
    if (os == OS_MACOS || os == OS_IOS) {
        write_log_format(LOG_LEVEL_INFO, "Detected OS: %s, swapping Ctrl and Gui keys\n", os_to_string(os));

        switch (keycode) {
            case KC_LCTL:
                if (record->event.pressed) {
                    register_code(KC_LGUI);
                } else {
                    unregister_code(KC_LGUI);
                }
                return false;

            case KC_RCTL:
                if (record->event.pressed) {
                    register_code(KC_RGUI);
                } else {
                    unregister_code(KC_RGUI);
                }
                return false;

            case KC_LGUI:
                if (record->event.pressed) {
                    register_code(KC_LCTL);
                } else {
                    unregister_code(KC_LCTL);
                }
                return false;

            case KC_RGUI:
                if (record->event.pressed) {
                    register_code(KC_RCTL);
                } else {
                    unregister_code(KC_RCTL);
                }
                return false;

            default:
                return true;
        }
    }
    return true;
}

char* os_to_string(os_variant_t os) {
    switch (os) {
        case OS_LINUX:
            return "Linux";
        case OS_WINDOWS:
            return "Windows";
        case OS_MACOS:
            return "macOS";
        case OS_IOS:
            return "iOS";
        case OS_UNSURE:
            return "Unsure";
        default:
            return "Unknown";
    }
}
