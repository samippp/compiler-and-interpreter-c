#ifndef AST
#define AST
#include "Token.h"
#include <vector>

class Function_node;
class Statement_node;
class Expression;
class Operator;

//Program Node
class Program_node{
    std::vector<Function_node> functions;
    TokenReverseStack &tokens;
    public:
        Program_node(TokenReverseStack& tokens);
        void printProgram();
        std::vector<Function_node> getFunctions();
};
//Function Node
class Function_node{
    std::string name;
    std::vector<Statement_node> statements;
    public:
        Function_node(std::string name);
        void printFunctionNode();
        std::vector<Statement_node> getStatements();
        std::string getName();

};

class Operator{
    public:
        void virtual printOp()const;
        virtual ~Operator();
};
//Expression Node
class Expression_node{
    Operator *op;
    public:
        Expression_node(Operator *op);
        ~Expression_node();
        void printExpression_node() const;
        Operator *getOperand();
};
//Statement node
class Statement_node{
    Expression_node exp; 
    public:
        Statement_node(Expression_node exp);
        void printStatement_node();
        Expression_node getExpression();
};

//Operators
class Uni_Operator : public Operator{
    Tokentype op;
    Expression_node *exp;
    public:
        Uni_Operator(Tokentype op, Expression_node *exp);
        ~Uni_Operator() override;
        void printOp() const override;
        Tokentype getOp();
        
};
class constant : public Operator{
    int c;
    public:
        constant(int c);
        ~constant() override;
        int getConst();
        void printOp() const override;
};


#endif
