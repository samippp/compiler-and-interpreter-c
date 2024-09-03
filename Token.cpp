#include "Token.h"
#include <string>

EmptyTokenStackException::EmptyTokenStackException(const std::string &msg) : message(msg) {}
const char* EmptyTokenStackException::what() const throw(){return message.c_str();}
TokenNode::TokenNode(Token data):data(data), next(nullptr){};
Token TokenNode::getData(){return this->data;}
TokenNode *TokenNode::getNext(){return this->next;}
void TokenNode::setNext(TokenNode *n) {this->next = n;}
TokenReverseStack::~TokenReverseStack(){
    while(!this->isEmpty()){
        this->next();
    }
}
TokenReverseStack::TokenReverseStack():first(nullptr),tail(nullptr){}
TokenReverseStack::TokenReverseStack(TokenReverseStack &tokens){
    this->first = tokens.first;
    this->tail = tokens.tail;
}
bool TokenReverseStack::isEmpty() {return (this->first == nullptr);}
Token TokenReverseStack::getfirst(){
    if(this->isEmpty())
        throw EmptyTokenStackException("List is empty.");
    return (*this->first).getData();
}
Token TokenReverseStack::peekNext(){
    if(this->isEmpty())
        throw EmptyTokenStackException("List is empty.");
    if(this->first->getNext() != nullptr)
        return this->first->getNext()->getData();
    else
        throw EmptyTokenStackException("List is empty.");
}
Token TokenReverseStack::getTail(){return (*this->tail).getData();}
void TokenReverseStack::append(Token t){
    TokenNode *newNode = new TokenNode(t);
    if(this->isEmpty()){
        this->first = newNode;
        this->tail = first;
    }
    else{
        this->tail->setNext(newNode);
        this->tail = this->tail->getNext();
    }
}
void TokenReverseStack::next(){
    if(this->isEmpty())
        return;
    TokenNode *temp = first;
    first = (*first).getNext();
    delete temp;
}
