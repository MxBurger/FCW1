/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_MINICPP_TAB_H_INCLUDED
# define YY_YY_MINICPP_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    BOOL = 258,                    /* BOOL  */
    BREAK = 259,                   /* BREAK  */
    CIN = 260,                     /* CIN  */
    CONST = 261,                   /* CONST  */
    COUT = 262,                    /* COUT  */
    DELETE = 263,                  /* DELETE  */
    ELSE = 264,                    /* ELSE  */
    ENDL = 265,                    /* ENDL  */
    FALSE = 266,                   /* FALSE  */
    IF = 267,                      /* IF  */
    INT = 268,                     /* INT  */
    NEW = 269,                     /* NEW  */
    NULLPTR = 270,                 /* NULLPTR  */
    RETURN = 271,                  /* RETURN  */
    STRING = 272,                  /* STRING  */
    TRUE = 273,                    /* TRUE  */
    VOID = 274,                    /* VOID  */
    WHILE = 275,                   /* WHILE  */
    IDENT = 276,                   /* IDENT  */
    NUMBER = 277,                  /* NUMBER  */
    SHL = 278,                     /* SHL  */
    SHR = 279,                     /* SHR  */
    PLUSEQ = 280,                  /* PLUSEQ  */
    MINUSEQ = 281,                 /* MINUSEQ  */
    TIMESEQ = 282,                 /* TIMESEQ  */
    DIVEQ = 283,                   /* DIVEQ  */
    MODEQ = 284,                   /* MODEQ  */
    EQ = 285,                      /* EQ  */
    NEQ = 286,                     /* NEQ  */
    LEQ = 287,                     /* LEQ  */
    GEQ = 288,                     /* GEQ  */
    AND = 289,                     /* AND  */
    OR = 290,                      /* OR  */
    INC = 291,                     /* INC  */
    DEC = 292,                     /* DEC  */
    LOWER_THAN_ELSE = 293          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MINICPP_TAB_H_INCLUDED  */
