#ifndef ALIASES_H
#define ALIASES_H
#pragma once

#include "quantum.h"

enum shorthand_letter {
    A_ = KC_A,
    B_ = KC_B,
    C_ = KC_C,
    D_ = KC_D,
    E_ = KC_E,
    F_ = KC_F,
    G_ = KC_G,
    H_ = KC_H,
    I_ = KC_I,
    J_ = KC_J,
    K_ = KC_K,
    L_ = KC_L,
    M_ = KC_M,
    N_ = KC_N,
    O_ = KC_O,
    P_ = KC_P,
    Q_ = KC_Q,
    R_ = KC_R,
    S_ = KC_S,
    T_ = KC_T,
    U_ = KC_U,
    V_ = KC_V,
    W_ = KC_W,
    X_ = KC_X,
    Y_ = KC_Y,
    Z_ = KC_Z,
};

#define NUMBR MO(2)
enum shorthand_number {
    _1 = KC_1,
    _2 = KC_2,
    _3 = KC_3,
    _4 = KC_4,
    _5 = KC_5,
    _6 = KC_6,
    _7 = KC_7,
    _8 = KC_8,
    _9 = KC_9,
    _0 = KC_0,
};

enum shorthand_function {
    _F1 = KC_F1,
    _F2 = KC_F2,
    _F3 = KC_F3,
    _F4 = KC_F4,
    _F5 = KC_F5,
    _F6 = KC_F6,
    _F7 = KC_F7,
    _F8 = KC_F8,
    _F9 = KC_F9,
    _F10 = KC_F10,
    _F11 = KC_F11,
    _F12 = KC_F12,
};

#define XXX KC_NO
#define ___ KC_TRANSPARENT
#define FROM KC_TRANSPARENT

#define CLN_ KC_COLN
#define SCL_ KC_SCLN
#define CM_ KC_COMMA
#define DQ_ KC_DQUO
#define DT_ KC_DOT
#define AO_ LALT_T(KC_O)
#define GE_ LGUI_T(KC_E)
#define CU_ LCTL_T(KC_U)
#define LS_ KC_LSFT

#define NV_SPC LT(1,KC_SPACE)
#define ArL  KC_LEFT
#define ArD  KC_DOWN
#define ArU  KC_UP
#define ArR  KC_RIGHT
#define HOME KC_HOME
#define END  KC_END
#define P_UP  KC_PAGE_UP
#define P_DN  KC_PAGE_DOWN
#define N_TAB  LCTL(KC_TAB)
#define P_TAB  LSFT(LCTL(KC_TAB))
#define WFwd    KC_WWW_FORWARD
#define WBk     KC_WWW_BACK

#define S_TAB LSFT_T(KC_TAB)

#define MACRO MO(4)
#define DM_P1     QK_DYNAMIC_MACRO_PLAY_1
#define DM_R1     QK_DYNAMIC_MACRO_RECORD_START_1
#define DM_P2     QK_DYNAMIC_MACRO_PLAY_2
#define DM_R2     QK_DYNAMIC_MACRO_RECORD_START_2

#define LEAD QK_LEADER
enum leader_aliases {
    LEAD_0 = 0x7C58, // QK_LEADER
    LEAD_1 = 0x7E40, // QK_USER_0:LEAD_1
    LEAD_2 = 0x7E41, // QK_USER_1:LEAD_2
    LD_SCAN = 0x00A0 // KC_OUT: Send as scan code sequence
};

#define MEDIA MO(5)
#define PLAY KC_MEDIA_PLAY_PAUSE
#define NXT KC_MEDIA_NEXT_TRACK
#define PRV KC_MEDIA_PREV_TRACK
#define VDN KC_KB_VOLUME_DOWN
#define VUP KC_KB_VOLUME_UP

#define BTN1 KC_MS_BTN1
#define BTN2 KC_MS_BTN2
#define BTN3 KC_MS_BTN3
#define BTN4 KC_MS_BTN4
#define BTN5 KC_MS_BTN5
#define WHUP KC_MS_WH_UP
#define WHDN KC_MS_WH_DOWN

#define RW_B LT(8, B_)
enum raw_aliases {
    RAW1 = QK_USER_3,
    RAW2 = QK_USER_4,
    RAW3 = QK_USER_5,
};

#endif // ALIASES_H
