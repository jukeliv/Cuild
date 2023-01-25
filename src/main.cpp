#include <stdlib.h>
#include "../include/bd.h"
#include "../include/token.h"

int main(int argc, char** argv)
{
    std::string cuild_file = "make";
    std::string std_lib_version = "";
    std::string project_name;
    std::string ext = ".out";
    if(!strcmp(TARGET, "Win"))
        ext=".exe";

    std::string c_compiler;
    std::vector<std::string> c_files;
    std::string compiler_flags;
    std::string obj_folder;
    std::string libraries;

    if(argc > 1)
    {
        if(!strcmp(argv[1], "-h") || !strcmp(argv[1], "-help") || !strcmp(argv[1], "-H"))
        {
            printf("Cuild: %s\n\n", build_data().c_str());
            printf("%s\n", "PROJ: Executable file's name\nCC: C/C++ Compiler\nFLAGS: Compiler flags ( every time you set it, it concatenates the flags to a string, not just sets it)\nFILES: Source files going to compile ( concatenates the same as `FLAGS` )\nSTD: Standard library version\nOBJS: path where the .o files are stored");
            return 0;
        }
        else
        {
            cuild_file = argv[1];
        }
    }

    std::vector<Token> list;
    
    if(!Tokenize(list, (cuild_file + ".CuildFile").c_str()))
        return -1;

    size_t i = 0;
    while(i < list.size())
    {
        if(list[i].type == STD){
            if(!std_lib_version.empty())
            {
                fprintf(stderr, "Can't re-set the value of \"STD\"");
                return -1;
            }
            if(list[i+1].type != COLON)
            {
                fprintf(stderr, "Can't call \"STD\" for something that is not setting it\n");
                return -1;
            }
            if(list[i+2].type != ID)
            {
                fprintf(stderr, "Can't set \"STD\" to a non-usable value\n");
                return -1;
            }

            std_lib_version = " -std=" + list[i+2].value;
            i+=2;
            continue;
        }

        if(list[i].type == PROJECTNAME){
            if(!project_name.empty())
            {
                fprintf(stderr, "Can't re-set the value of \"PROJ\"");
                return -1;
            }
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
            if(!c_compiler.empty())
            {
                fprintf(stderr, "Can't re-set the value of \"CC\"");
                return -1;
            }
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

        if(list[i].type == LIBRARY){
            if(list[i+1].type != COLON)
            {
                fprintf(stderr, "Can't call \"LIB\" for something that is not setting it\n");
                return -1;
            }
            if(list[i+2].type != ID)
            {
                fprintf(stderr, "Can't set \"LIB\" to a non-usable value\n");
                return -1;
            }
            
            i+=2;

            if(list[i+1].type != COMMA)
            {
                libraries += " -l" + list[i+2].value;
                continue;
            }
            
            libraries += " -L " + list[i+2].value + " -l " + list[i].value;
            
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
            
            c_files.push_back(list[i+2].value);
            
            i+=2;
            continue;
        }

        if(list[i].type == OBJS){
            if(list[i+1].type != COLON)
            {
                fprintf(stderr, "Can't call \"OBJS\" for something that is not setting it\n");
                return -1;
            }
            if(list[i+2].type != ID)
            {
                fprintf(stderr, "Can't set \"OBJS\" to a non-usable value\n");
                return -1;
            }
            
            obj_folder = list[i+2].value;
            
            i+=2;
            continue;
        }
        i++;
    }
    if(c_compiler.empty())
    {
        fprintf(stderr, "Check mate, you forgot to give \"CC\" a value!!!");
        return -1;
    }
    else if(c_files.empty()) // IF 0 is empty, there is nothing here ( but if it is empty, 0 doesn't exist and it crashes )
    {
        fprintf(stderr, "Check mate, you forgot to give \"FILES\" a value!!!");
        return -1;
    }
    else if(project_name.empty())
    {
        fprintf(stderr, "Check mate, you forgot to give \"PROJ\" a value!!!");
        return -1;
    }

    for( int i = 0; i < c_files.size(); i++)
    {
        std::string command;
        command += c_compiler + " -c ";
        command += c_files[i];

        if(!obj_folder.empty())
        {
            std::string obj = c_files[i];
            obj.pop_back();
            obj.push_back('o');
            command += " -o " + obj_folder + "/" + obj;
        }
        printf("%s\n", command.c_str());
        system(command.c_str());
    }

    std::string command = c_compiler + " ";
    for(int i = 0; i < c_files.size(); i++)
    {
        std::string file = c_files[i];
        file.pop_back();
        file.push_back('o');
        if(!obj_folder.empty())
            command += (obj_folder + "/" + file + " ");
        else
            command += (file + " ").c_str();
    }

    command += "-o ";
    command += project_name + ext;
    command += std_lib_version;
    command += compiler_flags;
    command += libraries;

    printf("%s\n", command.c_str());
    system(command.c_str());

    return 0;
}