#include <iostream>
#include "lexer.h"
#include "tree.h"
#include "Token.h"
#include "parser.h"
#include <fstream>
#include <string>

Expression_node *parse_factor(TokenReverseStack &tokens){
    Token e = tokens.getfirst();
    if(e.type ==3){
        tokens.next();
        Expression_node *exp = parse_expression(tokens);
        if(tokens.getfirst().type != 4)
            throw;
        tokens.next();
        return exp;
    }
    if(e.type == 9){
        Expression_node *exp = new Expression_node(new constant(std::stoi(e.value)));
        tokens.next();
        return exp;
    }
    else if(e.type == 10){
        tokens.next();
        Expression_node *exp = new Expression_node(new Uni_Operator(Tokentype::Negation));
        return parse_factor(tokens,exp,exp);
    }
    else if(e.type==11){
        tokens.next();
        Expression_node *exp = new Expression_node(new Uni_Operator(Tokentype::Bitwise_complement));
        return parse_factor(tokens,exp,exp);
    }
    else if(e.type==12){
        tokens.next();
        Expression_node *exp = new Expression_node(new Uni_Operator(Tokentype::Logical_negation));
        return parse_factor(tokens,exp,exp);
    }
    else{
        return new Expression_node(nullptr);
    }
}//tail recurs
Expression_node *parse_factor(TokenReverseStack &tokens, Expression_node *start, Expression_node *tail){
    Token e = tokens.getfirst();
    if(e.type == 9){
        Expression_node *exp = new Expression_node(new constant(std::stoi(e.value)));
        tail->getOperand()->setExp(exp);
        tokens.next();
        return start;
    }
    else if(e.type == 10){
        tokens.next();
        Expression_node *exp = new Expression_node(new Uni_Operator(Tokentype::Negation));
        tail->getOperand()->setExp(exp);
        return parse_factor(tokens,start,exp);
    }
    else if(e.type==11){
        tokens.next();
        Expression_node *exp = new Expression_node(new Uni_Operator(Tokentype::Bitwise_complement));
        tail->getOperand()->setExp(exp);
        return parse_factor(tokens,start,exp);
    }
    else if(e.type==12){
        tokens.next();
        Expression_node *exp = new Expression_node(new Uni_Operator(Tokentype::Logical_negation));
        tail->getOperand()->setExp(exp);
        return parse_factor(tokens,start,exp);
    }
    else if(e.type==13){
        tokens.next();
        Expression_node *exp = new Expression_node(new Bin_Operator(Tokentype::Addition,start));
        return parse_factor(tokens,exp,exp);
    }
    else
        throw;
    
}
Expression_node *parse_term(TokenReverseStack &tokens){
    Expression_node *term = parse_factor(tokens);
    if(tokens.getfirst().type != 15 && tokens.getfirst().type != 14)
        return term;

    Token e = tokens.getfirst();
    
    while(e.type == 14 || e.type == 15){
        if(e.type == 14){
            tokens.next();

            term = new Expression_node(new Bin_Operator(Tokentype::Multiplication,term, parse_factor(tokens)));
        }
        else if(e.type ==15){
            tokens.next();
            term = new Expression_node(new Bin_Operator(Tokentype::Division, term, parse_factor(tokens)));
        }
        e = tokens.getfirst();
    }

    return term;
}
Expression_node *parse_expression(TokenReverseStack &tokens){
    Expression_node *term = parse_term(tokens);
    if(tokens.getfirst().type != 13 && tokens.getfirst().type != 10)
        return term;
    
    Token e = tokens.getfirst();
    while(e.type == 13 || e.type == 10){
        if(e.type == 13){
            tokens.next();          
            term = new Expression_node(new Bin_Operator(Tokentype::Addition,term, parse_term(tokens)));
        }
        else if(e.type ==10){
            tokens.next();
            term = new Expression_node(new Bin_Operator(Tokentype::Negation, term, parse_term(tokens)));
        }

        e = tokens.getfirst();
    }

    return term;
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
int main(){
    std::ifstream myFile("test.c");
    TokenReverseStack tokens = TokenReverseStack(splitString(myFile));
    myFile.close();
    Expression_node *e = parse_expression(tokens);
    e->printExpression_node();
    return 0;
}
