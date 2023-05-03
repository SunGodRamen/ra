//morse_keys.h
#pragma once
#include "quantum.h"
#include <stdbool.h>
#include <stdint.h>

#define MORSE_TIMEOUT_LETTER 300 // Time in milliseconds to wait for a character
#define MORSE_TIMEOUT_WORD 500 // Time in milliseconds to wait for a word
#define MORSE_TIMEOUT_STATEMENT 750 // Time in milliseconds to wait to print the statement

void morse_decoder_init(void);
void morse_decoder_update(void);
bool morse_decoder_process(uint16_t keycode, keyrecord_t *record, void *data);
bool morse_decoder_decode(void);

void output_statement(void);
void append_word_to_statement(void);

void input_character(uint16_t keycode);
void input_shifted_character(uint16_t keycode);
