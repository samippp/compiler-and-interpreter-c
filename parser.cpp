#include <iostream>
#include "lexer.h"
#include "tree.h"
#include <fstream>
#include "Token.h"
#include <string>


Expression_node *parse_expression(TokenReverseStack &tokens){
    Token e = tokens.getfirst();
    if(e.type == 9){
        return new Expression_node(new constant(std::stoi(e.value)));
    }
    else if(e.type == 10){
        tokens.next();
        return new Expression_node(new Uni_Operator(Tokentype::Negation,parse_expression(tokens)));
        std::cout<<"nega\n";
    }
    else if(e.type==11){
        tokens.next();
        return new Expression_node(new Uni_Operator(Tokentype::Bitwise_complement,parse_expression(tokens)));
    }
    else if(e.type==12){
        tokens.next();
        return new Expression_node(new Uni_Operator(Tokentype::Logical_negation,parse_expression(tokens)));
        std::cout<<"nega\n";
    }
    else{
        return new Expression_node(nullptr);
    }
}/*
Statement_node parse_statement(TokenReverseStack &tokens){
    if(tokens.getfirst().type != 7)
        perror("Not Return Lla");
    tokens.next();
    Statement_node s = Statement_node(parse_expression(tokens));
    tokens.next();
    if(tokens.getfirst().type != 5)
        perror("Expected Semicolon");
    tokens.next();
    return s;
}

Function_node parse_function(TokenReverseStack& tokens){
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
    Function_node fn = Function_node(indentifier);
    while(!tokens.isEmpty() || tokens.getfirst().type != 2)
        parse_statement(tokens);
    //if(tokens.isEmpty())
        
    
}*/
int main(int argc, char **argv){
        
    std::ifstream myFile("test.cpp");
    TokenReverseStack tokens = TokenReverseStack(splitString(myFile));
    myFile.close();

    Expression_node *e = parse_expression(tokens);

    e->printExpression_node();
    /*
    Program_node p = Program_node(tokens);
    std::vector<Function_node> fn = p.getFunctions();
    std::string function_decl = "";
    std::string func_body = "";
    std::ofstream output;
    output.open("meow.s");
    output << function_decl;
    output << func_body+"\n";*/
    return 0;
}