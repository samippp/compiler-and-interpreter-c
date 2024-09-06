#include "Token.h"
#include "tree.h"
#include <vector>
#include <string>
#include <iterator>
#include <iostream>

//Program node
Program_node::Program_node(){}
Program_node::~Program_node(){
    while(!functions.empty()){
        delete functions.back();
        functions.back() = nullptr;
        functions.pop_back();
    }
}
void Program_node::appendToFunctions(Function_node *f){
    functions.emplace_back(f);
}

void Program_node::printProgram(){
    std::cout<<"Program\n|\n";
    for(Function_node *x: this->functions)
        x->printFunctionNode();
}

//Function Node
Function_node::Function_node(std::string name):name(name){}
Function_node::~Function_node(){
    while(!statements.empty()){
        delete statements.back();
        statements.back() = nullptr;
        statements.pop_back();
    }
}
void Function_node::printFunctionNode(){
    std::cout<<this->name<<"\n|\n";
    for(Statement_node *x: this->statements)
        x->printStatement_node();
}
void Function_node::pushStatement(Statement_node *s){
    statements.emplace_back(s);
}

//Expression Node
Expression_node::Expression_node(Operator *op):op(op){}
Expression_node::Expression_node():op(nullptr){}
Expression_node::~Expression_node(){
    if(op != nullptr){
        std::cout<<"deleteing ";
        op->printOp();
        std::cout<<"\n";
        delete op;
    }
    op = nullptr;
}
void Expression_node::printExpression_node() const{op->printOp();}
void Expression_node::setExp(Operator *op){
    this->op = op;
}
//Statement Node
Statement_node::Statement_node(Expression_node *exp):exp(exp){}
Statement_node::~Statement_node(){
    if(exp != nullptr){
        std::cout<<"Deleting ";
        this->printStatement_node();
        std::cout<<'\n';
        delete exp;
    }
    exp = nullptr;
}
void Statement_node::printStatement_node(){
    std::cout<<"Return\n|\n";
    exp->printExpression_node();
}

//Operators
Operator::~Operator(){}

//Uni Operator
Uni_Operator::~Uni_Operator(){
    delete exp;
    exp = nullptr;
}
Uni_Operator::Uni_Operator(Tokentype op, Expression_node *exp): op(op),exp(exp){}
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
//Bin_operator 
Bin_Operator::Bin_Operator(Expression_node *exp1, Expression_node *exp2):exp1(exp1),exp2(exp2){}
Bin_Operator::~Bin_Operator(){
    delete exp1;
    exp1 = nullptr;
    delete exp2; 
    exp2 = nullptr;
}
void Bin_Operator::printOp() const{
    if(op == 13)
        std::cout<<"+";
    else if(op == 14)
        std::cout<<"*";
    else if(op ==15)
        std::cout<<"/";
    std::cout<<"\n|\n";
    exp1->printExpression_node();
    exp2->printExpression_node();
}
Tokentype Bin_Operator::getType() const{
    return op;
}
std::pair<Expression_node*,Expression_node*> Bin_Operator::getPairExp() const{
    return {exp1, exp2};
}
//constant
constant::constant(int c):c(c){}
constant::~constant(){}
//getters
std::vector<Function_node*> Program_node::getFunctions(){
    return functions;
}
std::string Function_node::getName(){return this->name;}
std::vector<Statement_node*> Function_node::getStatements(){
    return statements;
}
Expression_node *Statement_node::getExpression(){
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
Tokentype constant::getType() const{
    return Tokentype::Integer_literal;
}
Tokentype Uni_Operator::getType() const{
    return op;
}
std::string constant::getValue() const{
    return std::to_string(c);
}
Expression_node *Uni_Operator::getExp() const{
    return exp;
}
Expression_node *constant::getExp() const{
    return nullptr;
}

