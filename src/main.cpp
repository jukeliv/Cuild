#include <stdlib.h>
#include "../include/token.h"

int main(int argc, char** argv)
{
    std::string project_name;
    std::string ext = ".out";
    std::string c_compiler;
    std::string c_files;
    std::string compiler_flags;

    if(argc > 1)
    {
        if(!strcmp(argv[1], "-Win") || !strcmp(argv[1], "-Windows") || !strcmp(argv[1], "-windows"))// 
            ext = ".exe";
        else if(!strcmp(argv[1], "-h") || !strcmp(argv[1], "-help") || !strcmp(argv[1], "-H"))
        {
            printf("%s\n", "LINE COMMANDS:\n-Win: Set the target to Windows ( just add \"exe\" as the file extension )\n-h: Help command\n\nCUILD FILE:\nPROJ: Executable file's name\nCC: C/C++ Compiler\nFLAGS: Compiler flags ( every time you set it, it concatenates the flags to a string, not just sets it)\nFILES: Source files going to compile ( concatenates the same as `FLAGS` )");
            return 0;
        }
    }

    std::vector<Token> list;
    
    if(!Tokenize(list, "CuildFile"))
        return -1;

    size_t i = 0;
    while(i < list.size())
    {
        if(list[i].type == PROJECTNAME){
            if(list[i+1].type != COLON)
            {
                fprintf(stderr, "Can't call \"PROJ\" for something that is not setting it\n");
                return -1;
            }
            if(list[i+2].type != ID)
            {
                fprintf(stderr, "Can't set \"PROJ\" to a non-usable value\n");
                return -1;
            }

            project_name = list[i+2].value;
            i+=2;
            continue;
        }

        if(list[i].type == CCOMPILER){
            if(list[i+1].type != COLON)
            {
                fprintf(stderr, "Can't call \"CC\" for something that is not setting it\n");
                return -1;
            }
            if(list[i+2].type != ID)
            {
                fprintf(stderr, "Can't set \"CC\" to a non-usable value\n");
                return -1;
            }

            c_compiler = list[i+2].value;
            i+=2;
            continue;
        }

        if(list[i].type == FLAGS){
            if(list[i+1].type != COLON)
            {
                fprintf(stderr, "Can't call \"FLAGS\" for something that is not setting it\n");
                return -1;
            }
            if(list[i+2].type != ID)
            {
                fprintf(stderr, "Can't set \"FLAGS\" to a non-usable value\n");
                return -1;
            }
            
            compiler_flags += " -" + list[i+2].value;
            
            i+=2;
            continue;
        }

        if(list[i].type == CFILE){
            if(list[i+1].type != COLON)
            {
                fprintf(stderr, "Can't call \"FILES\" for something that is not setting it\n");
                return -1;
            }
            if(list[i+2].type != ID)
            {
                fprintf(stderr, "Can't set \"FILES\" to a non-usable value\n");
                return -1;
            }
            
            c_files += list[i+2].value + " ";
            
            i+=2;
            continue;
        }
        i++;
    }
    if(c_compiler.empty() || c_files.empty() || project_name.empty())
    {
        fprintf(stderr, "Check mate, you forgot to add somme of these 3:\n");
        printf("\"CC\" | \"PROJ\" \"FILES\"");
        return -1;
    }

    std::string command;
    command += c_compiler + " ";
    command += c_files;
    command += "-o ";
    command += project_name + ext;
    command += compiler_flags;

    printf("%s\n", command.c_str());
    system(command.c_str());

    return 0;
}
