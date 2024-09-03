#include "Token.h"
#include "tree.h"
#include <vector>
#include <string>
#include <iterator>
#include <iostream>

//Program node
Program_node::Program_node(TokenReverseStack& tokens):tokens(tokens){
}

void Program_node::printProgram(){
    std::cout<<"Program\n|\n";
    for(Function_node x: this->functions)
        x.printFunctionNode();
}

//Function Node
Function_node::Function_node(std::string name):name(name){}
void Function_node::printFunctionNode(){
    std::cout<<this->name<<"\n|\n";
    for(Statement_node x: this->statements)
        x.printStatement_node();
}


//Expression Node
Expression_node::Expression_node(Operator *op):op(op){}

void Expression_node::printExpression_node() const{op->printOp();}

//Statement Node
Statement_node::Statement_node(Expression_node exp):exp(exp){}

void Statement_node::printStatement_node(){
    std::cout<<"Return\n|\n";
    this->exp.printExpression_node();
}

//Operators
Operator::~Operator(){}

//Uni Operator
Uni_Operator::~Uni_Operator(){
    delete exp->getOperand();
}
Uni_Operator::Uni_Operator(Tokentype op, Expression_node exp): op(op),exp(&exp){}
void Operator::printOp()const {
    std::cout<<"merow";
}
void Uni_Operator::printOp() const{
    if(op == 10)
        std::cout<<"-";
    else if(op == 11)
        std::cout<<"~";
    else if(op ==12)
        std::cout<<"!";
    
    std::cout<<"\n|\n";
    exp->printExpression_node();
}
constant::constant(int c):c(c){}
constant::~constant(){}
//getters
std::vector<Function_node> Program_node::getFunctions(){
    return functions;
}
std::string Function_node::getName(){return this->name;}
std::vector<Statement_node> Function_node::getStatements(){
    return statements;
}
Expression_node Statement_node::getExpression(){
    return exp;
}
Operator *Expression_node::getOperand(){
    return op;
}
int constant::getConst(){
    return c;
}
void constant::printOp() const{
    std::cout<<c;
}
Tokentype Uni_Operator::getOp(){
    return this->op;
}


