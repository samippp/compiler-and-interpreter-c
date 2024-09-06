#include <iostream>
#include "lexer.h"
#include "tree.h"
#include "Token.h"
#include "parser.h"
#include <fstream>
#include <string>


Expression_node *parse_expression(TokenReverseStack &tokens){
    Token e = tokens.getfirst();
    if(e.type == 9){
        return new Expression_node(new constant(std::stoi(e.value)));
    }
    else if(e.type == 10){
        tokens.next();
        return new Expression_node(new Uni_Operator(Tokentype::Negation,parse_expression(tokens)));
    }
    else if(e.type==11){
        tokens.next();
        return new Expression_node(new Uni_Operator(Tokentype::Bitwise_complement,parse_expression(tokens)));
    }
    else if(e.type==12){
        tokens.next();
        return new Expression_node(new Uni_Operator(Tokentype::Logical_negation,parse_expression(tokens)));
    }
    else{
        return new Expression_node(nullptr);
    }
}
Statement_node *parse_statement(TokenReverseStack &tokens){
    if(tokens.getfirst().type != 7)
        perror("Not Return Llaaa");
    tokens.next();
    Statement_node *s = new Statement_node(parse_expression(tokens));
    tokens.next();
    if(tokens.getfirst().type != 5)
        perror("Expected Semicolon");
    tokens.next();
    return s;
}

Function_node *parse_function(TokenReverseStack& tokens){
    if(tokens.getfirst().type != 6)
        perror("Wrong keyword. Only Accepting Int at the momenet :D");
    tokens.next();
    if(tokens.getfirst().type != 8)
        perror("Not a valid indentifier");
    std::string indentifier = tokens.getfirst().value;
    tokens.next();
    if(tokens.getfirst().type != 3)
        perror("Missing open parenthesis");
    tokens.next();
    if(tokens.getfirst().type != 4)
        perror("Missing closing parenthesis");
    tokens.next();
    if(tokens.getfirst().type != 1)
        perror("Missing open bracket");
    tokens.next();
    Function_node *fn = new Function_node(indentifier);
    while(!tokens.isEmpty() && tokens.getfirst().type != 2){
        fn->pushStatement(parse_statement(tokens));
    }
    if(tokens.getfirst().type != 2)
        perror("Expected Closing Bracket");
    tokens.next();
    return fn;
    
}
Program_node *parse_program(TokenReverseStack &tokens){
    Program_node *p = new Program_node();
    while(!tokens.isEmpty())
        p->appendToFunctions(parse_function(tokens));
    return p;
}
