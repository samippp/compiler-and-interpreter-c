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
    else
        return Token({curr,Tokentype::Identitfier});
}

TokenReverseStack splitString(std::ifstream &myFile){
    TokenReverseStack tokens = TokenReverseStack();
    std::string line;
    if(myFile.is_open()){
        char c;
        bool isNum = true;
        while(myFile.get(c)){
            if (c!=' ' && c!='\n'){
                if(isalnum(c) != 0 || c == '_'){
                    line += c;
                    if(c < 48 || c > 57)
                        isNum = false;

                }
                else if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';' || c=='-'||c=='~'||c=='!'){
                    if(line.empty())
                        line.clear();
                    else{
                        tokens.append(addToTokens(line,isNum));
                        line.clear();
                    }
                    line +=c;
                    tokens.append(addToTokens(line,false));
                    line.clear();
                    isNum = true;
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

