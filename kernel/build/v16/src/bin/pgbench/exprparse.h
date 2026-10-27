/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_EXPR_YY_EXPRPARSE_H_INCLUDED
# define YY_EXPR_YY_EXPRPARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int expr_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NULL_CONST = 258,
    INTEGER_CONST = 259,
    MAXINT_PLUS_ONE_CONST = 260,
    DOUBLE_CONST = 261,
    BOOLEAN_CONST = 262,
    VARIABLE = 263,
    FUNCTION = 264,
    AND_OP = 265,
    OR_OP = 266,
    NOT_OP = 267,
    NE_OP = 268,
    LE_OP = 269,
    GE_OP = 270,
    LS_OP = 271,
    RS_OP = 272,
    IS_OP = 273,
    CASE_KW = 274,
    WHEN_KW = 275,
    THEN_KW = 276,
    ELSE_KW = 277,
    END_KW = 278,
    ISNULL_OP = 279,
    NOTNULL_OP = 280,
    UNARY = 281
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 49 "/opt/neon//vendor/postgres-v16/src/bin/pgbench/exprparse.y" /* yacc.c:1909  */

	int64		ival;
	double		dval;
	bool		bval;
	char	   *str;
	PgBenchExpr *expr;
	PgBenchExprList *elist;

#line 90 "exprparse.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int expr_yyparse (yyscan_t yyscanner);

#endif /* !YY_EXPR_YY_EXPRPARSE_H_INCLUDED  */
