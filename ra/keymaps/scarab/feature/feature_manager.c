//feature_manager.c
#include "feature_manager.h"
#include "quantum.h"

#ifdef PROCESS_COUNTER_KEYS
#include "feature/counter_keys/counter_keys.h"
#endif
#ifdef PROCESS_TIMER_KEYS
#include "feature/timer_keys/timer_keys.h"
#endif
#ifdef PROCESS_TEXTFLOW_KEYS
#include "feature/textflow/textflow_keys.h"
#endif
#ifdef PROCESS_MORSE_KEYS
#include "feature/morse_keys/morse_keys.h"
#endif
#ifdef PROCESS_ARCH_TAP_KEYS
#include "feature/arch_tap_keys/arch_tap_keys.h"
#endif

const custom_key_t custom_keys[] = {

#ifdef PROCESS_COUNTER_KEYS
    {X_TARE, tare_action, NULL},
    {X_INCR, incr_action, NULL},
    {X_DECR, decr_action, NULL},
    {X_VALU, valu_action, NULL},
#endif

#ifdef PROCESS_TIMER_KEYS
    {T_MODE,    t_mode_action, NULL},
    {T_STRT,    t_start_action, NULL},
    {T_STOP,    t_stop_action, NULL},
    {T_LAP,     t_lap_action, NULL},
    {T_RST,     t_reset_action, NULL},
    {T_KEYSET,  t_keyset_action, NULL},
#endif

#ifdef PROCESS_TEXTFLOW_KEYS
    {T_FLOW, textflow_action, NULL},
#endif

#ifdef PROCESS_MORSE_KEYS
    {M_DOT, morse_decoder_process, "."},
    {M_DASH, morse_decoder_process, "-"},
#endif

#ifdef PROCESS_ARCH_TAP_KEYS
    {M_FWRD, macro_iterator_forward, NULL},
    {M_BACK, macro_iterator_backward, NULL},
#endif

};

uint8_t NUM_CUSTOM_KEYS = sizeof(custom_keys) / sizeof(custom_key_t);

// KEYBOARD INIT
void process_keyboard_init(void) {
#ifdef PROCESS_MORSE_KEYS
    morse_decoder_init();
#endif
}

//   MATRIX SCAN
void process_custom_matrix_scan(void) {

#ifdef PROCESS_TIMER_KEYS
    process_timer_scan();
#endif

#ifdef PROCESS_MORSE_KEYS
    morse_decoder_update();
#endif

}


//     PROCESS RECORD
bool process_custom_keys(uint16_t keycode, keyrecord_t *record) {
    for (uint8_t i = 0; i < NUM_CUSTOM_KEYS; i++) {
        if (keycode == custom_keys[i].keycode) {
            if (custom_keys[i].fn) {
                bool should_continue = custom_keys[i].fn(keycode, record, custom_keys[i].data);
                if (!should_continue) {
                    return false;
                }
            }
        }
    }

#ifdef PROCESS_COUNTER_KEYS
    if (KC_1 <= keycode && keycode <= KC_9) {
        bool should_continue = handle_number_key_tap(keycode, record);
        if (!should_continue) {
            return false;
        }
    }
#endif


#ifdef PROCESS_TEXTFLOW_KEYS
    handle_statement_input(keycode, record);
#endif

#ifdef PROCESS_ARCH_TAP_KEYS
    track_key_press(keycode, record);
#endif

    return true;

}

