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
#define LEADER_MULTI_KEY
#define LEADER_VAR_LEN 6
#define LEADER_SCANMOD
#define LEADER_TIMEOUT 320
#define LEADER_PER_KEY_TIMING

// Set dynamic macro size to 200 and delay to 2o0 ms
#define DYNAMIC_MACRO_SIZE 200
#define DYNAMIC_MACRO_DELAY 25


// Personal feature flags
#define LOGGING_ENABLE
#define HID_CONTROLLER_ENABLE
#define MOD_KEYS_ENABLE
#define FEATURE_KEYS_ENABLE
#define COUNTER_KEYS_ENABLE
