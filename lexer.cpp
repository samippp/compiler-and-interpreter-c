#include <fstream>
#include <vector>
#include <cstdio>
#include "Token.h"
#include <cctype>
#include "lexer.h"

Token addToTokens(std::string curr, bool isNum){
    if(curr == "{")
        return Token{curr,Tokentype::Open_brace};
    else if(curr == "}")
        return Token{curr,Tokentype::Close_brace};
    else if(curr == "(")
        return Token{curr,Tokentype::Open_parenthesis};
    else if(curr == ")")
        return Token{curr,Tokentype::Close_parenthesis};
    else if(curr == ";")
        return Token{curr,Tokentype::Semicolon};
    else if(curr == "return")
        return Token{curr,Tokentype::Return_keyword};
    else if(curr == "int")
        return Token{curr,Tokentype::Int_keyword};
    else if(isNum)
        return Token{curr,Tokentype::Integer_literal};
    else if(curr=="-")
        return Token{curr, Tokentype::Negation};
    else if(curr=="~") 
        return Token{curr,Tokentype::Bitwise_complement};
    else if(curr=="!")
        return Token{curr, Tokentype::Logical_negation};
    else if(curr=="+")
        return Token{curr,Tokentype::Addition};
    else if(curr=="*")
        return Token{curr,Tokentype::Multiplication};
    else if(curr=="/")
        return Token{curr,Tokentype::Division};
    else if(curr=="&&")
        return Token{curr,Tokentype::AND};
    else if(curr=="||")
        return Token{curr,Tokentype::OR};
    else if(curr=="=")
        return Token{curr,Tokentype::Assignment};
    else if(curr=="==")
        return Token{curr,Tokentype::Equal};
    else if(curr=="!=")
        return Token{curr,Tokentype::Not_Equal};
    else if(curr=="<")
        return Token{curr,Tokentype::Less};
    else if(curr=="<=")
        return Token{curr,Tokentype::Less_equal};
    else if(curr==">")
        return Token{curr,Tokentype::Greater};
    else if(curr==">=")
        return Token{curr,Tokentype::Greater_equal};
    else if(curr=="%")
        return Token{curr,Tokentype::Modulo};
    else
        return Token({curr,Tokentype::Identitfier});
}
bool isNullC(char c){
    return c==' ' || c=='\n';
}
TokenReverseStack splitString(std::ifstream &myFile){
    TokenReverseStack tokens;
    std::string line;
    if(myFile.is_open()){
        char c;
        bool isNum = true;
        while(myFile.get(c)){
            if (!isNullC(c)){
                if(isalnum(c) != 0 || c == '_'){
                    line += c;
                    if(c < 48 || c > 57)
                        isNum = false;
                }
                else if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';' || c=='-'||c=='~'||
                        c=='+'||c=='*'||c=='/'||c=='%'){
                    
                    if(line.empty())
                        line.clear();
                    else{
                        tokens.append(addToTokens(line,isNum));
                        line.clear();
                    }
                    line += c;
                    tokens.append(addToTokens(line,false));
                    isNum = true;
                    line.clear();
                }
                else if(c == '&'||c=='|' || c=='='||c=='<'||c=='>'|| c=='!'){
                    if(line.empty())
                        line.clear();
                    else{
                        tokens.append(addToTokens(line,isNum));
                        line.clear();
                    }
                    char b;
                    myFile.get(b);
                    if(c=='!'){
                        if(b=='=')
                            tokens.append(addToTokens("!=",false));
                        else {
                            tokens.append(addToTokens("!",false));
                            if(!isNullC(b))
                                line += b;
                        }
                    }
                    else if(c=='&'){
                        if(b=='&')
                            tokens.append(addToTokens("&&",false));
                        else {
                            throw;
                        }
                    }
                    else if(c=='|'){
                        if(b=='|')
                            tokens.append(addToTokens("||",false));
                        else {
                            throw;
                        }
                    }
                    else if(c=='='){
                        if(b=='=')
                            tokens.append(addToTokens("==",false));
                        else{
                            tokens.append(addToTokens("=",false));
                            if(!isNullC(b))
                                line+=b;
                        }
                    }
                    else if(c=='<'){
                        if(b=='=')
                            tokens.append(addToTokens("<=",false));
                        else {
                            tokens.append(addToTokens("<",false));
                            if(!isNullC(b))
                                line +=b;
                        }
                    }
                    else if(c=='>'){
                        if(b=='=')
                            tokens.append(addToTokens(">=",false));
                        else{
                            tokens.append(addToTokens(">",false));
                            if(!isNullC(b))
                                line+=b;
                        }
                    }
                    else if(c=='!'){
                        if(b=='=')
                            tokens.append(addToTokens("!=",false));
                        else{
                            tokens.append(addToTokens("!",false));
                            if(!isNullC(b))
                                line+=b;
                        }
                    }
                    else
                        throw;
                }
            }
            else{
                if(line.empty())
                    line.clear();
                else{
                    tokens.append(addToTokens(line,isNum));
                    line.clear();
                }
                isNum=true;
            }
        }
    }
    else
        perror("NOIOO");
        
    
    return tokens;
}       

