//common.h
#ifndef TEXTFLOW_COMMON_H
#define TEXTFLOW_COMMON_H

#include <stddef.h>
#include <stdbool.h>
#include "feature/keymap_ansi/keymap_ansi.h"

typedef enum {
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_SYMBOL,
    TOKEN_END
} TokenType;

typedef struct {
    TokenType type;
    const char *start;
    size_t length;
} Token;

typedef enum {
    VALUE_NONE,
    VALUE_NUMBER,
    VALUE_BOOL,
    VALUE_STRING,
#ifdef PROCESS_TEXTFLOW_VARIABLES
    VALUE_VARIABLE,
#endif
    VALUE_ERROR
} ValueType;

typedef struct {
    ValueType type;
    union {
        double number_value;
        bool bool_value;
        char *string_value;
        char *variable_name;
    };
} Value;

typedef struct Node {
    TokenType type;
    const char *value;
    size_t value_len;
    struct Node *children;
    size_t num_children;
} Node;

#endif // TEXTFLOW_COMMON_H
