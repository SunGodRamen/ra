#include "swap_hands.h"

const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    // left hand *ignored (swapped with the right hand)
    {{0, 4}, {0, 3}, {0, 2}, {0, 1}, {0, 0}},
    {{1, 4}, {1, 3}, {1, 2}, {1, 1}, {1, 0}},
    {{2, 4}, {2, 3}, {2, 2}, {2, 1}, {2, 0}},
    {{KC_NO, KC_NO}, {KC_NO, KC_NO}, {3, 0}, {3, 1}, {KC_NO, KC_NO}},
    // right hand (swapped with the left hand)
    {{0, 4}, {0, 3}, {0, 2}, {0, 1}, {0, 0}},
    {{1, 4}, {1, 3}, {1, 2}, {1, 1}, {1, 0}},
    {{2, 4}, {2, 3}, {2, 2}, {2, 1}, {2, 0}},
    {{KC_NO, KC_NO}, {KC_NO, KC_NO}, {3, 0}, {3, 1}, {KC_NO, KC_NO}}
};
