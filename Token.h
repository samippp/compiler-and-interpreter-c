#ifndef TOKEN_H
#define TOKEN_H
#include <exception>
#include <string>
enum Tokentype{
    Program,//0
    Open_brace,//1
    Close_brace,//2
    Open_parenthesis,//3
    Close_parenthesis,//4
    Semicolon,//5
    Int_keyword,//6
    Return_keyword,//7
    Identitfier,//8
    Integer_literal,//9
    Negation,//10
    Bitwise_complement,//11
    Logical_negation//12
};

struct Token{
    std::string value;
    Tokentype type;
};

class TokenNode{
    Token data;
    TokenNode *next;
    public:
        TokenNode(Token data);
        void setNext(TokenNode *n);
        TokenNode *getNext();
        Token getData();
};

class EmptyTokenStackException : public std::exception{
    std::string message;
    public:
        EmptyTokenStackException(const std::string &msg);
        const char* what() const throw();
};

class TokenReverseStack{
    TokenNode *first;
    TokenNode *tail;
    public:
        TokenReverseStack();
        TokenReverseStack(TokenReverseStack &tokens);
        ~TokenReverseStack();
        bool isEmpty();
        void append(Token t);
        Token getfirst();
        Token getTail();
        void next();
        Token peekNext();
};
#endif 