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

#ifndef YY_BASE_YY_GRAM_H_INCLUDED
# define YY_BASE_YY_GRAM_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int base_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENT = 258,
    UIDENT = 259,
    FCONST = 260,
    SCONST = 261,
    USCONST = 262,
    BCONST = 263,
    XCONST = 264,
    Op = 265,
    ICONST = 266,
    PARAM = 267,
    TYPECAST = 268,
    DOT_DOT = 269,
    COLON_EQUALS = 270,
    EQUALS_GREATER = 271,
    LESS_EQUALS = 272,
    GREATER_EQUALS = 273,
    NOT_EQUALS = 274,
    ABORT_P = 275,
    ABSENT = 276,
    ABSOLUTE_P = 277,
    ACCESS = 278,
    ACTION = 279,
    ADD_P = 280,
    ADMIN = 281,
    AFTER = 282,
    AGGREGATE = 283,
    ALL = 284,
    ALSO = 285,
    ALTER = 286,
    ALWAYS = 287,
    ANALYSE = 288,
    ANALYZE = 289,
    AND = 290,
    ANY = 291,
    ARRAY = 292,
    AS = 293,
    ASC = 294,
    ASENSITIVE = 295,
    ASSERTION = 296,
    ASSIGNMENT = 297,
    ASYMMETRIC = 298,
    ATOMIC = 299,
    AT = 300,
    ATTACH = 301,
    ATTRIBUTE = 302,
    AUTHORIZATION = 303,
    BACKWARD = 304,
    BEFORE = 305,
    BEGIN_P = 306,
    BETWEEN = 307,
    BIGINT = 308,
    BINARY = 309,
    BIT = 310,
    BOOLEAN_P = 311,
    BOTH = 312,
    BREADTH = 313,
    BY = 314,
    CACHE = 315,
    CALL = 316,
    CALLED = 317,
    CASCADE = 318,
    CASCADED = 319,
    CASE = 320,
    CAST = 321,
    CATALOG_P = 322,
    CHAIN = 323,
    CHAR_P = 324,
    CHARACTER = 325,
    CHARACTERISTICS = 326,
    CHECK = 327,
    CHECKPOINT = 328,
    CLASS = 329,
    CLOSE = 330,
    CLUSTER = 331,
    COALESCE = 332,
    COLLATE = 333,
    COLLATION = 334,
    COLUMN = 335,
    COLUMNS = 336,
    COMMENT = 337,
    COMMENTS = 338,
    COMMIT = 339,
    COMMITTED = 340,
    COMPRESSION = 341,
    CONCURRENTLY = 342,
    CONFIGURATION = 343,
    CONFLICT = 344,
    CONNECTION = 345,
    CONSTRAINT = 346,
    CONSTRAINTS = 347,
    CONTENT_P = 348,
    CONTINUE_P = 349,
    CONVERSION_P = 350,
    COPY = 351,
    COST = 352,
    CREATE = 353,
    CROSS = 354,
    CSV = 355,
    CUBE = 356,
    CURRENT_P = 357,
    CURRENT_CATALOG = 358,
    CURRENT_DATE = 359,
    CURRENT_ROLE = 360,
    CURRENT_SCHEMA = 361,
    CURRENT_TIME = 362,
    CURRENT_TIMESTAMP = 363,
    CURRENT_USER = 364,
    CURSOR = 365,
    CYCLE = 366,
    DATA_P = 367,
    DATABASE = 368,
    DAY_P = 369,
    DEALLOCATE = 370,
    DEC = 371,
    DECIMAL_P = 372,
    DECLARE = 373,
    DEFAULT = 374,
    DEFAULTS = 375,
    DEFERRABLE = 376,
    DEFERRED = 377,
    DEFINER = 378,
    DELETE_P = 379,
    DELIMITER = 380,
    DELIMITERS = 381,
    DEPENDS = 382,
    DEPTH = 383,
    DESC = 384,
    DETACH = 385,
    DICTIONARY = 386,
    DISABLE_P = 387,
    DISCARD = 388,
    DISTINCT = 389,
    DO = 390,
    DOCUMENT_P = 391,
    DOMAIN_P = 392,
    DOUBLE_P = 393,
    DROP = 394,
    EACH = 395,
    ELSE = 396,
    ENABLE_P = 397,
    ENCODING = 398,
    ENCRYPTED = 399,
    END_P = 400,
    ENUM_P = 401,
    ESCAPE = 402,
    EVENT = 403,
    EXCEPT = 404,
    EXCLUDE = 405,
    EXCLUDING = 406,
    EXCLUSIVE = 407,
    EXECUTE = 408,
    EXISTS = 409,
    EXPLAIN = 410,
    EXPRESSION = 411,
    EXTENSION = 412,
    EXTERNAL = 413,
    EXTRACT = 414,
    FALSE_P = 415,
    FAMILY = 416,
    FETCH = 417,
    FILTER = 418,
    FINALIZE = 419,
    FIRST_P = 420,
    FLOAT_P = 421,
    FOLLOWING = 422,
    FOR = 423,
    FORCE = 424,
    FOREIGN = 425,
    FORMAT = 426,
    FORWARD = 427,
    FREEZE = 428,
    FROM = 429,
    FULL = 430,
    FUNCTION = 431,
    FUNCTIONS = 432,
    GENERATED = 433,
    GLOBAL = 434,
    GRANT = 435,
    GRANTED = 436,
    GREATEST = 437,
    GROUP_P = 438,
    GROUPING = 439,
    GROUPS = 440,
    HANDLER = 441,
    HAVING = 442,
    HEADER_P = 443,
    HOLD = 444,
    HOUR_P = 445,
    IDENTITY_P = 446,
    IF_P = 447,
    ILIKE = 448,
    IMMEDIATE = 449,
    IMMUTABLE = 450,
    IMPLICIT_P = 451,
    IMPORT_P = 452,
    IN_P = 453,
    INCLUDE = 454,
    INCLUDING = 455,
    INCREMENT = 456,
    INDENT = 457,
    INDEX = 458,
    INDEXES = 459,
    INHERIT = 460,
    INHERITS = 461,
    INITIALLY = 462,
    INLINE_P = 463,
    INNER_P = 464,
    INOUT = 465,
    INPUT_P = 466,
    INSENSITIVE = 467,
    INSERT = 468,
    INSTEAD = 469,
    INT_P = 470,
    INTEGER = 471,
    INTERSECT = 472,
    INTERVAL = 473,
    INTO = 474,
    INVOKER = 475,
    IS = 476,
    ISNULL = 477,
    ISOLATION = 478,
    JOIN = 479,
    JSON = 480,
    JSON_ARRAY = 481,
    JSON_ARRAYAGG = 482,
    JSON_OBJECT = 483,
    JSON_OBJECTAGG = 484,
    KEY = 485,
    KEYS = 486,
    LABEL = 487,
    LANGUAGE = 488,
    LARGE_P = 489,
    LAST_P = 490,
    LATERAL_P = 491,
    LEADING = 492,
    LEAKPROOF = 493,
    LEAST = 494,
    LEFT = 495,
    LEVEL = 496,
    LIKE = 497,
    LIMIT = 498,
    LISTEN = 499,
    LOAD = 500,
    LOCAL = 501,
    LOCALTIME = 502,
    LOCALTIMESTAMP = 503,
    LOCATION = 504,
    LOCK_P = 505,
    LOCKED = 506,
    LOGGED = 507,
    MAPPING = 508,
    MATCH = 509,
    MATCHED = 510,
    MATERIALIZED = 511,
    MAXVALUE = 512,
    MERGE = 513,
    METHOD = 514,
    MINUTE_P = 515,
    MINVALUE = 516,
    MODE = 517,
    MONTH_P = 518,
    MOVE = 519,
    NAME_P = 520,
    NAMES = 521,
    NATIONAL = 522,
    NATURAL = 523,
    NCHAR = 524,
    NEW = 525,
    NEXT = 526,
    NFC = 527,
    NFD = 528,
    NFKC = 529,
    NFKD = 530,
    NO = 531,
    NONE = 532,
    NORMALIZE = 533,
    NORMALIZED = 534,
    NOT = 535,
    NOTHING = 536,
    NOTIFY = 537,
    NOTNULL = 538,
    NOWAIT = 539,
    NULL_P = 540,
    NULLIF = 541,
    NULLS_P = 542,
    NUMERIC = 543,
    OBJECT_P = 544,
    OF = 545,
    OFF = 546,
    OFFSET = 547,
    OIDS = 548,
    OLD = 549,
    ON = 550,
    ONLY = 551,
    OPERATOR = 552,
    OPTION = 553,
    OPTIONS = 554,
    OR = 555,
    ORDER = 556,
    ORDINALITY = 557,
    OTHERS = 558,
    OUT_P = 559,
    OUTER_P = 560,
    OVER = 561,
    OVERLAPS = 562,
    OVERLAY = 563,
    OVERRIDING = 564,
    OWNED = 565,
    OWNER = 566,
    PARALLEL = 567,
    PARAMETER = 568,
    PARSER = 569,
    PARTIAL = 570,
    PARTITION = 571,
    PASSING = 572,
    PASSWORD = 573,
    PLACING = 574,
    PLANS = 575,
    POLICY = 576,
    POSITION = 577,
    PRECEDING = 578,
    PRECISION = 579,
    PRESERVE = 580,
    PREPARE = 581,
    PREPARED = 582,
    PRIMARY = 583,
    PRIOR = 584,
    PRIVILEGES = 585,
    PROCEDURAL = 586,
    PROCEDURE = 587,
    PROCEDURES = 588,
    PROGRAM = 589,
    PUBLICATION = 590,
    QUOTE = 591,
    RANGE = 592,
    READ = 593,
    REAL = 594,
    REASSIGN = 595,
    RECHECK = 596,
    RECURSIVE = 597,
    REF_P = 598,
    REFERENCES = 599,
    REFERENCING = 600,
    REFRESH = 601,
    REINDEX = 602,
    RELATIVE_P = 603,
    RELEASE = 604,
    RENAME = 605,
    REPEATABLE = 606,
    REPLACE = 607,
    REPLICA = 608,
    RESET = 609,
    RESTART = 610,
    RESTRICT = 611,
    RETURN = 612,
    RETURNING = 613,
    RETURNS = 614,
    REVOKE = 615,
    RIGHT = 616,
    ROLE = 617,
    ROLLBACK = 618,
    ROLLUP = 619,
    ROUTINE = 620,
    ROUTINES = 621,
    ROW = 622,
    ROWS = 623,
    RULE = 624,
    SAVEPOINT = 625,
    SCALAR = 626,
    SCHEMA = 627,
    SCHEMAS = 628,
    SCROLL = 629,
    SEARCH = 630,
    SECOND_P = 631,
    SECURITY = 632,
    SELECT = 633,
    SEQUENCE = 634,
    SEQUENCES = 635,
    SERIALIZABLE = 636,
    SERVER = 637,
    SESSION = 638,
    SESSION_USER = 639,
    SET = 640,
    SETS = 641,
    SETOF = 642,
    SHARE = 643,
    SHOW = 644,
    SIMILAR = 645,
    SIMPLE = 646,
    SKIP = 647,
    SMALLINT = 648,
    SNAPSHOT = 649,
    SOME = 650,
    SQL_P = 651,
    STABLE = 652,
    STANDALONE_P = 653,
    START = 654,
    STATEMENT = 655,
    STATISTICS = 656,
    STDIN = 657,
    STDOUT = 658,
    STORAGE = 659,
    STORED = 660,
    STRICT_P = 661,
    STRIP_P = 662,
    SUBSCRIPTION = 663,
    SUBSTRING = 664,
    SUPPORT = 665,
    SYMMETRIC = 666,
    SYSID = 667,
    SYSTEM_P = 668,
    SYSTEM_USER = 669,
    TABLE = 670,
    TABLES = 671,
    TABLESAMPLE = 672,
    TABLESPACE = 673,
    TEMP = 674,
    TEMPLATE = 675,
    TEMPORARY = 676,
    TEXT_P = 677,
    THEN = 678,
    TIES = 679,
    TIME = 680,
    TIMESTAMP = 681,
    TO = 682,
    TRAILING = 683,
    TRANSACTION = 684,
    TRANSFORM = 685,
    TREAT = 686,
    TRIGGER = 687,
    TRIM = 688,
    TRUE_P = 689,
    TRUNCATE = 690,
    TRUSTED = 691,
    TYPE_P = 692,
    TYPES_P = 693,
    UESCAPE = 694,
    UNBOUNDED = 695,
    UNCOMMITTED = 696,
    UNENCRYPTED = 697,
    UNION = 698,
    UNIQUE = 699,
    UNKNOWN = 700,
    UNLISTEN = 701,
    UNLOGGED = 702,
    UNTIL = 703,
    UPDATE = 704,
    USER = 705,
    USING = 706,
    VACUUM = 707,
    VALID = 708,
    VALIDATE = 709,
    VALIDATOR = 710,
    VALUE_P = 711,
    VALUES = 712,
    VARCHAR = 713,
    VARIADIC = 714,
    VARYING = 715,
    VERBOSE = 716,
    VERSION_P = 717,
    VIEW = 718,
    VIEWS = 719,
    VOLATILE = 720,
    WHEN = 721,
    WHERE = 722,
    WHITESPACE_P = 723,
    WINDOW = 724,
    WITH = 725,
    WITHIN = 726,
    WITHOUT = 727,
    WORK = 728,
    WRAPPER = 729,
    WRITE = 730,
    XML_P = 731,
    XMLATTRIBUTES = 732,
    XMLCONCAT = 733,
    XMLELEMENT = 734,
    XMLEXISTS = 735,
    XMLFOREST = 736,
    XMLNAMESPACES = 737,
    XMLPARSE = 738,
    XMLPI = 739,
    XMLROOT = 740,
    XMLSERIALIZE = 741,
    XMLTABLE = 742,
    YEAR_P = 743,
    YES_P = 744,
    ZONE = 745,
    FORMAT_LA = 746,
    NOT_LA = 747,
    NULLS_LA = 748,
    WITH_LA = 749,
    WITHOUT_LA = 750,
    MODE_TYPE_NAME = 751,
    MODE_PLPGSQL_EXPR = 752,
    MODE_PLPGSQL_ASSIGN1 = 753,
    MODE_PLPGSQL_ASSIGN2 = 754,
    MODE_PLPGSQL_ASSIGN3 = 755,
    UMINUS = 756
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 232 "/opt/neon//vendor/postgres-v16/src/backend/parser/gram.y" /* yacc.c:1909  */

	core_YYSTYPE core_yystype;
	/* these fields must match core_YYSTYPE: */
	int			ival;
	char	   *str;
	const char *keyword;

	char		chr;
	bool		boolean;
	JoinType	jtype;
	DropBehavior dbehavior;
	OnCommitAction oncommit;
	List	   *list;
	Node	   *node;
	ObjectType	objtype;
	TypeName   *typnam;
	FunctionParameter *fun_param;
	FunctionParameterMode fun_param_mode;
	ObjectWithArgs *objwithargs;
	DefElem	   *defelt;
	SortBy	   *sortby;
	WindowDef  *windef;
	JoinExpr   *jexpr;
	IndexElem  *ielem;
	StatsElem  *selem;
	Alias	   *alias;
	RangeVar   *range;
	IntoClause *into;
	WithClause *with;
	InferClause	*infer;
	OnConflictClause *onconflict;
	A_Indices  *aind;
	ResTarget  *target;
	struct PrivTarget *privtarget;
	AccessPriv *accesspriv;
	struct ImportQual *importqual;
	InsertStmt *istmt;
	VariableSetStmt *vsetstmt;
	PartitionElem *partelem;
	PartitionSpec *partspec;
	PartitionBoundSpec *partboundspec;
	RoleSpec   *rolespec;
	PublicationObjSpec *publicationobjectspec;
	struct SelectLimit *selectlimit;
	SetQuantifier setquantifier;
	struct GroupClause *groupclause;
	MergeWhenClause *mergewhen;
	struct KeyActions *keyactions;
	struct KeyAction *keyaction;

#line 607 "gram.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int base_yyparse (core_yyscan_t yyscanner);

#endif /* !YY_BASE_YY_GRAM_H_INCLUDED  */
