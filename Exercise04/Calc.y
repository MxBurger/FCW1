/*Calc.y:                                             HDO, 2006-2015
  ------
  Attributed grammar for a simple calculator.
====================================================================*/

%{

  #include <stdio.h> /* for printf                                  */

  /*int yylval; holds default lexical attribute for current token   */

%}

%token NUMBER

%%

Calc: Expr         { printf("%d\n", $1);  }
  ;
  
Expr: Term         { $$ = $1; /*default*/ }
  | Expr '+' Term  { $$ = $1 + $3;        }
  | Expr '-' Term  { $$ = $1 - $3;        }
  ;

Term: Fact         { $$ = $1; /*default*/ }
  | Term '*' Fact  { $$ = $1 * $3;        }
  | Term '/' Fact  { $$ = $1 / $3;        }
  ;
  
Fact: NUMBER       { $$ = $1; /*default*/ }
  | '(' Expr ')'   { $$ = $2;             }
  ;
 
%%

int yyerror(char *msg) {
  printf("error: %s\n", msg);
  return 0;
} /*yyerror*/

int main(int argc, char *argv[]) {
  yyparse();
  return 0;
} /*main*/


/* End of Calc.y
====================================================================*/