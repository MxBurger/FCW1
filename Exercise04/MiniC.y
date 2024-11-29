/*MiniC.y:                                            HDO, 2006-2015
  -------
  Yacc/Bison attributed grammar for MinC.
====================================================================*/

%{

  #include <stdio.h>
  #include <stdlib.h>

  extern int yylineno;  /*current line number, initalized with 1    */
  extern int yylval;    /*lexical attribute for current token       */

%}

%token INT
%token MAIN
%token PRINTF
%token SCANF
%token VOID

%token IDENT
%token NUMBER

%%

MC:
  VOID MAIN '(' ')' Block
  ;
  
Block:
  '{' OptVarDecl StatSeq '}'
  ;
  
OptVarDecl:
     /*epsilon*/
  |  INT IdList ';'
  ;
  
IdList:
    IDENT
  | IdList ',' IDENT
  ;
  
StatSeq:
    /*epsilon*/
  | StatSeq Stat
  ;
  
Stat:
    IDENT '=' Expr       ';'
  | SCANF  '(' IDENT ')' ';'
  | PRINTF '(' Expr  ')' ';'
  ;
  
Expr: 
    Term         
  | Expr '+' Term  
  | Expr '-' Term  
  ;

Term: 
    Fact         
  | Term '*' Fact  
  | Term '/' Fact  
  ;
  
Fact: 
    IDENT
  | NUMBER
  | '(' Expr ')'   
  ;
 
%%

extern FILE *yyin;     /*file to parse, stdin per default*/

int yyerror(char *msg) {
  printf("ERROR: %s in line %d\n", msg, yylineno);
  return 0;
} /*yyerror*/

int main(int argc, char *argv[]) {
  if (argc > 1) {
    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL) {
      printf("ERROR: file %s not found\n", argv[1]);
      exit(-1);
    } /*if*/
    yyin = fin;
  } /*if*/
  yyparse();
  yylex_destroy();     /*free memory allocated by scanner*/
  printf("lines parsed: %d\n", yylineno);
  return 0;
} /*main*/


/* End of MiniC.y
====================================================================*/
