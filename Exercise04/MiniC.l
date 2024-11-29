/*MiniC.l:                                            HDO, 2006-2015
  -------
  Lex/Flex description for MiniC.
====================================================================*/

/*instead of function yywrap that returns 1:                        */
%option noyywrap 

%{

  #include "MiniC.tab.h" /*generated with "bison -d MiniC.y"        */

  extern int yylineno;   /*current line number, initalized with 1   */
  extern int yylval;     /*lexical attribute for current token      */

%}

%%

[ \t]+      { ; }        /*ignore white space: blanks and tabs      */

\n          { yylineno++; }

int         { return INT;    }
main        { return MAIN;   }
printf      { return PRINTF; }
scanf       { return SCANF;  }
void        { return VOID;   }

[a-zA-Z][a-zA-Z0-9]* { return IDENT; }

[0-9]+      { yylval = atoi(yytext); return NUMBER; }


.           { return yytext[0]; } /*return all other chars 
                                    as tokens to parser: '+', ...   */

%%

/* End of MiniC.l
====================================================================*/
