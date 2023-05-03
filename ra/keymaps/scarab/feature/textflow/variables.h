//variables.h
#ifndef TEXTFLOW_VARIABLES_H
#define TEXTFLOW_VARIABLES_H

#include "features/textflow/interpreter.h"
#include "features/textflow/common.h"

void variables_init(void);
void variable_set(const char *name, Value value);
Value variable_get(const char *name);

#endif // TEXTFLOW_VARIABLES_H
