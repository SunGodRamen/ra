#ifndef LEADER_KEY_H
#define LEADER_KEY_H
#pragma once

#include "quantum.h"
#include "feature/log/log.h"
#include "../../aliases.h"
#include "stdbool.h"
#include "stdint.h"
#include "feature/leader_key/subfeatures/alt_tab.h"

#ifdef LEADER_MULTIKEY
void leader_end_user(uint16_t leader_key);
#endif
bool process_record_leader(uint16_t keycode, keyrecord_t *record);

bool leader_sequence_alt_tab(void);
bool leader_sequence_logging_level(void);
bool leader_sequence_reboot(void);
bool leader_sequence_macros(void);
bool leader_sequence_app_focus(void);
bool leader_sequence_hotkeys(void);

#endif // LEADER_KEY_H
