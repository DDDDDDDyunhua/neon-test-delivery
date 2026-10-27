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

#ifndef YY_BOOT_YY_BOOTPARSE_H_INCLUDED
# define YY_BOOT_YY_BOOTPARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int boot_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    COMMA = 259,
    EQUALS = 260,
    LPAREN = 261,
    RPAREN = 262,
    NULLVAL = 263,
    OPEN = 264,
    XCLOSE = 265,
    XCREATE = 266,
    INSERT_TUPLE = 267,
    XDECLARE = 268,
    INDEX = 269,
    ON = 270,
    USING = 271,
    XBUILD = 272,
    INDICES = 273,
    UNIQUE = 274,
    XTOAST = 275,
    OBJ_ID = 276,
    XBOOTSTRAP = 277,
    XSHARED_RELATION = 278,
    XROWTYPE_OID = 279,
    XFORCE = 280,
    XNOT = 281,
    XNULL = 282
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 82 "/opt/neon//vendor/postgres-v16/src/backend/bootstrap/bootparse.y" /* yacc.c:1909  */

	List		*list;
	IndexElem	*ielem;
	char		*str;
	const char	*kw;
	int			ival;
	Oid			oidval;

#line 91 "bootparse.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE boot_yylval;

int boot_yyparse (void);

#endif /* !YY_BOOT_YY_BOOTPARSE_H_INCLUDED  */
