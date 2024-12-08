%{
#include <stdio.h>
#include <stdlib.h>

extern int yylineno;
extern int yylex();
extern int yyparse();
extern FILE *yyin;

void yyerror(const char *s);
%}

%token BOOL BREAK CIN CONST COUT DELETE ELSE ENDL FALSE IF INT
%token NEW NULLPTR RETURN STRING TRUE VOID WHILE
%token IDENT NUMBER
%token SHL SHR PLUSEQ MINUSEQ TIMESEQ DIVEQ MODEQ
%token EQ NEQ LEQ GEQ AND OR INC DEC

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

MiniCpp     : /* empty */
            | MiniCpp TopLevel
            ;

TopLevel    : ConstDef
            | VarDef
            | FuncDecl
            | FuncDef
            | ';'
            ;

ConstDef    : CONST Type IdentInit ';'
            ;

IdentInit   : IDENT Init
            | IdentInit ',' IDENT Init
            ;

Init        : '=' InitValue
            ;

InitValue   : FALSE
            | TRUE
            | NULLPTR
            | OptSign NUMBER
            ;

OptSign     : /* empty */
            | '+'
            | '-'
            ;

VarDef      : Type VarList ';'
            ;

VarList     : VarItem
            | VarList ',' VarItem
            ;

VarItem     : OptPointer IDENT OptInit
            ;

OptPointer  : /* empty */
            | '*'
            ;

OptInit     : /* empty */
            | Init
            ;

FuncDecl    : FuncHead ';'
            ;

FuncDef     : FuncHead Block
            ;

FuncHead    : Type OptPointer IDENT '(' OptFormParList ')'
            ;

OptFormParList : /* empty */
               | FormParList
               ;

FormParList : VOID
            | ParamDef
            | FormParList ',' ParamDef
            ;

ParamDef    : Type OptPointer IDENT OptArray
            ;

OptArray    : /* empty */
            | '[' ']'
            ;

Type        : VOID
            | BOOL
            | INT
            ;

Block       : '{' BlockItems '}'
            ;

BlockItems  : /* empty */
            | BlockItems BlockItem
            ;

BlockItem   : ConstDef
            | VarDef
            | Stat
            ;

Stat        : EmptyStat
            | BlockStat
            | ExprStat
            | IfStat
            | WhileStat
            | BreakStat
            | InputStat
            | OutputStat
            | DeleteStat
            | ReturnStat
            ;

EmptyStat   : ';'
            ;

BlockStat   : Block
            ;

ExprStat    : Expr ';'
            ;

IfStat      : IF '(' Expr ')' Stat              %prec LOWER_THAN_ELSE
            | IF '(' Expr ')' Stat ELSE Stat
            ;

WhileStat   : WHILE '(' Expr ')' Stat
            ;

BreakStat   : BREAK ';'
            ;

InputStat   : CIN SHR IDENT ';'
            ;

OutputStat  : COUT OutList ';'
            ;

OutList     : SHL OutExpr
            | OutList SHL OutExpr
            ;

OutExpr     : Expr
            | STRING
            | ENDL
            ;

DeleteStat  : DELETE '[' ']' IDENT ';'
            ;

ReturnStat  : RETURN OptExpr ';'
            ;

OptExpr     : /* empty */
            | Expr
            ;

Expr        : OrExpr
            | OrExpr AssignOp OrExpr
            ;

AssignOp    : '='
            | PLUSEQ
            | MINUSEQ
            | TIMESEQ
            | DIVEQ
            | MODEQ
            ;

OrExpr      : AndExpr
            | OrExpr OR AndExpr
            ;

AndExpr     : RelExpr
            | AndExpr AND RelExpr
            ;

RelExpr     : SimpleExpr
            | RelExpr RelOp SimpleExpr
            ;

RelOp       : EQ
            | NEQ
            | '<'
            | LEQ
            | '>'
            | GEQ
            ;

SimpleExpr  : OptSign Term
            | SimpleExpr AddOp Term
            ;

AddOp       : '+'
            | '-'
            ;

Term        : NotFact
            | Term MulOp NotFact
            ;

MulOp       : '*'
            | '/'
            | '%'
            ;

NotFact     : Fact
            | '!' Fact
            ;

Fact        : FALSE
            | TRUE
            | NULLPTR
            | NUMBER
            | LValue
            | NEW Type '[' Expr ']'
            | '(' Expr ')'
            ;

LValue      : OptInc IDENT OptPostInc
            | OptInc IDENT '[' Expr ']' OptPostInc
            | OptInc IDENT '(' OptActParams ')' OptPostInc
            ;

OptInc      : /* empty */
            | INC
            | DEC
            ;

OptPostInc  : /* empty */
            | INC
            | DEC
            ;

OptActParams: /* empty */
            | ActParams
            ;

ActParams   : Expr
            | ActParams ',' Expr
            ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return 1;
        }
    }

    if (yyparse() == 0) {
        printf("lines parsed: %d\n", yylineno);
        printf("Parsing completed successfully\n");
    }
    return 0;
}