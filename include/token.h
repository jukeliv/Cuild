#pragma once

#include <vector>
#include <string>
#include "utility.h"

#ifndef VER
    #define VER "1.0.0(RELEASE)"
#endif
#ifndef TARGET
    #define TARGET "Win"
#endif

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
    //REGULAR KEYWORDS
    ID,         //7
    COLON,      //8
    COMMA,      //9
    OPEN,       //10
    CLOSE,      //11
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