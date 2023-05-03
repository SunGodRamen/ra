//app_driver.c
#include "app_driver.h"
#include "raw_hid.h"

app_t current_app = BASE;

const custom_rawhid_t custom_rawhid[] = {
    {0x0101, rawhid_app, (void *)GOOGLE},
    {0x0102, rawhid_app, (void *)VSCODE},
};

uint8_t NUM_CUSTOM_RAWHID = sizeof(custom_rawhid) / sizeof(custom_rawhid_t);

custom_app_key_t custom_app_keys[] = {
    {KC_G, LCTL(KC_TAB), GOOGLE},
    {KC_V, KC_RIGHT,     VSCODE},
};

uint8_t NUM_CUSTOM_APP_KEYS = sizeof(custom_app_keys) / sizeof(custom_app_key_t);

bool rawhid_app(uint16_t data, void *user_data) {
    app_t app = (app_t)user_data;
    current_app = app;
    return true;
}

void process_app_driver(uint8_t *data, uint8_t length) {
    if (length != RAW_EPSIZE) {
        return;
    }

    uint16_t data_word = (data[0] << 8) | data[1];

    for (uint8_t i = 0; i < NUM_CUSTOM_RAWHID; i++) {
        if (data_word == custom_rawhid[i].data) {
            if (custom_rawhid[i].fn) {
                custom_rawhid[i].fn(data_word, custom_rawhid[i].user_data);
            }
        }
    }
}

bool process_custom_app_keys(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        for (int i = 0; i < NUM_CUSTOM_APP_KEYS; ++i) {
            if (keycode == custom_app_keys[i].keycode && current_app == custom_app_keys[i].app) {
                // Send the app-specific keycode
                register_code16(custom_app_keys[i].app_keycode);
                return false;
            }
        }
    } else {
        for (int i = 0; i < NUM_CUSTOM_APP_KEYS; ++i) {
            if (keycode == custom_app_keys[i].keycode && current_app == custom_app_keys[i].app) {
                // Unregister the app-specific keycode
                unregister_code16(custom_app_keys[i].app_keycode);
                return false;
            }
        }
    }

    return true;
}
