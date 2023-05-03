// parser.c
#include "feature/textflow/parser.h"

// Tokenize the input text into a list of tokens
void tokenize(const char *input, Token *tokens, size_t num_tokens) {
    size_t token_index = 0;
    while (*input != '\0') {
        // Skip whitespace
        while (isspace(*input)) {
            input++;
        }

        // If we reach the end of input, break
        if (*input == '\0') {
            break;
        }

        // If we have used all available tokens, break
        if (token_index >= num_tokens) {
            break;
        }

        // Set the start of the token and initialize its length
        tokens[token_index].start = input;
        tokens[token_index].length = 0;

        // Identify the type of the token
        if (*input == '(') {
            tokens[token_index].type = TOKEN_LPAREN;
        } else if (*input == ')') {
            tokens[token_index].type = TOKEN_RPAREN;
        } else {
            tokens[token_index].type = TOKEN_SYMBOL;
            // Increment token length and input pointer for non-whitespace, non-parenthesis characters
            while (!isspace(*input) && *input != '(' && *input != ')' && *input != '\0') {
                tokens[token_index].length++;
                input++;
            }
            input--;
        }

        token_index++;
        input++;
    }

    // Add TOKEN_END to the end of the tokens list
    tokens[token_index].type = TOKEN_END;
}

// Parse a list expression in the form of "(...)"
Node *parse_list(Token **tokens) {
    // Allocate memory for a new node and set its type to TOKEN_LPAREN
    Node *node = malloc(sizeof(Node));
    node->type = TOKEN_LPAREN;
    node->value = (*tokens)->start;
    node->value_len = (*tokens)->length;

    // Allocate memory for the children array and initialize its capacity and number of children
    size_t capacity = 4;
    node->children = malloc(capacity * sizeof(Node));
    node->num_children = 0;

    // Increment the token pointer and parse the children expressions
    (*tokens)++;
    while ((*tokens)->type != TOKEN_RPAREN && (*tokens)->type != TOKEN_END) {
        // Reallocate memory for the children array if needed
        if (node->num_children == capacity) {
            capacity *= 2;
            node->children = realloc(node->children, capacity * sizeof(Node));
        }
        // Parse the expression and add it as a child to the current node
        node->children[node->num_children++] = *parse_expression(tokens);
    }

    // If the token type is TOKEN_RPAREN, increment the token pointer
    if ((*tokens)->type == TOKEN_RPAREN) {
        (*tokens)++;
    }

    return node;
}

// Parse a number or string token
Node *parse_number_or_string(Token **tokens) {
    // Allocate memory for a new node and set its type, value, and value_len
    Node *node = malloc(sizeof(Node));
    node->type = (*tokens)->type;
    node->value = (*tokens)->start;
    node->value_len = (*tokens)->length;
    // Initialize the children array and number of children to NULL and 0
    node->children = NULL;
    node->num_children = 0;

    // Increment the token pointer
    (*tokens)++;
    return node;
}

// Parse an expression, which can be a list, number, or string
Node *parse_expression(Token **tokens) {
    if ((*tokens)->type == TOKEN_LPAREN) {
        return parse_list(tokens);
    } else {
        return parse_number_or_string(tokens);
    }
}

// Parse the input text into an abstract syntax tree
Node *parse(const char *input) {
    Token tokens[128];
    tokenize(input, tokens, sizeof(tokens) / sizeof(tokens[0]));

    Token *tokens_ptr = tokens;
    return parse_expression(&tokens_ptr);
}

// Free the memory used by the abstract syntax tree
void free_tree(Node *node) {
    if (node == NULL) {
        return;
    }

    // Free the memory used by the children nodes
    if (node->children != NULL) {
        for (size_t i = 0; i < node->num_children; i++) {
            free_tree(&node->children[i]);
        }
        free(node->children);
    }

    // Free the memory used by the current node
    free(node);
}

// Print the abstract syntax tree for debugging purposes
void print_tree(const Node *node, int indent) {
    // Print indentation
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }

    // Print the left parenthesis if the node type is TOKEN_LPAREN
    if (node->type == TOKEN_LPAREN) {
        printf("(");
    }

    // Print the node value
    printf("%.*s", (int)node->value_len, node->value);

    // If the node has children, print them recursively
    if (node->num_children > 0) {
        printf(" [\n");
        for (size_t i = 0; i < node->num_children; i++) {
            print_tree(&node->children[i], indent + 1);
            printf("\n");
        }
        // Print the closing bracket for the children array
        for (int i = 0; i < indent; i++) {
            printf("  ");
        }
        printf("]");
    }

    // Print the right parenthesis if the node type is TOKEN_LPAREN
    if (node->type == TOKEN_LPAREN) {
        printf(")");
    }
}
