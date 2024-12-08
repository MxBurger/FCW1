%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;
extern int yylex();
extern int yyparse();
extern FILE *yyin;
extern char* yytext;
extern char id_name[];  /* Declared in scanner */

void yyerror(const char *s);

/* Data structures for function call graph */
#define MAX_FUNCS 100
#define MAX_CALLS 1000
#define MAX_NAME 64

/**
 * Function information structure
 * defined: 1 if function is defined, 0 if only declared
 */
typedef struct {
    char name[MAX_NAME];
    int defined;
} Function;

/**
 * Function call edge information structure
 * represents a directed edge in the call graph
 */
typedef struct {
    char caller[MAX_NAME];
    char callee[MAX_NAME];
} FunctionCall;

/* Global state variables */
Function functions[MAX_FUNCS];          /* Array of all functions */
FunctionCall calls[MAX_CALLS];          /* Array of all function calls */
int num_functions = 0;                  /* Number of functions found */
int num_calls = 0;                      /* Number of calls found */
char current_function[MAX_NAME] = "";   /* Currently analyzed function */

void add_function(const char* name, int defined) {
    if (num_functions >= MAX_FUNCS) {
        fprintf(stderr, "Too many functions!\n");
        return;
    }
    
    /* Check if function already exists */
    for (int i = 0; i < num_functions; i++) {
        if (strcmp(functions[i].name, name) == 0) {
            if (defined) functions[i].defined = 1;
            return;
        }
    }
    
    strcpy(functions[num_functions].name, name);
    functions[num_functions].defined = defined;
    num_functions++;
}

void add_call(const char* callee) {
    if (num_calls >= MAX_CALLS || strlen(current_function) == 0) {
        return;
    }
    
    /* Don't add self-calls or empty names */
    if (strlen(callee) == 0) {
        return;
    }
    
    /* Avoid duplicate calls */
    for (int i = 0; i < num_calls; i++) {
        if (strcmp(calls[i].caller, current_function) == 0 &&
            strcmp(calls[i].callee, callee) == 0) {
            return;
        }
    }
    
    strcpy(calls[num_calls].caller, current_function);
    strcpy(calls[num_calls].callee, callee);
    num_calls++;
}

void generate_graph() {
    FILE *f = fopen("callgraph.gv", "w");
    if (!f) return;
    
    fprintf(f, "digraph CallGraph {\n");
    fprintf(f, "  rankdir=LR;\n");
    fprintf(f, "  node [shape=box];\n\n");
    
    /* Create nodes for all functions */
    for (int i = 0; i < num_functions; i++) {
        if (functions[i].defined) {
            fprintf(f, "  \"%s\" [style=filled,fillcolor=lightblue];\n", 
                   functions[i].name);
        } else {
            fprintf(f, "  \"%s\" [style=dashed];\n", functions[i].name);
        }
    }
    
    fprintf(f, "\n");
    
    /* Create edges for all calls */
    for (int i = 0; i < num_calls; i++) {
        fprintf(f, "  \"%s\" -> \"%s\";\n", 
               calls[i].caller, calls[i].callee);
    }
    
    fprintf(f, "}\n");
    fclose(f);
}

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
            {
                add_function(id_name, 0); /* Add as declaration */
            }
            ;

FuncDef     : FuncHead
            {
                add_function(id_name, 1);  /* Add as defined */
                strncpy(current_function, id_name, MAX_NAME-1);
            }
              Block
            {
                current_function[0] = '\0';
            }
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
            | OptInc IDENT
            {
                /* Store callee name */
                  char callee[MAX_NAME];
                  strncpy(callee, id_name, MAX_NAME-1);
                  callee[MAX_NAME-1] = '\0';
                  if (strlen(current_function) > 0) {  /* If we're inside a function */
                      add_call(callee);  /* Add the call */
                  }
            }
              '(' OptActParams ')'
              OptPostInc
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
        generate_graph();
        printf("Call graph written to callgraph.gv\n");
    }
    return 0;
}