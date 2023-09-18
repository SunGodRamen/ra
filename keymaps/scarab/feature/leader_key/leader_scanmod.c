#include "leader_scanmod.h"

// Function to transform a regular keycode to a custom scancode
uint16_t transform_to_custom_scancode(uint16_t keycode) {
    uint16_t custom_scancode = CUSTOM_SCANCODE_BASE + (keycode % (0xDF - CUSTOM_SCANCODE_BASE + 1));

    // Logging the transformed and original keycode
    write_log_format(LOG_LEVEL_DEBUG, "Original Keycode: 0x%X | Transformed Scancode: 0x%X\n", keycode, custom_scancode);

    return custom_scancode;
}

void leader_scanmod_user(uint16_t sequence_key) {
    write_log_format(LOG_LEVEL_DEBUG, "leader_mod_user\n");
    uint16_t custom_code = transform_to_custom_scancode(sequence_key);
    register_code(custom_code);
    unregister_code(custom_code);
    return;
}
