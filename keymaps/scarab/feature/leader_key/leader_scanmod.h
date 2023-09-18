#ifndef LEADER_SCANMOD_H
#define LEADER_SCANMOD_H

#include "stdbool.h"
#include "stdint.h"
#include "../../aliases.h"
#include "feature/log/log.h"
#define CUSTOM_SCANCODE_BASE 0xA5

// transform any key to raw USB HID keycode within range 0xA5 to 0xDF.
// when last key in sequence is pressed, send to leader_scanmod_user
void leader_scanmod_user(uint16_t sequence_key);

#endif
