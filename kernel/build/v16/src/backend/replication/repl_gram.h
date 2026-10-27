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

#ifndef YY_REPLICATION_YY_REPL_GRAM_H_INCLUDED
# define YY_REPLICATION_YY_REPL_GRAM_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int replication_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SCONST = 258,
    IDENT = 259,
    UCONST = 260,
    RECPTR = 261,
    K_BASE_BACKUP = 262,
    K_IDENTIFY_SYSTEM = 263,
    K_READ_REPLICATION_SLOT = 264,
    K_SHOW = 265,
    K_START_REPLICATION = 266,
    K_CREATE_REPLICATION_SLOT = 267,
    K_DROP_REPLICATION_SLOT = 268,
    K_TIMELINE_HISTORY = 269,
    K_WAIT = 270,
    K_TIMELINE = 271,
    K_PHYSICAL = 272,
    K_LOGICAL = 273,
    K_SLOT = 274,
    K_RESERVE_WAL = 275,
    K_TEMPORARY = 276,
    K_TWO_PHASE = 277,
    K_EXPORT_SNAPSHOT = 278,
    K_NOEXPORT_SNAPSHOT = 279,
    K_USE_SNAPSHOT = 280
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 44 "/opt/neon//vendor/postgres-v16/src/backend/replication/repl_gram.y" /* yacc.c:1909  */

	char	   *str;
	bool		boolval;
	uint32		uintval;
	XLogRecPtr	recptr;
	Node	   *node;
	List	   *list;
	DefElem	   *defelt;

#line 90 "repl_gram.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE replication_yylval;

int replication_yyparse (void);

#endif /* !YY_REPLICATION_YY_REPL_GRAM_H_INCLUDED  */
