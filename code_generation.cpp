#include <iostream>
#include <fstream>
#include "Token.h"
#include "tree.h"
#include "lexer.h"
#include "parser.h"

std::string traverseExp(Expression_node *e, std::string res){
    if(e->getOperand()->getType() == Tokentype::Integer_literal){
        return "\tmovl\t$"+e->getOperand()->getValue()+", %eax\n\n\t"+res+"ret\n";
    }
    else if(e->getOperand()->getType() == Tokentype::Negation){
        return traverseExp(e->getOperand()->getExp(),res+"neg\t%eax\n\n\t");
    }
    else if(e->getOperand()->getType() == Tokentype::Bitwise_complement){
        return traverseExp(e->getOperand()->getExp(),res+"not\t%eax\n\n\t");
    }
    else if(e->getOperand()->getType() == Tokentype::Logical_negation){
        return traverseExp(e->getOperand()->getExp(),res+"cmpl\t$0, %eax\n\tmovl\t$0, %eax\n\tsete\t%al\n\n\t");
    }
}

int main(int argc, char **argv){
        
    std::ifstream myFile("test.c");
    TokenReverseStack tokens = TokenReverseStack(splitString(myFile));
    myFile.close();

    
    Program_node *p = parse_program(tokens);
    std::string header_assembly = "\t.text";
    std::string function_assmebly = "";
    for(Function_node *f : p->getFunctions()){
        header_assembly+="\n\t.globl "+f->getName()+"\n";
        function_assmebly+=f->getName()+":\n";
        for(Statement_node *s : f->getStatements()){
            function_assmebly+=traverseExp(s->getExpression(),"");
        }
        function_assmebly+="\n";
    }
    delete p;
    
    std::ofstream file;
    
    file.open("meow.S");
    
    file<<header_assembly;
    file<<function_assmebly;
    
    myFile.close();
    return 0;
}