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

(\r\n|\n)   { yylineno++; } /*this also supports unix style line-endings*/

"/*"        {            /*skip C comments                          */
              int prevCh = 0, ch = input();
              while (1) {
                if (ch <= 0) { /* EOF == -1 */
                  yyerror("eof within comment"); /*see in MiniC.y   */
                  break;
                } /*if*/
                if (ch == '\n' || ch == '\r\n')
                  yylineno++;
                else if (prevCh == '*' && ch == '/')
                  break; /*ok: correct end of comment               */
                prevCh = ch;
                ch = input();
              } /*while*/
            }


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
