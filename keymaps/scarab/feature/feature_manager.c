// Feature manager

#include "feature_manager.h"

bool process_dummy_key(uint16_t keycode, keyrecord_t *record) {
    return true;  // always allow further processing
}

// define the feature array,
// concatenating all the feature arrays from the features you want to use
const feature_key_t feature_keys[] = {
    {KC_NO, process_dummy_key},
#ifdef PROCESS_COUNTER_KEYS
    {X_TARE,    process_counter_key},
    {X_INCR,    process_counter_key},
    {X_DECR,    process_counter_key},
    {X_VALU,    process_counter_key},
    {KC_1,      process_counter_key},
    {KC_2,      process_counter_key},
    {KC_3,      process_counter_key},
    {KC_4,      process_counter_key},
    {KC_5,      process_counter_key},
    {KC_6,      process_counter_key},
    {KC_7,      process_counter_key},
    {KC_8,      process_counter_key},
    {KC_9,      process_counter_key},
#endif
};

uint8_t NUM_FEATURE_KEYS = sizeof(feature_keys) / sizeof(feature_key_t);

// process the feature keys
bool process_record_feature(uint16_t keycode, keyrecord_t *record) {
    // Detect if the keycode is in the feature array
    for (uint8_t i = 0; i < NUM_FEATURE_KEYS; i++) {
        if (keycode == feature_keys[i].keycode) {
            // If it is, call the feature function, and return the result
            log_event(LOG_LEVEL_INFO, "feature key pressed");
            return feature_keys[i].fn(keycode, record);
        }
    }
    // Otherwise, return true to continue processing the key
    return true;
}
