#pragma once

#include <vector>
#include "utility.hpp"

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

TokenType KEYWORD(std::string word)
{
    if(word == "CC")
    {
        return CCOMPILER;
    }
    else if(word == "PROJ")
    {
        return PROJECTNAME;
    }
    else if(word == "LIB")
    {
        return LIBRARY;
    }
    else if(word == "FILES")
    {
        return CFILE;
    }
    else if(word == "FLAGS")
    {
        return FLAGS;
    }

    return ERROR;
}

bool Tokenize(std::vector<Token>& list, std::string sourceCode)
{
    char lex[256];
    int lexi = 0;

    int i = 0;
    while(sourceCode[i] != '\0')
    {
        zero(lex, 256);

        if(is_space(sourceCode[i]))
        {
            while(is_space(sourceCode[i]))
                i++;
        }

        switch(sourceCode[i])
        {
            case '[':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, OPEN));
                break;
                
            case ']':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, CLOSE));
                break;

            case ',':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, COMMA));
                break;

            case ':':
                lex[0] = sourceCode[i++];
                list.push_back(Token(lex, COLON));
                break;
            default:    // HANDLE MULTIPLE-CHARACTER TOKENS
                if(isalnum(sourceCode[i]) || sourceCode[i] == '.')
                {
                    while(isalnum(sourceCode[i]) || sourceCode[i] == '.')
                        lex[lexi++] = sourceCode[i++];

                    if(KEYWORD(lex) == ERROR)
                        list.push_back(Token(lex, ID));
                    else
                        list.push_back(Token(lex, KEYWORD(lex)));

                    lexi = 0;
                    continue;
                }
                /*
                else if(sourceCode[i] == '\0')
                {
                    lex[0] = '\0';
                    list.push_back(Token(lex, OPEN));
                    return true;
                    break;
                }*/
                else if(sourceCode[i] != '\0')
                {
                    fprintf(stderr, "Unknown character found in Cuil file: \"%c\" %i\n", sourceCode[i], i);
                    return false;
                }
                break;
        }
    }
    return true;
}