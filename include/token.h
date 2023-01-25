#pragma once

#include <vector>
#include <string>
#include "utility.h"

typedef enum _TokenType
{
    //RESERVED KEYWORDS
    ERROR,      //0
    CCOMPILER,  //1
    PROJECTNAME,//2
    LIBRARY,    //3
    COMPILE,    //4
    FLAGS,      //5
    CFILE,      //6
    STD,        //7
    OBJS,       //8
    //REGULAR KEYWORDS
    ID,         //9
    COLON,      //10
    COMMA,      //11
    OPEN,       //12
    CLOSE,      //13
}TokenType;

class Token
{
public:
    Token(std::string val, TokenType type)
    :value(val), type(type){}

    std::string value;
    TokenType type;
};

TokenType KEYWORD(std::string word);

bool Tokenize(std::vector<Token>& list, const char* sourceCode);