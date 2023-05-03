//interpreter.h
#ifndef TEXTFLOW_INTERPRETER_H
#define TEXTFLOW_INTERPRETER_H

#include "feature/textflow/common.h"
#include "feature/textflow/parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Value interpret_node(const Node *node);
void value_to_string(const Value *value, char *buf, size_t bufsize);
void  print_value(const Value *value, char *result_str);

#endif
