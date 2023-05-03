// os_keys.c
/*
    OS_UNSURE,
    OS_LINUX,
    OS_WINDOWS,
    OS_MACOS,
    OS_IOS,
*/

#include "os_keys.h"

os_variant_t current_os = OS_UNSURE;

void swap_control_and_gui_on_windows_and_linux(void) {
    os_variant_t os = detected_host_os();
    if (os == OS_WINDOWS || os == OS_LINUX) {
        // Swap Control and GUI keys
        keymap_config.swap_lctl_lgui = true;
        keymap_config.swap_rctl_rgui = true;
    } else {
        // Use regular mapping for other OSes
        keymap_config.swap_lctl_lgui = false;
        keymap_config.swap_rctl_rgui = false;
    }
    // Save the settings to EEPROM
    eeconfig_update_keymap(keymap_config.raw);
}

void swap_key(uint16_t keycode, keyrecord_t *record, uint16_t data) {
    if (record->event.pressed) {
        register_code16(data);
    } else {
        unregister_code16(data);
    }
}

custom_os_key_t custom_os_keys[] = {
    {LGUI_T(KC_U),  swap_key,  LCTL_T(KC_U),    OS_LINUX},
};

uint8_t NUM_CUSTOM_OS_KEYS = sizeof(custom_os_keys) / sizeof(custom_os_key_t);

bool process_custom_os_keys(uint16_t keycode, keyrecord_t *record) {
    if (current_os == OS_UNSURE) {
        current_os = detected_host_os();
    }
    for (int i = 0; i < NUM_CUSTOM_OS_KEYS; ++i) {
        if (keycode == custom_os_keys[i].keycode && current_os == custom_os_keys[i].os) {
            // Call the custom function
            custom_os_keys[i].os_function(keycode, record, custom_os_keys[i].data);
            return false;
        }
    }

    return true;
}
