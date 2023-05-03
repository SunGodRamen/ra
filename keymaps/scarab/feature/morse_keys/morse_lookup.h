#ifndef MORSE_LOOKUP_H
#define MORSE_LOOKUP_H

#include "quantum.h"

typedef struct {
    const char* code;
    uint16_t key_code;
} morse_entry_t;

const morse_entry_t morse_lookup_table[] = {
  {".-", KC_A},
  {"-...", KC_B},
  {"-.-.", KC_C},
  {"-..", KC_D},
  {".", KC_E},
  {"..-.", KC_F},
  {"--.", KC_G},
  {"....", KC_H},
  {"..", KC_I},
  {".---", KC_J},
  {"-.-", KC_K},
  {".-..", KC_L},
  {"--", KC_M},
  {"-.", KC_N},
  {"---", KC_O},
  {".--.", KC_P},
  {"--.-", KC_Q},
  {".-.", KC_R},
  {"...", KC_S},
  {"-", KC_T},
  {"..-", KC_U},
  {"...-", KC_V},
  {".--", KC_W},
  {"-..-", KC_X},
  {"-.--", KC_Y},
  {"--..", KC_Z},
  {"-----", KC_0},
  {".----", KC_1},
  {"..---", KC_2},
  {"...--", KC_3},
  {"....-", KC_4},
  {".....", KC_5},
  {"-....", KC_6},
  {"--...", KC_7},
  {"---..", KC_8},
  {"----.", KC_9},
  {".-.-.-", KC_DOT},
  {"--..--", KC_COMM},
  {".----.", KC_QUOT},
  {"-..-.", KC_SLSH},
  {"-.-.-.", KC_SCLN},
  {"-...-", KC_EQL},
  {"-....-", KC_MINS},
  {"..--..", KC_QUES},    //?
  {"-.-.--", KC_EXCLAIM},        //!
  {"-.--.", KC_RPRN},         //(
  {"-.--.-", KC_LPRN},        //)
  {".-...", KC_AMPERSAND},         //&
  {"---...", KC_COLN},     //:
  {".-.-.", KC_PLUS},       //+
  {"..--.-", KC_UNDERSCORE},     //_
  {".-..-.", KC_DOUBLE_QUOTE},     //"
  {"...-..-", KC_DOLLAR},       //$
  {".--.-.", KC_AT}         //@
};

#endif
