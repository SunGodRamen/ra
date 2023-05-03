//variables.c
#include "variables.h"
#include <stdlib.h>
#include <string.h>

#define VARIABLE_MAP_SIZE 16

typedef struct {
    char *name;
    Value value;
} VariableEntry;

VariableEntry variable_map[VARIABLE_MAP_SIZE];

void variables_init(void) {
    memset(variable_map, 0, sizeof(variable_map));
}

unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % VARIABLE_MAP_SIZE;
}

void variable_set(const char *name, Value value) {
    unsigned long index = hash(name);
    if (variable_map[index].name != NULL) {
        free(variable_map[index].name);
    }

    variable_map[index].name = strdup(name);
    variable_map[index].value = value;
}

Value variable_get(const char *name) {
    unsigned long index = hash(name);
    if (variable_map[index].name == NULL || strcmp(variable_map[index].name, name) != 0) {
        Value none_value;
        none_value.type = VALUE_NONE;
        return none_value;
    }
    return variable_map[index].value;
}
