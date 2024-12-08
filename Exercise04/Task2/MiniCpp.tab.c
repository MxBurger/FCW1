/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "MiniCpp.y"

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


#line 189 "MiniCpp.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "MiniCpp.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_BOOL = 3,                       /* BOOL  */
  YYSYMBOL_BREAK = 4,                      /* BREAK  */
  YYSYMBOL_CIN = 5,                        /* CIN  */
  YYSYMBOL_CONST = 6,                      /* CONST  */
  YYSYMBOL_COUT = 7,                       /* COUT  */
  YYSYMBOL_DELETE = 8,                     /* DELETE  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_ENDL = 10,                      /* ENDL  */
  YYSYMBOL_FALSE = 11,                     /* FALSE  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_INT = 13,                       /* INT  */
  YYSYMBOL_NEW = 14,                       /* NEW  */
  YYSYMBOL_NULLPTR = 15,                   /* NULLPTR  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_STRING = 17,                    /* STRING  */
  YYSYMBOL_TRUE = 18,                      /* TRUE  */
  YYSYMBOL_VOID = 19,                      /* VOID  */
  YYSYMBOL_WHILE = 20,                     /* WHILE  */
  YYSYMBOL_IDENT = 21,                     /* IDENT  */
  YYSYMBOL_NUMBER = 22,                    /* NUMBER  */
  YYSYMBOL_SHL = 23,                       /* SHL  */
  YYSYMBOL_SHR = 24,                       /* SHR  */
  YYSYMBOL_PLUSEQ = 25,                    /* PLUSEQ  */
  YYSYMBOL_MINUSEQ = 26,                   /* MINUSEQ  */
  YYSYMBOL_TIMESEQ = 27,                   /* TIMESEQ  */
  YYSYMBOL_DIVEQ = 28,                     /* DIVEQ  */
  YYSYMBOL_MODEQ = 29,                     /* MODEQ  */
  YYSYMBOL_EQ = 30,                        /* EQ  */
  YYSYMBOL_NEQ = 31,                       /* NEQ  */
  YYSYMBOL_LEQ = 32,                       /* LEQ  */
  YYSYMBOL_GEQ = 33,                       /* GEQ  */
  YYSYMBOL_AND = 34,                       /* AND  */
  YYSYMBOL_OR = 35,                        /* OR  */
  YYSYMBOL_INC = 36,                       /* INC  */
  YYSYMBOL_DEC = 37,                       /* DEC  */
  YYSYMBOL_LOWER_THAN_ELSE = 38,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_39_ = 39,                       /* ';'  */
  YYSYMBOL_40_ = 40,                       /* ','  */
  YYSYMBOL_41_ = 41,                       /* '='  */
  YYSYMBOL_42_ = 42,                       /* '+'  */
  YYSYMBOL_43_ = 43,                       /* '-'  */
  YYSYMBOL_44_ = 44,                       /* '*'  */
  YYSYMBOL_45_ = 45,                       /* '('  */
  YYSYMBOL_46_ = 46,                       /* ')'  */
  YYSYMBOL_47_ = 47,                       /* '['  */
  YYSYMBOL_48_ = 48,                       /* ']'  */
  YYSYMBOL_49_ = 49,                       /* '{'  */
  YYSYMBOL_50_ = 50,                       /* '}'  */
  YYSYMBOL_51_ = 51,                       /* '<'  */
  YYSYMBOL_52_ = 52,                       /* '>'  */
  YYSYMBOL_53_ = 53,                       /* '/'  */
  YYSYMBOL_54_ = 54,                       /* '%'  */
  YYSYMBOL_55_ = 55,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 56,                  /* $accept  */
  YYSYMBOL_MiniCpp = 57,                   /* MiniCpp  */
  YYSYMBOL_TopLevel = 58,                  /* TopLevel  */
  YYSYMBOL_ConstDef = 59,                  /* ConstDef  */
  YYSYMBOL_IdentInit = 60,                 /* IdentInit  */
  YYSYMBOL_Init = 61,                      /* Init  */
  YYSYMBOL_InitValue = 62,                 /* InitValue  */
  YYSYMBOL_OptSign = 63,                   /* OptSign  */
  YYSYMBOL_VarDef = 64,                    /* VarDef  */
  YYSYMBOL_VarList = 65,                   /* VarList  */
  YYSYMBOL_VarItem = 66,                   /* VarItem  */
  YYSYMBOL_OptPointer = 67,                /* OptPointer  */
  YYSYMBOL_OptInit = 68,                   /* OptInit  */
  YYSYMBOL_FuncDecl = 69,                  /* FuncDecl  */
  YYSYMBOL_FuncDef = 70,                   /* FuncDef  */
  YYSYMBOL_71_1 = 71,                      /* $@1  */
  YYSYMBOL_FuncHead = 72,                  /* FuncHead  */
  YYSYMBOL_OptFormParList = 73,            /* OptFormParList  */
  YYSYMBOL_FormParList = 74,               /* FormParList  */
  YYSYMBOL_ParamDef = 75,                  /* ParamDef  */
  YYSYMBOL_OptArray = 76,                  /* OptArray  */
  YYSYMBOL_Type = 77,                      /* Type  */
  YYSYMBOL_Block = 78,                     /* Block  */
  YYSYMBOL_BlockItems = 79,                /* BlockItems  */
  YYSYMBOL_BlockItem = 80,                 /* BlockItem  */
  YYSYMBOL_Stat = 81,                      /* Stat  */
  YYSYMBOL_EmptyStat = 82,                 /* EmptyStat  */
  YYSYMBOL_BlockStat = 83,                 /* BlockStat  */
  YYSYMBOL_ExprStat = 84,                  /* ExprStat  */
  YYSYMBOL_IfStat = 85,                    /* IfStat  */
  YYSYMBOL_WhileStat = 86,                 /* WhileStat  */
  YYSYMBOL_BreakStat = 87,                 /* BreakStat  */
  YYSYMBOL_InputStat = 88,                 /* InputStat  */
  YYSYMBOL_OutputStat = 89,                /* OutputStat  */
  YYSYMBOL_OutList = 90,                   /* OutList  */
  YYSYMBOL_OutExpr = 91,                   /* OutExpr  */
  YYSYMBOL_DeleteStat = 92,                /* DeleteStat  */
  YYSYMBOL_ReturnStat = 93,                /* ReturnStat  */
  YYSYMBOL_OptExpr = 94,                   /* OptExpr  */
  YYSYMBOL_Expr = 95,                      /* Expr  */
  YYSYMBOL_AssignOp = 96,                  /* AssignOp  */
  YYSYMBOL_OrExpr = 97,                    /* OrExpr  */
  YYSYMBOL_AndExpr = 98,                   /* AndExpr  */
  YYSYMBOL_RelExpr = 99,                   /* RelExpr  */
  YYSYMBOL_RelOp = 100,                    /* RelOp  */
  YYSYMBOL_SimpleExpr = 101,               /* SimpleExpr  */
  YYSYMBOL_AddOp = 102,                    /* AddOp  */
  YYSYMBOL_Term = 103,                     /* Term  */
  YYSYMBOL_MulOp = 104,                    /* MulOp  */
  YYSYMBOL_NotFact = 105,                  /* NotFact  */
  YYSYMBOL_Fact = 106,                     /* Fact  */
  YYSYMBOL_LValue = 107,                   /* LValue  */
  YYSYMBOL_108_2 = 108,                    /* $@2  */
  YYSYMBOL_OptInc = 109,                   /* OptInc  */
  YYSYMBOL_OptPostInc = 110,               /* OptPostInc  */
  YYSYMBOL_OptActParams = 111,             /* OptActParams  */
  YYSYMBOL_ActParams = 112                 /* ActParams  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   183

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  128
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  192

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    55,     2,     2,     2,    54,     2,     2,
      45,    46,    44,    42,    40,    43,     2,    53,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    39,
      51,    41,    52,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    48,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,    50,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   130,   130,   131,   134,   135,   136,   137,   138,   141,
     144,   145,   148,   151,   152,   153,   154,   157,   158,   159,
     162,   165,   166,   169,   172,   173,   176,   177,   180,   187,
     186,   197,   200,   201,   204,   205,   206,   209,   212,   213,
     216,   217,   218,   221,   224,   225,   228,   229,   230,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   245,
     248,   251,   254,   255,   258,   261,   264,   267,   270,   271,
     274,   275,   276,   279,   282,   285,   286,   289,   290,   293,
     294,   295,   296,   297,   298,   301,   302,   305,   306,   309,
     310,   313,   314,   315,   316,   317,   318,   321,   322,   325,
     326,   329,   330,   333,   334,   335,   338,   339,   342,   343,
     344,   345,   346,   347,   348,   351,   352,   354,   353,   367,
     368,   369,   372,   373,   374,   377,   378,   381,   382
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "BOOL", "BREAK", "CIN",
  "CONST", "COUT", "DELETE", "ELSE", "ENDL", "FALSE", "IF", "INT", "NEW",
  "NULLPTR", "RETURN", "STRING", "TRUE", "VOID", "WHILE", "IDENT",
  "NUMBER", "SHL", "SHR", "PLUSEQ", "MINUSEQ", "TIMESEQ", "DIVEQ", "MODEQ",
  "EQ", "NEQ", "LEQ", "GEQ", "AND", "OR", "INC", "DEC", "LOWER_THAN_ELSE",
  "';'", "','", "'='", "'+'", "'-'", "'*'", "'('", "')'", "'['", "']'",
  "'{'", "'}'", "'<'", "'>'", "'/'", "'%'", "'!'", "$accept", "MiniCpp",
  "TopLevel", "ConstDef", "IdentInit", "Init", "InitValue", "OptSign",
  "VarDef", "VarList", "VarItem", "OptPointer", "OptInit", "FuncDecl",
  "FuncDef", "$@1", "FuncHead", "OptFormParList", "FormParList",
  "ParamDef", "OptArray", "Type", "Block", "BlockItems", "BlockItem",
  "Stat", "EmptyStat", "BlockStat", "ExprStat", "IfStat", "WhileStat",
  "BreakStat", "InputStat", "OutputStat", "OutList", "OutExpr",
  "DeleteStat", "ReturnStat", "OptExpr", "Expr", "AssignOp", "OrExpr",
  "AndExpr", "RelExpr", "RelOp", "SimpleExpr", "AddOp", "Term", "MulOp",
  "NotFact", "Fact", "LValue", "$@2", "OptInc", "OptPostInc",
  "OptActParams", "ActParams", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-151)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-126)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -151,    24,  -151,  -151,    57,  -151,  -151,  -151,  -151,  -151,
    -151,  -151,  -151,   -22,   -24,     4,  -151,   -15,  -151,     7,
    -151,    19,    23,    54,  -151,  -151,  -151,   -24,    67,    72,
    -151,  -151,    46,     2,  -151,    51,    94,  -151,  -151,  -151,
    -151,  -151,  -151,  -151,  -151,    88,    23,    56,    78,   113,
      96,   100,    89,   101,  -151,  -151,  -151,    44,  -151,   -24,
    -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,
    -151,  -151,  -151,   105,    92,   114,    73,    80,    23,   -18,
     103,   107,  -151,   -24,  -151,  -151,  -151,   118,     6,    45,
     102,    99,   112,  -151,    99,  -151,    57,  -151,  -151,  -151,
    -151,  -151,    99,    64,   -25,  -151,  -151,  -151,   131,  -151,
    -151,  -151,  -151,  -151,  -151,    99,  -151,    99,    99,  -151,
    -151,  -151,  -151,  -151,  -151,    99,  -151,  -151,    44,  -151,
      57,   132,   115,  -151,  -151,  -151,  -151,     6,  -151,   134,
     110,  -151,   111,   116,   119,  -151,  -151,  -151,  -151,    44,
      93,   114,   123,    73,    80,   -25,  -151,   117,  -151,  -151,
     120,    49,    49,    99,  -151,  -151,  -151,  -151,    99,   121,
    -151,   122,  -151,  -151,   151,  -151,   124,   125,    31,  -151,
      49,  -151,    98,  -151,   128,   127,  -151,  -151,    98,    99,
    -151,  -151
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,    41,     0,    42,    40,     8,     3,     4,
       5,     6,     7,    29,    24,     0,    28,     0,    25,     0,
      21,     0,     0,     0,    44,    30,    20,    24,    26,    17,
      10,     9,     0,    17,    22,     0,    32,    27,    23,    13,
      15,    14,    18,    19,    12,     0,     0,     0,     0,     0,
       0,     0,    17,     0,    59,    43,    46,   119,    47,    24,
      60,    45,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,     0,    77,    85,    87,    89,    26,    34,
       0,    33,    35,    24,    16,    11,    65,     0,    17,     0,
       0,    17,     0,    76,    17,   108,     0,   110,   109,   111,
     120,   121,    17,   119,    97,   101,   106,   112,     0,    61,
      80,    81,    82,    83,    84,    17,    79,    17,    17,    91,
      92,    94,    96,    93,    95,    17,    99,   100,   119,    31,
       0,     0,     0,    72,    71,    68,    70,    17,    67,     0,
       0,    74,     0,     0,     0,   107,   103,   104,   105,   119,
     122,    86,    78,    88,    90,    98,    36,    38,    66,    69,
       0,    17,    17,    17,   114,   102,   123,   124,    17,     0,
     115,     0,    37,    73,    62,    64,     0,     0,    17,    39,
      17,   113,   122,   127,     0,   126,    63,   116,   122,    17,
     118,   128
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -151,  -151,  -151,   129,  -151,   -11,  -151,   139,   136,  -151,
     144,   -12,  -151,  -151,  -151,  -151,  -151,  -151,  -151,    47,
    -151,     0,   158,  -151,  -151,  -149,  -151,  -151,  -151,  -151,
    -151,  -151,  -151,  -151,  -151,    39,  -151,  -151,  -151,   -52,
    -151,    61,    65,    43,  -151,    58,  -151,    53,  -151,    30,
      79,  -151,  -151,  -151,  -150,  -151,  -151
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     8,     9,    23,    37,    44,    57,    10,    19,
      20,    35,    38,    11,    12,    17,    13,    80,    81,    82,
     172,    83,    60,    33,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    89,   135,    71,    72,    92,    73,
     117,    74,    75,    76,   125,    77,   128,   104,   149,   105,
     106,   107,   169,   108,   170,   184,   185
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      93,    14,    21,   -40,    15,     3,    47,    48,     4,    49,
      50,    30,   174,   175,    51,     5,   133,    16,    52,   146,
      18,     6,    53,   134,     2,    22,   -40,     3,   147,   148,
       4,   186,   187,    59,    24,    85,   136,     5,   190,   140,
      28,    54,   142,     6,    42,    43,    26,    27,    42,    43,
     144,    24,    55,    47,    48,    95,    49,    50,    96,    97,
       3,    51,    98,     7,    29,    52,    99,    46,   137,    53,
       5,   131,    78,    42,    43,    95,     6,  -125,    96,    97,
     100,   101,    98,    39,   138,   136,    99,    40,    54,   102,
      41,    42,    43,    31,    32,    86,   143,     3,    24,   103,
     100,   101,    87,   119,   120,   121,   122,     5,    29,   102,
      84,   176,    36,    79,    42,    43,   177,   110,   111,   112,
     113,   114,   126,   127,   123,   124,   183,   115,   -75,   166,
     167,    42,    43,   116,   166,   167,    88,   191,  -117,   132,
     168,    42,    43,    90,   109,    91,    94,   130,   118,   129,
     139,   141,   150,   157,   158,   160,   161,   162,   115,   173,
     180,   153,    56,   163,   171,   164,   178,   189,    45,    58,
     179,    34,   181,   182,   188,    25,   159,   156,   152,   165,
     151,   155,   145,   154
};

static const yytype_uint8 yycheck[] =
{
      52,     1,    14,    21,     4,     3,     4,     5,     6,     7,
       8,    22,   161,   162,    12,    13,    10,    39,    16,    44,
      44,    19,    20,    17,     0,    21,    44,     3,    53,    54,
       6,   180,   182,    33,    49,    46,    88,    13,   188,    91,
      21,    39,    94,    19,    42,    43,    39,    40,    42,    43,
     102,    49,    50,     4,     5,    11,     7,     8,    14,    15,
       3,    12,    18,    39,    41,    16,    22,    21,    23,    20,
      13,    83,    21,    42,    43,    11,    19,    46,    14,    15,
      36,    37,    18,    11,    39,   137,    22,    15,    39,    45,
      18,    42,    43,    39,    40,    39,    96,     3,    49,    55,
      36,    37,    24,    30,    31,    32,    33,    13,    41,    45,
      22,   163,    45,    19,    42,    43,   168,    25,    26,    27,
      28,    29,    42,    43,    51,    52,   178,    35,    39,    36,
      37,    42,    43,    41,    36,    37,    23,   189,    45,    21,
      47,    42,    43,    47,    39,    45,    45,    40,    34,    46,
      48,    39,    21,    21,    39,    21,    46,    46,    35,    39,
       9,   118,    33,    47,    47,    46,    45,    40,    29,    33,
      48,    27,    48,    48,    46,    17,   137,   130,   117,   149,
     115,   128,   103,   125
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    57,     0,     3,     6,    13,    19,    39,    58,    59,
      64,    69,    70,    72,    77,    77,    39,    71,    44,    65,
      66,    67,    21,    60,    49,    78,    39,    40,    21,    41,
      61,    39,    40,    79,    66,    67,    45,    61,    68,    11,
      15,    18,    42,    43,    62,    63,    21,     4,     5,     7,
       8,    12,    16,    20,    39,    50,    59,    63,    64,    77,
      78,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    92,    93,    95,    97,    98,    99,   101,    21,    19,
      73,    74,    75,    77,    22,    61,    39,    24,    23,    90,
      47,    45,    94,    95,    45,    11,    14,    15,    18,    22,
      36,    37,    45,    55,   103,   105,   106,   107,   109,    39,
      25,    26,    27,    28,    29,    35,    41,    96,    34,    30,
      31,    32,    33,    51,    52,   100,    42,    43,   102,    46,
      40,    67,    21,    10,    17,    91,    95,    23,    39,    48,
      95,    39,    95,    77,    95,   106,    44,    53,    54,   104,
      21,    98,    97,    99,   101,   103,    75,    21,    39,    91,
      21,    46,    46,    47,    46,   105,    36,    37,    47,   108,
     110,    47,    76,    39,    81,    81,    95,    95,    45,    48,
       9,    48,    48,    95,   111,   112,    81,   110,    46,    40,
     110,    95
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    56,    57,    57,    58,    58,    58,    58,    58,    59,
      60,    60,    61,    62,    62,    62,    62,    63,    63,    63,
      64,    65,    65,    66,    67,    67,    68,    68,    69,    71,
      70,    72,    73,    73,    74,    74,    74,    75,    76,    76,
      77,    77,    77,    78,    79,    79,    80,    80,    80,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    82,
      83,    84,    85,    85,    86,    87,    88,    89,    90,    90,
      91,    91,    91,    92,    93,    94,    94,    95,    95,    96,
      96,    96,    96,    96,    96,    97,    97,    98,    98,    99,
      99,   100,   100,   100,   100,   100,   100,   101,   101,   102,
     102,   103,   103,   104,   104,   104,   105,   105,   106,   106,
     106,   106,   106,   106,   106,   107,   107,   108,   107,   109,
     109,   109,   110,   110,   110,   111,   111,   112,   112
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     4,
       2,     4,     2,     1,     1,     1,     2,     0,     1,     1,
       3,     1,     3,     3,     0,     1,     0,     1,     2,     0,
       3,     6,     0,     1,     1,     1,     3,     4,     0,     2,
       1,     1,     1,     3,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     5,     7,     5,     2,     4,     3,     2,     3,
       1,     1,     1,     5,     3,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     2,     3,     1,
       1,     1,     3,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     5,     3,     3,     6,     0,     7,     0,
       1,     1,     0,     1,     1,     0,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 28: /* FuncDecl: FuncHead ';'  */
#line 181 "MiniCpp.y"
            {
                add_function(id_name, 0); /* Add as declaration */
            }
#line 1434 "MiniCpp.tab.c"
    break;

  case 29: /* $@1: %empty  */
#line 187 "MiniCpp.y"
            {
                add_function(id_name, 1);  /* Add as defined */
                strncpy(current_function, id_name, MAX_NAME-1);
            }
#line 1443 "MiniCpp.tab.c"
    break;

  case 30: /* FuncDef: FuncHead $@1 Block  */
#line 192 "MiniCpp.y"
            {
                current_function[0] = '\0';
            }
#line 1451 "MiniCpp.tab.c"
    break;

  case 117: /* $@2: %empty  */
#line 354 "MiniCpp.y"
            {
                /* Store callee name */
                  char callee[MAX_NAME];
                  strncpy(callee, id_name, MAX_NAME-1);
                  callee[MAX_NAME-1] = '\0';
                  if (strlen(current_function) > 0) {  /* If we're inside a function */
                      add_call(callee);  /* Add the call */
                  }
            }
#line 1465 "MiniCpp.tab.c"
    break;


#line 1469 "MiniCpp.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 385 "MiniCpp.y"


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
