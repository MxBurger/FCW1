/*Calc.l:                                            HDO, 2006-2015
  ------
  Description of the lexical structure for a simple calculator.
====================================================================*/

%{

  #include "Calc.tab.h" /*generated by yacc/bison from Clac.y
                          if option -d is used, defines NUMBER      */

  extern int yylval;    /*lexical attribute for current token       */

%}

%%

[ \t]+   { ; }          /*ignore white space: blanks and tabs       */

[0-9]+   { yylval = atoi(yytext); return NUMBER; }

\n       { return 0; }         /*return logical EOF                 */

.        { return yytext[0]; } /*return all other chars 
                                 as tokens: '+', '-', ...           */

%%

int yywrap() {
  return 1; /*on end of input: no further files to scan             */
} /*yywrap*/

/* End of Calc.l
====================================================================*/