#include "token.h"

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
        memset(lex, 0, 256);

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