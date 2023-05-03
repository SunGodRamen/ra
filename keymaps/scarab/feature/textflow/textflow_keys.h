//textflow_keys.h
#pragma once

#include "quantum.h"
#include <ctype.h>
#include <limits.h>
#include "feature/keymap_ascii/keymap_ascii.h"
#include "feature/textflow/common.h"
#include "feature/textflow/parser.h"
#include "feature/textflow/interpreter.h"

typedef enum {
    TOKEN_OPERATOR,
    TOKEN_OPERAND
} token_type_t;

typedef struct {
    token_type_t type;
    union {
        char operator;
        int operand;
    } value;
} token_t;

bool textflow_action(uint16_t keycode, keyrecord_t *record, void *data);
bool handle_statement_input(uint16_t keycode, keyrecord_t *record);
int  parse_textflow_buffer(void);
void print_syntax_tree(token_t *token_stack, int token_stack_size);
