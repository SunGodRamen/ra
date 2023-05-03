// app_driver.h
#pragma once
#include "quantum.h"

typedef struct {
    uint16_t data;
    bool (*fn)(uint16_t, void *);
    void *user_data;
} custom_rawhid_t;

typedef enum {
    BASE,
    GOOGLE,
    VSCODE,
    // Add more app names here
} app_t;

extern app_t current_app;

bool rawhid_app(uint16_t data, void *user_data);
void process_app_driver(uint8_t *data, uint8_t length);

typedef struct {
    uint16_t keycode;
    uint16_t app_keycode;
    app_t app;
} custom_app_key_t;

extern custom_app_key_t custom_app_keys[];
extern uint8_t NUM_CUSTOM_APP_KEYS;

bool process_custom_app_keys(uint16_t keycode, keyrecord_t *record);
