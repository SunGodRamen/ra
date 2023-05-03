//timer_keys.h
#pragma once

#include QMK_KEYBOARD_H

// Action functions for timer keys
void t_mode_action(uint16_t keycode, keyrecord_t *record, void *data);
void t_start_action(uint16_t keycode, keyrecord_t *record, void *data);
void t_stop_action(uint16_t keycode, keyrecord_t *record, void *data);
void t_reset_action(uint16_t keycode, keyrecord_t *record, void *data);
void t_lap_action(uint16_t keycode, keyrecord_t *record, void *data);
void t_keyset_action(uint16_t keycode, keyrecord_t *record, void *data);

// Functions to update timer and display
void update_timestamp(void);
char *write_formatted_timestamp(uint32_t timestamp);
void delete_formatted_timestamp(void);

// Process keycodes for timer keys
bool process_timer_keys(uint16_t keycode, keyrecord_t *record);

// Process matrix scans
void process_timer_scan(void);
