//mod_keys.c
#include "mod_keys.h"

custom_mod_key_t custom_mod_keys[] = {
    {KC_COLN,      KC_SCLN,    KC_LSFT},
    {KC_DQUO,      KC_QUOT,    KC_LSFT},
    {KC_DOT,       KC_EXCLAIM, KC_LSFT},
    {KC_COMM,      KC_QUES,    KC_LSFT},
    {KC_BSPC,      KC_DEL,     KC_LSFT},
    {KC_8,         KC_ASTERISK,KC_LSFT},
    {LCTL_T(KC_E), KC_BTN2,    KC_LOPT},
    {LCMD_T(KC_U), KC_BTN1,    KC_LOPT},
};

uint8_t NUM_CUSTOM_MOD_KEYS = sizeof(custom_mod_keys) / sizeof(custom_mod_key_t);

bool process_custom_mod_keys(uint16_t keycode, keyrecord_t *record) {
    // Initialize a static variable to store the registered keycode
    static uint16_t registered_keycode = KC_NO;

    // If a keycode was previously registered, unregister it
    if (registered_keycode != KC_NO) {
        unregister_code16(registered_keycode);
        registered_keycode = KC_NO;
    }

    // Check if the key event is a key press
    if (record->event.pressed) {
        // Get the current modifiers state
        const uint8_t mods = get_mods();

        // Combine the current modifiers state with weak modifiers and one-shot modifiers, if they are enabled
#ifndef NO_ACTION_ONESHOT
        uint8_t mod_masks = mods | get_weak_mods() | get_oneshot_mods();
#else
        uint8_t mod_masks = mods;
#endif

        // If there are active modifiers
        if (mod_masks) {
            // Check if the keycode is a mod-tap or layer-tap and has not been tapped yet; if so, return true
            if ((IS_QK_MOD_TAP(keycode) || IS_QK_LAYER_TAP(keycode)) &&
                record->tap.count == 0) {
                return true;
            }

            // Iterate over the custom mod keys array
            for (int i = 0; i < NUM_CUSTOM_MOD_KEYS; ++i) {
                // Get the key position for the custom modifier key
                keypos_t modifier_keypos = {.col = custom_mod_keys[i].modifier & 0xF, .row = custom_mod_keys[i].modifier >> 4};
                // Get the keycode for the custom modifier key
                uint16_t modifier_keycode = keymap_key_to_keycode(0, modifier_keypos);
                // Check if the pressed keycode matches the custom mod key and if the custom modifier is active or if the custom modifier key is pressed
                if (keycode == custom_mod_keys[i].keycode && ((mod_masks & MOD_BIT(custom_mod_keys[i].modifier)) || (modifier_keycode != KC_NO && (get_mods() & (1 << (modifier_keycode - KC_LCTL)))))) {
                    // Set the registered keycode to the mod_keycode from the custom mod key
                    registered_keycode = custom_mod_keys[i].mod_keycode;
                    // Get the modifier mask for the custom modifier key
                    uint8_t mod_mask = MOD_BIT(custom_mod_keys[i].modifier);

                    // If the registered keycode is a mod keycode and the mod_mask is part of the mod_keycode, register the keycode
                    if (IS_QK_MODS(registered_keycode) &&
                        (QK_MODS_GET_MODS(registered_keycode) & mod_mask) != 0) {
                        register_code16(registered_keycode);
                    } else {
                        // If the custom modifier key is a modifier, remove it from the active modifiers
                        if (IS_MODIFIER_KEYCODE(custom_mod_keys[i].modifier)) {
                            del_weak_mods(mod_mask);
#ifndef NO_ACTION_ONESHOT
                            del_oneshot_mods(mod_mask);
#endif
                            unregister_mods(mod_mask);
                        } else {
                            // If the custom modifier key is not a modifier, unregister the keycode
                            unregister_code(custom_mod_keys[i].modifier);
                        }
                        // Register the custom mod keycode and restore the original modifiers state
                        register_code16(registered_keycode);
                        set_mods(mods);
                    }
                    // Return false to indicate that the custom mod key has been processed
                    return false;
                }
            }
        }
    }

    // If the keycode was not processed as a custom mod key, return true
    return true;
}
