#include <stdlib.h>
#include "utility.h"
#include "token.h"

int main(int argc, char** argv)
{
    std::string project_name;
    std::string c_compiler;
    std::string c_files;
    std::string compiler_flags;


    std::vector<Token> list;
    
    if(!Tokenize(list, read("CuilFile")))
        exit(-1);

    size_t i = 0;
    while(i < list.size())
    {
        if(list[i].type == PROJECTNAME){
            if(list[i+1].type != COLON)
            {
                fprintf(stderr, "Can't call \"PROJ\" for something that is not setting it\n");
                exit(-2);
            }
            if(list[i+2].type != ID)
            {
                fprintf(stderr, "Can't set \"PROJ\" to a non-usable value\n");
                exit(-3);
            }

            project_name = list[i+2].value;
            i+=2;
            continue;
        }

        if(list[i].type == CCOMPILER){
            if(list[i+1].type != COLON)
            {
                fprintf(stderr, "Can't call \"CC\" for something that is not setting it\n");
                exit(-2);
            }
            if(list[i+2].type != ID)
            {
                fprintf(stderr, "Can't set \"CC\" to a non-usable value\n");
                exit(-3);
            }

            c_compiler = list[i+2].value;
            i+=2;
            continue;
        }

        if(list[i].type == FLAGS){
            if(list[i+1].type != COLON)
            {
                fprintf(stderr, "Can't call \"FLAGS\" for something that is not setting it\n");
                exit(-2);
            }
            if(list[i+2].type != ID)
            {
                fprintf(stderr, "Can't set \"FLAGS\" to a non-usable value\n");
                exit(-3);
            }
            
            compiler_flags += " -" + list[i+2].value;
            
            i+=2;
            continue;
        }

        if(list[i].type == CFILE){
            if(list[i+1].type != COLON)
            {
                fprintf(stderr, "Can't call \"FILES\" for something that is not setting it\n");
                exit(-2);
            }
            if(list[i+2].type != ID)
            {
                fprintf(stderr, "Can't set \"FILES\" to a non-usable value\n");
                exit(-3);
            }
            
            c_files += " " + list[i+2].value;
            
            i+=2;
            continue;
        }
        i++;
    }

    //clang main.c -o test.exe
    std::string command;
    command += c_compiler;
    command += c_files;
    command += " -o ";
    command += project_name + ".exe";
    command += compiler_flags;

    printf("%s\n", command.c_str());
    system(command.c_str());

    return 0;
}