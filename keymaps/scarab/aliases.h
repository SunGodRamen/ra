#ifndef ALIASES_H
#define ALIASES_H
#pragma once

#include "quantum.h"

enum leader_keys {
    LD_1 = QK_LEADER,
    LD_2 = PB_1,
    LD_3 = PB_2,
};

enum shorthand_letter {
    A_ = KC_A,
    B_,
    C_,
    D_,
    E_,
    F_,
    G_,
    H_,
    I_,
    J_,
    K_,
    L_,
    M_,
    N_,
    O_,
    P_,
    Q_,
    R_,
    S_,
    T_,
    U_,
    V_,
    W_,
    X_,
    Y_,
    Z_,
};

enum shorthand_number {
    _1 = KC_1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,
    _0,
};

enum shorthand_function {
    _F1 = KC_F1,
    _F2,
    _F3,
    _F4,
    _F5,
    _F6,
    _F7,
    _F8,
    _F9,
    _F10,
    _F11,
    _F12,
};

#define CLN_ KC_COLN
#define CM_ KC_COMM
#define DQ_ KC_DQUO
#define DT_ KC_DOT
#define AO_ LALT_T(KC_O)
#define GE_ LGUI_T(KC_E)
#define CU_ LCTL_T(KC_U)
#define LS_ KC_LSFT

#define ArL  KC_LEFT
#define ArD  KC_DOWN
#define ArU  KC_UP
#define ArR  KC_RIGHT
#define HOME KC_HOME
#define END  KC_END
#define P_UP  KC_PGUP
#define P_DN  KC_PGDN
#define N_TAB  LCTL(KC_TAB)
#define P_TAB  LSFT(LCTL(KC_TAB))
#define WFwd    KC_WFWD
#define WBk     KC_WBAK

#define ___ KC_TRNS
#define FROM KC_TRNS

#define S_TAB LSFT_T(KC_TAB)
#define NUMBR MO(2)
#define NV_SPC LT(1,KC_SPACE)
#define MACRO MO(4)
#define LEAD KC_LEAD
#define MEDIA MO(5)
#define PLAY KC_MPLY
#define NXT KC_MNXT
#define PRV KC_MPRV
#define VDN KC_VOLD
#define VUP KC_VOLU

#define BTN1 KC_BTN1
#define BTN2 KC_BTN2
#define BTN3 KC_BTN3

#endif // ALIASES_H
