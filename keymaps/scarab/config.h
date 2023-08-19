//config.h
#pragma once

// Set USB polling interval to 1 ms and enable NKRO
#define USB_POLLING_INTERVAL_MS 1
#define FORCE_NKRO

// Set tapping term to 320 ms and enable per-key tapping term
#define TAPPING_TERM 320
#define PERMISSIVE_HOLD

// Set combo term to 72 ms and enable extra short combos
#define COMBO_TERM 72
#define COMBO_STRICT_TIMER
#define EXTRA_SHORT_COMBOS

// Set leader timeout to 320 ms and enable per-key timing
#define LEADER_TIMEOUT 320
#define LEADER_PER_KEY_TIMING

// Set dynamic macro size to 200 and delay to 50 ms
#define DYNAMIC_MACRO_SIZE 200
#define DYNAMIC_MACRO_DELAY 50

// Custom output for modified keys
#define PROCESS_CUSTOM_MOD_KEYS

// Custom feature keys
#include "feature/feature_config.h"
