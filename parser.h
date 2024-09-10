#include "Token.h"
#include "tree.h"

Statement_node *parse_statement(TokenReverseStack &tokens);
Expression_node *parse_factor(TokenReverseStack &tokens);
Expression_node *parse_factor(TokenReverseStack &tokens, Expression_node *start, Expression_node *tail);
Expression_node *parse_term(TokenReverseStack &tokens);
Expression_node *parse_expression(TokenReverseStack &tokens);
Function_node *parse_function(TokenReverseStack &tokens);
Program_node *parse_program(TokenReverseStack &tokens);