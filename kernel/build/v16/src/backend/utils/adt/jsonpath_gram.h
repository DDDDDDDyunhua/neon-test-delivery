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

#ifndef YY_JSONPATH_YY_JSONPATH_GRAM_H_INCLUDED
# define YY_JSONPATH_YY_JSONPATH_GRAM_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int jsonpath_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TO_P = 258,
    NULL_P = 259,
    TRUE_P = 260,
    FALSE_P = 261,
    IS_P = 262,
    UNKNOWN_P = 263,
    EXISTS_P = 264,
    IDENT_P = 265,
    STRING_P = 266,
    NUMERIC_P = 267,
    INT_P = 268,
    VARIABLE_P = 269,
    OR_P = 270,
    AND_P = 271,
    NOT_P = 272,
    LESS_P = 273,
    LESSEQUAL_P = 274,
    EQUAL_P = 275,
    NOTEQUAL_P = 276,
    GREATEREQUAL_P = 277,
    GREATER_P = 278,
    ANY_P = 279,
    STRICT_P = 280,
    LAX_P = 281,
    LAST_P = 282,
    STARTS_P = 283,
    WITH_P = 284,
    LIKE_REGEX_P = 285,
    FLAG_P = 286,
    ABS_P = 287,
    SIZE_P = 288,
    TYPE_P = 289,
    FLOOR_P = 290,
    DOUBLE_P = 291,
    CEILING_P = 292,
    KEYVALUE_P = 293,
    DATETIME_P = 294,
    UMINUS = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 67 "/opt/neon//vendor/postgres-v16/src/backend/utils/adt/jsonpath_gram.y" /* yacc.c:1909  */

	JsonPathString		str;
	List			   *elems;	/* list of JsonPathParseItem */
	List			   *indexs;	/* list of integers */
	JsonPathParseItem  *value;
	JsonPathParseResult *result;
	JsonPathItemType	optype;
	bool				boolean;
	int					integer;

#line 106 "jsonpath_gram.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int jsonpath_yyparse (JsonPathParseResult **result, struct Node *escontext);

#endif /* !YY_JSONPATH_YY_JSONPATH_GRAM_H_INCLUDED  */
