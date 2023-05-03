// interpreter.c
#include "feature/textflow/interpreter.h"

// Interpret a node from the abstract syntax tree and return its value
Value interpret_node(const Node *node) {
    Value result;

    // Handle symbol tokens
    if (node->type == TOKEN_SYMBOL) {
        // Check if the symbol is a boolean value
        if (strncmp(node->value, "T", node->value_len) == 0) {
            result.type = VALUE_BOOL;
            result.bool_value = true;
        } else if (strncmp(node->value, "F", node->value_len) == 0) {
            result.type = VALUE_BOOL;
            result.bool_value = false;
        } else if (node->value[0] == '\'') {
            // Handle string values
            result.type = VALUE_STRING;
            result.string_value = strndup(node->value + 1, node->value_len - 2);
        } else {
            // Handle number values and variable names
            // You can add more sophisticated parsing here.
            result.type = VALUE_NUMBER;
            sscanf(node->value, "%lf", &result.number_value); // Change here
        }
    } else if (node->type == TOKEN_LPAREN) {
        // Handle list tokens, for now, we only handle addition, subtraction,
        // multiplication, and division

        // Addition
        if (strncmp(node->children[0].value, "+", node->children[0].value_len) == 0) {
            Value left = interpret_node(&node->children[1]);
            Value right = interpret_node(&node->children[2]);

            if (left.type == VALUE_NUMBER && right.type == VALUE_NUMBER) {
                result.type = VALUE_NUMBER;
                result.number_value = left.number_value + right.number_value;
            } else {
                // Error: Invalid types for addition
                result.type = VALUE_ERROR;
            }

        // Subtraction
        } else if (strncmp(node->children[0].value, "-", node->children[0].value_len) == 0) {
            Value left = interpret_node(&node->children[1]);
            Value right = interpret_node(&node->children[2]);

            if (left.type == VALUE_NUMBER && right.type == VALUE_NUMBER) {
                result.type = VALUE_NUMBER;
                result.number_value = left.number_value - right.number_value;
            } else {
                // Error: Invalid types for subtraction
                result.type = VALUE_ERROR;
            }

        // Multiplication
        } else if (strncmp(node->children[0].value, "*", node->children[0].value_len) == 0) {
            Value left = interpret_node(&node->children[1]);
            Value right = interpret_node(&node->children[2]);

            if (left.type == VALUE_NUMBER && right.type == VALUE_NUMBER) {
                result.type = VALUE_NUMBER;
                result.number_value = left.number_value * right.number_value;
            } else {
                // Error: Invalid types for multiplication
                result.type = VALUE_ERROR;
            }

        // Division
        } else if (strncmp(node->children[0].value, "/", node->children[0].value_len) == 0) {
            Value left = interpret_node(&node->children[1]);
            Value right = interpret_node(&node->children[2]);

            if (left.type == VALUE_NUMBER && right.type == VALUE_NUMBER) {
                if (right.number_value != 0) {
                    result.type = VALUE_NUMBER;
                    result.number_value = left.number_value / right.number_value;
                } else {
                    // Error: Division by zero
                    result.type = VALUE_ERROR;
                }
            } else {
                // Error: Invalid types for division
                result.type = VALUE_ERROR;
            }
        } else {
            // Error: Unrecognized function
            result.type = VALUE_ERROR;
        }
    } else {
        // Error: Invalid node type
        result.type = VALUE_ERROR;
    }

    return result;
}

// Print the value of a Value struct as a string
void print_value(const Value *value, char *result_str) {
    switch (value->type) {
        case VALUE_NUMBER:
            // Convert number value to string representation
            snprintf(result_str, 32, "%f", value->number_value);
            break;
        case VALUE_BOOL:
            // Convert boolean value to string representation
            snprintf(result_str, 32, value->bool_value ? "T" : "F");
            break;
        case VALUE_STRING:
            // Print string value with quotes
            snprintf(result_str, 32, "'%s'", value->string_value);
            break;
        case VALUE_ERROR:
            // Print error value as 'ERROR'
            snprintf(result_str, 32, "'ERROR'");
            break;
        case VALUE_NONE:
            // Print none value as 'NONE'
            snprintf(result_str, 32, "NONE");
            break;
        default:
            // Print unknown value types as '_'
            snprintf(result_str, 32, "_");
    }
}
