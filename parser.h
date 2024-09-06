#include "Token.h"
#include "tree.h"

Expression_node *parse_expression(TokenReverseStack &tokens, Operator *start, Operator *tail);
Statement_node *parse_statement(TokenReverseStack &tokens);
Function_node *parse_function(TokenReverseStack &tokens);
Program_node *parse_program(TokenReverseStack &tokens);