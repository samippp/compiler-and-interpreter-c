#include <iostream>
#include <fstream>
//#include "lexer.h"
#include "tree.h"
#include "Token.h"
#include <string>

int main(int argc, char **argv){
    Operator *c = new constant(5);
    Operator *o= new Uni_Operator(Tokentype::Negation, c);
    Expression_node e = Expression_node(o);
    e.printExpression_node();
    delete o;
    delete c;
    return 0;
}