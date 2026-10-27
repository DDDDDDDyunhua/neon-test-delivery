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

#ifndef YY_SPEC_YY_SPECPARSE_H_INCLUDED
# define YY_SPEC_YY_SPECPARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int spec_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    sqlblock = 258,
    identifier = 259,
    INTEGER = 260,
    NOTICES = 261,
    PERMUTATION = 262,
    SESSION = 263,
    SETUP = 264,
    STEP = 265,
    TEARDOWN = 266,
    TEST = 267
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 26 "/opt/neon//vendor/postgres-v16/src/test/isolation/specparse.y" /* yacc.c:1909  */

	char	   *str;
	int			integer;
	Session	   *session;
	Step	   *step;
	Permutation *permutation;
	PermutationStep *permutationstep;
	PermutationStepBlocker *blocker;
	struct
	{
		void  **elements;
		int		nelements;
	}			ptr_list;

#line 82 "specparse.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE spec_yylval;

int spec_yyparse (void);

#endif /* !YY_SPEC_YY_SPECPARSE_H_INCLUDED  */
