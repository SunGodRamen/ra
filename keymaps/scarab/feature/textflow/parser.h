//parser.h
#ifndef TEXTFLOW_PARSER_H
#define TEXTFLOW_PARSER_H
#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "feature/textflow/common.h"

void  tokenize(const char *input, Token *tokens, size_t num_tokens);
Node *parse_list(Token **tokens);
Node *parse_number_or_string(Token **tokens);
Node *parse_expression(Token **tokens);
Node *parse(const char *input);
void  free_tree(Node *node);
void  print_tree(const Node *node, int indent);

#endif // TEXTFLOW_PARSER_H
