#include <iostream>
#include <fstream>
#include "Token.h"
#include "tree.h"
#include "lexer.h"
#include "parser.h"
#include <string>

std::string traverseExp(Expression_node *e, std::string res, int label_num){
    if(e->getOperand()->getType() == Tokentype::Integer_literal){
        return "\tmovl\t$"+e->getOperand()->getValue()+", %eax\n\t"+res+"\n";
    }
    else if(e->getOperand()->getType() == Tokentype::Negation && !e->getOperand()->isBinOp()){
        return traverseExp(e->getOperand()->getExp(),res+"neg\t%eax\n\n\t",label_num);
    }
    else if(e->getOperand()->getType() == Tokentype::Bitwise_complement){
        return traverseExp(e->getOperand()->getExp(),res+"not\t%eax\n\t",label_num);
    }
    else if(e->getOperand()->getType() == Tokentype::Logical_negation){
        return traverseExp(e->getOperand()->getExp(),res+"cmpl\t$0, %eax\n\tmovl\t$0, %eax\n\tsete\t%al\n\n\t",label_num);
    }
    else if(e->getOperand()->getType()==Tokentype::Negation){
        std::string exp1 = traverseExp(e->getOperand()->getPairExp().first,"",label_num)+"\n\tpushq\t%rax\n";
        std::string exp2 = traverseExp(e->getOperand()->getPairExp().second,"",label_num)+"\n\tpopq\t%rcx\n\tsubl\t%ecx, %eax\n\t";
        return exp1+exp2;
    }
    else if(e->getOperand()->getType()==Tokentype::Addition){
        std::string exp1 = traverseExp(e->getOperand()->getPairExp().first,"",label_num)+"\n\tpushq\t%rax\n";
        std::string exp2 = traverseExp(e->getOperand()->getPairExp().second,"",label_num)+"\n\tpopq\t%rcx\n\taddl\t%ecx, %eax\n\t";
        return exp1+exp2;
    }
    else if(e->getOperand()->getType()==Tokentype::Multiplication){
        std::string exp1 = traverseExp(e->getOperand()->getPairExp().first,"",label_num)+"\n\tpushq\t%rax\n";
        std::string exp2 = traverseExp(e->getOperand()->getPairExp().second,"",label_num)+"\n\tpopq\t%rcx\n\timul\t%ecx, %eax\n\t";
        return exp1+exp2;
    }
    else if(e->getOperand()->getType()==Tokentype::Division){
        std::string exp2 = traverseExp(e->getOperand()->getPairExp().second,"",label_num)+"\n\tmovl\t%eax, %ebx\n";
        std::string exp1 = traverseExp(e->getOperand()->getPairExp().first,"",label_num)+"\n\tcdq\n\tidivl\t%ebx";
        return exp2+exp1;
    }
    else if(e->getOperand()->getType()==Tokentype::Modulo){
        std::string exp2 = traverseExp(e->getOperand()->getPairExp().second,"",label_num)+"\n\tmovl\t%eax, %ebx\n";
        std::string exp1 = traverseExp(e->getOperand()->getPairExp().first,"",label_num)+"\n\tcdq\n\tidivl\t%ebx\n\tmovq\t%rdx, %rax";
        return exp2+exp1;
    }
    else if(e->getOperand()->getType()>= 18 && e->getOperand()->getType()<=23){
        std::string set_cmd;
        if(e->getOperand()->getType() == 18)
            set_cmd = "sete";
        else if(e->getOperand()->getType() == 19)
            set_cmd = "setne";
        else if(e->getOperand()->getType() == 20)
            set_cmd = "setl";
        else if(e->getOperand()->getType() == 21)
            set_cmd = "setle";
        else if(e->getOperand()->getType() == 22)
            set_cmd = "setg";
        else if(e->getOperand()->getType() == 23)
            set_cmd = "setge";
        std::string exp1 = traverseExp(e->getOperand()->getPairExp().first,"",label_num)+"\n\tpushq\t%rax\n";
        std::string exp2 = traverseExp(e->getOperand()->getPairExp().second,"",label_num)+"\n\tpopq\t%rcx\n\tcmpl\t%eax, %ecx\n\tmovl\t$0,%eax\n\t"+set_cmd+"\t%al\n";
        return exp1+exp2;
    }
    else if(e->getOperand()->getType() == Tokentype::OR){
        std::string label = "end"+std::to_string(label_num);
        label_num++;
        std::string exp1 = traverseExp(e->getOperand()->getPairExp().first,"",label_num)+"\n\tcmpl\t$0, %eax\n\tmovq\t$0, %rax\n\tsetne\t%al\n\tjne\t"+label+"\n";
        std::string exp2 = traverseExp(e->getOperand()->getPairExp().second,"",label_num)+"cmpl\t$0, %eax\n\tsetne\t%al\n\t\n"+label+":\n\t";  
        return exp1+exp2;
    }
    else if(e->getOperand()->getType() == Tokentype::AND){
        std::string label = "end"+std::to_string(label_num);
        label_num++;
        std::string exp1 = traverseExp(e->getOperand()->getPairExp().first,"",label_num)+"\n\tcmpl\t$0, %eax\n\tmovq\t$0, %rax\n\tsetne\t%al\n\tje\t"+label+"\n";
        std::string exp2 = traverseExp(e->getOperand()->getPairExp().second,"",label_num)+"\tcmpl\t$0, %eax\n\tsetne\t%al\n\t\n"+label+":\n\t";  
        return exp1+exp2;
    }
    
        perror("NOERMOEWMROWEMR");
        return "merow";
    
}

int main(int argc, char **argv){
        
    std::ifstream myFile("test.c");
    TokenReverseStack tokens = TokenReverseStack(splitString(myFile));
    myFile.close();
    
    Program_node *p = parse_program(tokens);
    std::string header_assembly = "\t.text";
    std::string function_assmebly = "";
    for(Function_node *f : p->getFunctions()){
        header_assembly+="\n\t.globl _"+f->getName()+"\n";
        function_assmebly+="_"+f->getName()+":\n";
        for(Statement_node *s : f->getStatements()){
            s->getExpression()->printExpression_node();
            function_assmebly+=traverseExp(s->getExpression(),"",0)+"\n\tret";
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