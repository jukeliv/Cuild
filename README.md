### Cuild
a simple Build System for C and C++ made to gain knowledge about Lexers and Parsers

## HOW 2 USE CUILD???
the way it works is by setting this parameters:
PROJ, CC, FLAGS and FILES

PROJ -- Output file name
CC -- C Compiler
FLAGS -- Compiler flags ( you just need to insert them as they are called, no need for adding "-")
FILES -- Source files going to be compiled

to set any of these you need to do something like this:
PROJ: test

this would set PROJ as "test" and it would compile as "test.exe"

( this only sets the variable but for other things like FLAGS or FILES it adds that string to it, kinda strange but i like it so i ain't changing it )

# EXAMPLE!!!
PROJ: test
CC: clang
FILES: main.c
FLAGS: Wall

##  OUPUT:
clang main.c -o test.exe -Wall