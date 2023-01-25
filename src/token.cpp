#include "../include/token.h"

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

bool Tokenize(std::vector<Token>& list, const char* path)
{
    std::string sourceCode = read(path);
    char lex[256];
    int lexi = 0;

    int i = 0;
    while(sourceCode[i] != '\0')
    {
        while(sourceCode[i] == ' ' || sourceCode[i] == '\t' || sourceCode[i] == '\n')
            i++;
        
        memset(lex, 0, 256);

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
                if(isalnum(sourceCode[i]) || sourceCode[i] == '+' || sourceCode[i] == '_')
                {
                    while(isalnum(sourceCode[i]) || sourceCode[i] == '.'  || sourceCode[i] == '+' || sourceCode[i] == '_')
                        lex[lexi++] = sourceCode[i++];

                    if(KEYWORD(lex) == ERROR)
                        list.push_back(Token(lex, ID));
                    else
                        list.push_back(Token(lex, KEYWORD(lex)));

                    lexi = 0;
                    continue;
                }
                else if(sourceCode[i] != '\0')
                {
                    fprintf(stderr, "Unknown character found in Cuild file: \"%c\" %i\n", sourceCode[i], i);
                    return false;
                }
                break;
        }
    }
    return true;
}