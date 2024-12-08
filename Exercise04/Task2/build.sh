#!/bin/bash

flex MiniCpp.l
bison -d -v -g -Wcounterexamples MiniCpp.y
gcc lex.yy.c MiniCpp.tab.c -o MiniCpp
./MiniCpp < Sieve.mcpp