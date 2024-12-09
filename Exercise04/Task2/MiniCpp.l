%option noyywrap

%{
#include "MiniCpp.tab.h"
extern int yylineno;   /*current line number, initalized with 1   */
%}

%%

[ \t\r]+    { ; }  /* ignore whitespace */
\n          { yylineno++; }

"/*"        {  /* skip C-style comments */
              int c;
              while((c = input()) != EOF) {
                if(c == '\n') 
                  yylineno++;
                else if(c == '*') {
                  if((c = input()) == '/')
                    break;
                  else
                    unput(c);
                }
              }
            }

"//"        {  /* skip C++ style comments */
              int c;
              while((c = input()) != EOF && c != '\n') 
                ;
              if(c == '\n') 
                yylineno++;
            }

"bool"      { return BOOL; }
"break"     { return BREAK; }
"cin"       { return CIN; }
"const"     { return CONST; }
"cout"      { return COUT; }
"delete"    { return DELETE; }
"else"      { return ELSE; }
"endl"      { return ENDL; }
"false"     { return FALSE; }
"if"        { return IF; }
"int"       { return INT; }
"new"       { return NEW; }
"nullptr"   { return NULLPTR; }
"return"    { return RETURN; }
"true"      { return TRUE; }
"void"      { return VOID; }
"while"     { return WHILE; }

[a-zA-Z][a-zA-Z0-9]*  { yylval.strval = strdup(yytext); return IDENT; }

[0-9]+      { yylval.intval = atoi(yytext); return NUMBER; }

\"[^\"]*\"  { return STRING; }  /* string literals */

"<<"        { return SHL; }
">>"        { return SHR; }
"+="        { return PLUSEQ; }
"-="        { return MINUSEQ; }
"*="        { return TIMESEQ; }
"/="        { return DIVEQ; }
"%="        { return MODEQ; }
"=="        { return EQ; }
"!="        { return NEQ; }
"<="        { return LEQ; }
">="        { return GEQ; }
"&&"        { return AND; }
"||"        { return OR; }
"++"        { return INC; }
"--"        { return DEC; }

[-+*/%=<>!&|(){}\[\];,]  { return yytext[0]; }

.           { printf("Unrecognized character: %s\n", yytext); }

%%