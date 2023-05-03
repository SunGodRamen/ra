## Custom Mod Keys
custom_mod_keys is a QMK feature that allows you to create custom behavior for specific key combinations involving a regular key and a modifier key (such as Shift, Ctrl, Alt, or GUI). You can also configure the feature to respond to certain non-modifier keys being held down.

## Usage
To use custom_mod_keys in your keymap, follow these steps:

Include the custom_mod_keys.h header file in your keymap file:

    #include "custom_mod_keys.h"

Define your custom mod keys array and the number of custom mod keys:

    const custom_mod_key_t custom_mod_keys[] = {
        {KC_A, KC_B, KC_LSFT},
        {KC_C, KC_D, KC_LCTL},
    };

    uint8_t NUM_CUSTOM_MOD_KEYS = sizeof(custom_mod_keys) / sizeof(custom_mod_key_t);

In this example, when the Left Shift is held down and the 'A' key is pressed, it will produce a 'B' character. When the Left Control is held down and the 'C' key is pressed, it will produce a 'D' character.

Call the process_custom_mod_keys() function from your process_record_user() function:

    bool process_record_user(uint16_t keycode, keyrecord_t *record) {
        if (!process_custom_mod_keys(keycode, record)) {
            return false;
        }

        // Your other key processing code here

        return true;
    }

Now, your keymap will have the custom_mod_keys feature enabled, allowing you to create custom key combinations involving modifier keys.

## Configuration
The custom_mod_key_t structure is used to define custom key combinations. Each entry in the custom_mod_keys[] array has three fields:

keycode: The base key that will be modified by the modifier key.
mod_keycode: The new keycode that will be sent when the modifier is active.
modifier: The modifier key that triggers the change in behavior. Can be a specific modifier key like KC_LSFT, or a non-modifier key that needs to be held down.
You can add as many custom mod key entries as you like. Just make sure to update the NUM_CUSTOM_MOD_KEYS variable accordingly.

## Additional Notes
The custom_mod_keys feature is compatible with other QMK features like Layer Tap and Mod Tap.
The feature can be configured to work with multiple custom mod key entries that share the same base keycode or modifier. The first matching entry in the custom_mod_keys[] array will be used.
