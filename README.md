# Cuild (Syntax Highlight [here](https://github.com/jukeliv/Cuild-Highlight))
a simple Build System for C and C++ made to gain knowledge about Lexers and Parsers

## HOW 2 USE CUILD??? ( see the example in `example` for more )
the way it works is by setting this parameters:
`PROJ`, `STD`, `CC`, `FLAGS` and `FILES`

`PROJ` -- Output file name

`STD` -- Standard C/C++ library version

`CC` -- C Compiler

`FLAGS` -- Compiler flags ( you just need to insert them as they are called, no need for adding "-")

`FILES` -- Source files going to be compiled

to set any of these you need to do something like this:
PROJ: test

this would set `PROJ` as `test`

( this only sets the variable to the value you write, but for other things like `FLAGS` or `FILES` it concatenates that string to it, kinda strange but i like it so i ain't changing it )

# EXAMPLE!!!
``` cuild
PROJ: test
CC: clang
STD: c11

FILES: main.c

FLAGS: Wall
```

##  OUPUT: ( to compile on the terminal, you need to have cuild somewhere and call `cuild`)
`clang main.c -o test.exe -Wall`