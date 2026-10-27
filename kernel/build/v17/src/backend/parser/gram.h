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
    CONDITIONAL = 343,
    CONFIGURATION = 344,
    CONFLICT = 345,
    CONNECTION = 346,
    CONSTRAINT = 347,
    CONSTRAINTS = 348,
    CONTENT_P = 349,
    CONTINUE_P = 350,
    CONVERSION_P = 351,
    COPY = 352,
    COST = 353,
    CREATE = 354,
    CROSS = 355,
    CSV = 356,
    CUBE = 357,
    CURRENT_P = 358,
    CURRENT_CATALOG = 359,
    CURRENT_DATE = 360,
    CURRENT_ROLE = 361,
    CURRENT_SCHEMA = 362,
    CURRENT_TIME = 363,
    CURRENT_TIMESTAMP = 364,
    CURRENT_USER = 365,
    CURSOR = 366,
    CYCLE = 367,
    DATA_P = 368,
    DATABASE = 369,
    DAY_P = 370,
    DEALLOCATE = 371,
    DEC = 372,
    DECIMAL_P = 373,
    DECLARE = 374,
    DEFAULT = 375,
    DEFAULTS = 376,
    DEFERRABLE = 377,
    DEFERRED = 378,
    DEFINER = 379,
    DELETE_P = 380,
    DELIMITER = 381,
    DELIMITERS = 382,
    DEPENDS = 383,
    DEPTH = 384,
    DESC = 385,
    DETACH = 386,
    DICTIONARY = 387,
    DISABLE_P = 388,
    DISCARD = 389,
    DISTINCT = 390,
    DO = 391,
    DOCUMENT_P = 392,
    DOMAIN_P = 393,
    DOUBLE_P = 394,
    DROP = 395,
    EACH = 396,
    ELSE = 397,
    EMPTY_P = 398,
    ENABLE_P = 399,
    ENCODING = 400,
    ENCRYPTED = 401,
    END_P = 402,
    ENUM_P = 403,
    ERROR_P = 404,
    ESCAPE = 405,
    EVENT = 406,
    EXCEPT = 407,
    EXCLUDE = 408,
    EXCLUDING = 409,
    EXCLUSIVE = 410,
    EXECUTE = 411,
    EXISTS = 412,
    EXPLAIN = 413,
    EXPRESSION = 414,
    EXTENSION = 415,
    EXTERNAL = 416,
    EXTRACT = 417,
    FALSE_P = 418,
    FAMILY = 419,
    FETCH = 420,
    FILTER = 421,
    FINALIZE = 422,
    FIRST_P = 423,
    FLOAT_P = 424,
    FOLLOWING = 425,
    FOR = 426,
    FORCE = 427,
    FOREIGN = 428,
    FORMAT = 429,
    FORWARD = 430,
    FREEZE = 431,
    FROM = 432,
    FULL = 433,
    FUNCTION = 434,
    FUNCTIONS = 435,
    GENERATED = 436,
    GLOBAL = 437,
    GRANT = 438,
    GRANTED = 439,
    GREATEST = 440,
    GROUP_P = 441,
    GROUPING = 442,
    GROUPS = 443,
    HANDLER = 444,
    HAVING = 445,
    HEADER_P = 446,
    HOLD = 447,
    HOUR_P = 448,
    IDENTITY_P = 449,
    IF_P = 450,
    ILIKE = 451,
    IMMEDIATE = 452,
    IMMUTABLE = 453,
    IMPLICIT_P = 454,
    IMPORT_P = 455,
    IN_P = 456,
    INCLUDE = 457,
    INCLUDING = 458,
    INCREMENT = 459,
    INDENT = 460,
    INDEX = 461,
    INDEXES = 462,
    INHERIT = 463,
    INHERITS = 464,
    INITIALLY = 465,
    INLINE_P = 466,
    INNER_P = 467,
    INOUT = 468,
    INPUT_P = 469,
    INSENSITIVE = 470,
    INSERT = 471,
    INSTEAD = 472,
    INT_P = 473,
    INTEGER = 474,
    INTERSECT = 475,
    INTERVAL = 476,
    INTO = 477,
    INVOKER = 478,
    IS = 479,
    ISNULL = 480,
    ISOLATION = 481,
    JOIN = 482,
    JSON = 483,
    JSON_ARRAY = 484,
    JSON_ARRAYAGG = 485,
    JSON_EXISTS = 486,
    JSON_OBJECT = 487,
    JSON_OBJECTAGG = 488,
    JSON_QUERY = 489,
    JSON_SCALAR = 490,
    JSON_SERIALIZE = 491,
    JSON_TABLE = 492,
    JSON_VALUE = 493,
    KEEP = 494,
    KEY = 495,
    KEYS = 496,
    LABEL = 497,
    LANGUAGE = 498,
    LARGE_P = 499,
    LAST_P = 500,
    LATERAL_P = 501,
    LEADING = 502,
    LEAKPROOF = 503,
    LEAST = 504,
    LEFT = 505,
    LEVEL = 506,
    LIKE = 507,
    LIMIT = 508,
    LISTEN = 509,
    LOAD = 510,
    LOCAL = 511,
    LOCALTIME = 512,
    LOCALTIMESTAMP = 513,
    LOCATION = 514,
    LOCK_P = 515,
    LOCKED = 516,
    LOGGED = 517,
    MAPPING = 518,
    MATCH = 519,
    MATCHED = 520,
    MATERIALIZED = 521,
    MAXVALUE = 522,
    MERGE = 523,
    MERGE_ACTION = 524,
    METHOD = 525,
    MINUTE_P = 526,
    MINVALUE = 527,
    MODE = 528,
    MONTH_P = 529,
    MOVE = 530,
    NAME_P = 531,
    NAMES = 532,
    NATIONAL = 533,
    NATURAL = 534,
    NCHAR = 535,
    NESTED = 536,
    NEW = 537,
    NEXT = 538,
    NFC = 539,
    NFD = 540,
    NFKC = 541,
    NFKD = 542,
    NO = 543,
    NONE = 544,
    NORMALIZE = 545,
    NORMALIZED = 546,
    NOT = 547,
    NOTHING = 548,
    NOTIFY = 549,
    NOTNULL = 550,
    NOWAIT = 551,
    NULL_P = 552,
    NULLIF = 553,
    NULLS_P = 554,
    NUMERIC = 555,
    OBJECT_P = 556,
    OF = 557,
    OFF = 558,
    OFFSET = 559,
    OIDS = 560,
    OLD = 561,
    OMIT = 562,
    ON = 563,
    ONLY = 564,
    OPERATOR = 565,
    OPTION = 566,
    OPTIONS = 567,
    OR = 568,
    ORDER = 569,
    ORDINALITY = 570,
    OTHERS = 571,
    OUT_P = 572,
    OUTER_P = 573,
    OVER = 574,
    OVERLAPS = 575,
    OVERLAY = 576,
    OVERRIDING = 577,
    OWNED = 578,
    OWNER = 579,
    PARALLEL = 580,
    PARAMETER = 581,
    PARSER = 582,
    PARTIAL = 583,
    PARTITION = 584,
    PASSING = 585,
    PASSWORD = 586,
    PATH = 587,
    PLACING = 588,
    PLAN = 589,
    PLANS = 590,
    POLICY = 591,
    POSITION = 592,
    PRECEDING = 593,
    PRECISION = 594,
    PRESERVE = 595,
    PREPARE = 596,
    PREPARED = 597,
    PRIMARY = 598,
    PRIOR = 599,
    PRIVILEGES = 600,
    PROCEDURAL = 601,
    PROCEDURE = 602,
    PROCEDURES = 603,
    PROGRAM = 604,
    PUBLICATION = 605,
    QUOTE = 606,
    QUOTES = 607,
    RANGE = 608,
    READ = 609,
    REAL = 610,
    REASSIGN = 611,
    RECHECK = 612,
    RECURSIVE = 613,
    REF_P = 614,
    REFERENCES = 615,
    REFERENCING = 616,
    REFRESH = 617,
    REINDEX = 618,
    RELATIVE_P = 619,
    RELEASE = 620,
    RENAME = 621,
    REPEATABLE = 622,
    REPLACE = 623,
    REPLICA = 624,
    RESET = 625,
    RESTART = 626,
    RESTRICT = 627,
    RETURN = 628,
    RETURNING = 629,
    RETURNS = 630,
    REVOKE = 631,
    RIGHT = 632,
    ROLE = 633,
    ROLLBACK = 634,
    ROLLUP = 635,
    ROUTINE = 636,
    ROUTINES = 637,
    ROW = 638,
    ROWS = 639,
    RULE = 640,
    SAVEPOINT = 641,
    SCALAR = 642,
    SCHEMA = 643,
    SCHEMAS = 644,
    SCROLL = 645,
    SEARCH = 646,
    SECOND_P = 647,
    SECURITY = 648,
    SELECT = 649,
    SEQUENCE = 650,
    SEQUENCES = 651,
    SERIALIZABLE = 652,
    SERVER = 653,
    SESSION = 654,
    SESSION_USER = 655,
    SET = 656,
    SETS = 657,
    SETOF = 658,
    SHARE = 659,
    SHOW = 660,
    SIMILAR = 661,
    SIMPLE = 662,
    SKIP = 663,
    SMALLINT = 664,
    SNAPSHOT = 665,
    SOME = 666,
    SOURCE = 667,
    SQL_P = 668,
    STABLE = 669,
    STANDALONE_P = 670,
    START = 671,
    STATEMENT = 672,
    STATISTICS = 673,
    STDIN = 674,
    STDOUT = 675,
    STORAGE = 676,
    STORED = 677,
    STRICT_P = 678,
    STRING_P = 679,
    STRIP_P = 680,
    SUBSCRIPTION = 681,
    SUBSTRING = 682,
    SUPPORT = 683,
    SYMMETRIC = 684,
    SYSID = 685,
    SYSTEM_P = 686,
    SYSTEM_USER = 687,
    TABLE = 688,
    TABLES = 689,
    TABLESAMPLE = 690,
    TABLESPACE = 691,
    TARGET = 692,
    TEMP = 693,
    TEMPLATE = 694,
    TEMPORARY = 695,
    TEXT_P = 696,
    THEN = 697,
    TIES = 698,
    TIME = 699,
    TIMESTAMP = 700,
    TO = 701,
    TRAILING = 702,
    TRANSACTION = 703,
    TRANSFORM = 704,
    TREAT = 705,
    TRIGGER = 706,
    TRIM = 707,
    TRUE_P = 708,
    TRUNCATE = 709,
    TRUSTED = 710,
    TYPE_P = 711,
    TYPES_P = 712,
    UESCAPE = 713,
    UNBOUNDED = 714,
    UNCONDITIONAL = 715,
    UNCOMMITTED = 716,
    UNENCRYPTED = 717,
    UNION = 718,
    UNIQUE = 719,
    UNKNOWN = 720,
    UNLISTEN = 721,
    UNLOGGED = 722,
    UNTIL = 723,
    UPDATE = 724,
    USER = 725,
    USING = 726,
    VACUUM = 727,
    VALID = 728,
    VALIDATE = 729,
    VALIDATOR = 730,
    VALUE_P = 731,
    VALUES = 732,
    VARCHAR = 733,
    VARIADIC = 734,
    VARYING = 735,
    VERBOSE = 736,
    VERSION_P = 737,
    VIEW = 738,
    VIEWS = 739,
    VOLATILE = 740,
    WHEN = 741,
    WHERE = 742,
    WHITESPACE_P = 743,
    WINDOW = 744,
    WITH = 745,
    WITHIN = 746,
    WITHOUT = 747,
    WORK = 748,
    WRAPPER = 749,
    WRITE = 750,
    XML_P = 751,
    XMLATTRIBUTES = 752,
    XMLCONCAT = 753,
    XMLELEMENT = 754,
    XMLEXISTS = 755,
    XMLFOREST = 756,
    XMLNAMESPACES = 757,
    XMLPARSE = 758,
    XMLPI = 759,
    XMLROOT = 760,
    XMLSERIALIZE = 761,
    XMLTABLE = 762,
    YEAR_P = 763,
    YES_P = 764,
    ZONE = 765,
    FORMAT_LA = 766,
    NOT_LA = 767,
    NULLS_LA = 768,
    WITH_LA = 769,
    WITHOUT_LA = 770,
    MODE_TYPE_NAME = 771,
    MODE_PLPGSQL_EXPR = 772,
    MODE_PLPGSQL_ASSIGN1 = 773,
    MODE_PLPGSQL_ASSIGN2 = 774,
    MODE_PLPGSQL_ASSIGN3 = 775,
    UMINUS = 776
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 231 "/opt/neon//vendor/postgres-v17/src/backend/parser/gram.y" /* yacc.c:1909  */

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
	MergeMatchKind mergematch;
	MergeWhenClause *mergewhen;
	struct KeyActions *keyactions;
	struct KeyAction *keyaction;

#line 628 "gram.h" /* yacc.c:1909  */
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
