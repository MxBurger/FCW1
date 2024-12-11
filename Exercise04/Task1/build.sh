#!/bin/bash

flex MiniC.l
bison -d -v -g -Wcounterexamples MiniC.y
gcc lex.yy.c MiniC.tab.c -o MiniC
./MiniC < SVP.mc
