//config.h
#pragma once

// Set USB polling interval to 1 ms and enable NKRO
#define USB_POLLING_INTERVAL_MS 1
#define FORCE_NKRO

// Set tapping term to 200 ms and enable per-key tapping term
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

// Set combo term to 72 ms and enable extra short combos
#define COMBO_TERM 72
#define COMBO_KEY_BUFFER_LENGTH 16
#define COMBO_BUFFER_LENGTH 16
#define COMBO_STRICT_TIMER
#define EXTRA_SHORT_COMBOS


// Set leader timeout to 480 ms and enable per-key timing
#define LEADER_TIMEOUT 480
#define LEADER_PER_KEY_TIMING

// Set dynamic macro size to 600 and delay to 1 ms
#define DYNAMIC_MACRO_SIZE 600
#define DYNAMIC_MACRO_DELAY 1


// Enable processing of custom shift keys, counter keys, and timer keys
#define PROCESS_CUSTOM_MOD_KEYS
//#define PROCESS_RAWHID_KEYS
#define PROCESS_CUSTOM_KEYS
#ifdef PROCESS_CUSTOM_KEYS
#define PROCESS_COUNTER_KEYS
//#define PROCESS_MORSE_KEYS
//#define PROCESS_TIMER_KEYS
#define PROCESS_ARCH_TAP_KEYS
//#define PROCESS_TEXTFLOW_KEYS
//#define PROCESS_TEXTFLOW_VARIABLES
#endif
