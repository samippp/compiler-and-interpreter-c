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
    std::vector<Function_node*> functions;
    public:
        Program_node();
        ~Program_node();
        void printProgram();
        std::vector<Function_node*> getFunctions();
        void appendToFunctions(Function_node *f);
};
//Function Node
class Function_node{
    std::string name;
    std::vector<Statement_node*> statements;
    public:
        Function_node(std::string name);
        ~Function_node();
        void printFunctionNode();
        std::vector<Statement_node*> getStatements();
        std::string getName();
        void pushStatement(Statement_node *s);

};

//Expression Node
class Expression_node{
    Operator *op;
    public:
        Expression_node(Operator *op);
        Expression_node();
        ~Expression_node();
        void printExpression_node() const;
        Operator *getOperand();
        void setOp(Operator *op);
};
//Statement node
class Statement_node{
    Expression_node *exp; 
    public:
        Statement_node(Expression_node *exp);
        ~Statement_node();
        void printStatement_node();
        Expression_node *getExpression();
};

//Operators
class Operator{
    public:
        void virtual printOp()const{}
        virtual ~Operator(){}
        void virtual setExp(Expression_node *exp){}
        Tokentype virtual getType() const{}
        std::string virtual getValue() const{}
        Expression_node virtual *getExp() const{}
        std::pair<Expression_node*,Expression_node*> virtual getPairExp() const{};
};
class Uni_Operator : public Operator{
    Tokentype op;
    Expression_node *exp;
    public:
        Uni_Operator(Tokentype op, Expression_node *exp);
        Uni_Operator(Tokentype op);
        ~Uni_Operator() override;
        void printOp() const override;
        Tokentype getType() const override;
        Expression_node *getExp() const;
        void setExp(Expression_node *exp) override;
        
};
class Bin_Operator : public Operator{
    Tokentype op;
    Expression_node *exp1;
    Expression_node *exp2;
    public:
        Bin_Operator(Tokentype op);
        Bin_Operator(Tokentype op,Expression_node *exp1, Expression_node *exp2);
        Bin_Operator(Tokentype op, Expression_node *exp1);
        ~Bin_Operator() override;
        void printOp() const override;
        Tokentype getType() const override;
        void setExp1(Expression_node *exp1);
        void setExp2(Expression_node *exp2);
        std::pair<Expression_node*,Expression_node*> virtual getPairExp() const override;
};
class constant : public Operator{
    int c;
    public:
        constant(int c);
        ~constant() override;
        int getConst();
        void printOp() const override;
        Tokentype getType() const override;
        std::string getValue() const override;
        Expression_node *getExp() const override;
};


#endif
