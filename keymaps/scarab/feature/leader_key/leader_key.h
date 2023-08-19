#ifndef LEADER_KEY_H
#define LEADER_KEY_H
#pragma once

#include "quantum.h"
#include "feature/log/log.h"
#include "../../aliases.h"

void leader_end_user(void);
bool process_record_leader(uint16_t keycode, keyrecord_t *record);

bool leader_sequence_alt_tab(void);
bool leader_sequence_log(void);
bool leader_sequence_macros(void);
bool leader_sequence_hotkeys(void);

bool leader_record_alt_tab(uint16_t keycode, keyrecord_t *record);
uint32_t alt_tab_timeout_callback(uint32_t trigger_time, void *cb_arg);


#endif // LEADER_KEY_H
