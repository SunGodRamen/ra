// morse_keys.c
#include "morse_keys.h"
#include "morse_lookup.h"
#include "quantum.h"
#include <stdio.h>

static char morse_buffer[8];
static uint8_t morse_pos = 0;
static uint16_t morse_timer = 0;

static uint16_t word_buffer[32];
static uint8_t word_pos = 0;
static uint16_t word_timer = 0;

static uint16_t statement_buffer[96];
static uint8_t statement_pos = 0;
static uint16_t statement_timer = 0;

void morse_decoder_init(void) {
    memset(morse_buffer, 0, sizeof(morse_buffer));
    morse_pos = 0;
    morse_timer = 0;
    printf("Morse decoder initialized\n");
}

void morse_decoder_update(void) {
    if (morse_timer && timer_elapsed(morse_timer) > MORSE_TIMEOUT_LETTER) {
        morse_decoder_decode();
        morse_timer = 0;
        morse_pos = 0;
        memset(morse_buffer, 0, sizeof(morse_buffer));
        printf("Morse decoder timed out (letter)\n");
    }

    if (word_timer && timer_elapsed(word_timer) > MORSE_TIMEOUT_WORD) {
        append_word_to_statement();
        word_timer = 0;
        word_pos = 0;
        memset(word_buffer, 0, sizeof(word_buffer));
        printf("Morse decoder timed out (word)\n");
    }

    if (statement_timer && timer_elapsed(statement_timer) > MORSE_TIMEOUT_STATEMENT) {
        output_statement();
        statement_timer = 0;
        statement_pos = 0;
        memset(statement_buffer, 0, sizeof(statement_buffer));
        printf("Morse decoder timed out (statement)\n");
    }
}

bool morse_decoder_process(uint16_t keycode, keyrecord_t *record, void *data) {
    if (record->event.pressed) {
        char morse_input = *((char *)data);
        if (morse_input == ' ' || morse_pos == sizeof(morse_buffer) - 1) {
            // Call decode function when space key is pressed or buffer is full
            morse_decoder_decode();
            morse_timer = 0;
        } else {
            morse_buffer[morse_pos++] = morse_input;
            morse_timer = timer_read();
            word_timer = timer_read(); // Reset the word timer
            statement_timer = timer_read(); // Reset the statement timer
            printf("Morse input: %c, morse_buffer: %s\n", morse_input, morse_buffer);
        }
    }
    return true;
}

void append_word_to_statement(void) {
    for (uint8_t i = 0; i < word_pos; i++) {
        statement_buffer[statement_pos++] = word_buffer[i];
    }
    statement_buffer[statement_pos++] = KC_SPACE; // Append a space after the word
}

void output_statement(void) {
    for (uint8_t i = 0; i < statement_pos - 1; i++) {
        tap_code(statement_buffer[i]);
    }
}

void input_character(uint16_t keycode) {
    tap_code(keycode);
}

void input_shifted_character(uint16_t keycode) {
    register_code16(KC_LSFT);
    tap_code(keycode);
    unregister_code16(KC_LSFT);
}

bool morse_decoder_decode(void) {
    if (!morse_timer || timer_elapsed(morse_timer) < MORSE_TIMEOUT_LETTER) {
        return false;
    }

    morse_timer = 0;

    for (uint8_t i = 0; i < sizeof(morse_lookup_table) / sizeof(morse_entry_t); i++) {
        if (strcmp(morse_buffer, morse_lookup_table[i].code) == 0) {
            word_buffer[word_pos++] = morse_lookup_table[i].key_code;
            morse_pos = 0;
            memset(morse_buffer, 0, sizeof(morse_buffer));
            printf("Morse code decoded: %u\n", morse_lookup_table[i].key_code);
            return true;
        }
    }

    printf("Morse code not found in lookup table\n");
    return false;
}
