/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "../core/src/parser/c.y" /* yacc.c:339  */

    #include "code_audit/parser.h"

    #include <map>

    using namespace std;
    #define YYSTYPE ASTNode*
    #define EXTRACT_TOKEN(NAME, TARGET)     \
        TokenNode* __temp = (TokenNode*)TARGET;   \
        Token NAME = __temp->token;         \
        delete __temp;                   

namespace CodeAudit
{
namespace SyntaxParser
{
    void yyerror (char *s)
    {
        printf ("%s\n", s);
    }
    int yylex();
    
    void (*ASTCallback)(ASTTree*);

#line 91 "../core/src/parser/parser.yy.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ASSIGN = 258,
    OR = 259,
    AND = 260,
    EQ = 261,
    CMPR = 262,
    SHIFT = 263,
    ID = 264,
    TYPE = 265,
    NUMBER = 266,
    UNSIGNED = 267,
    IF = 268,
    ELSEIF = 269,
    ELSE = 270,
    FOR = 271,
    WHILE = 272,
    INC = 273,
    DEC = 274
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 159 "../core/src/parser/parser.yy.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   284

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  120

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   274

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    17,     9,     2,
      29,    30,    15,    13,     3,    14,     2,    16,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    33,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    35,     8,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     7,    32,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     4,     5,
       6,    10,    11,    12,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    60,    60,    65,    72,    75,    86,    91,    98,   102,
     109,   110,   113,   116,   117,   125,   134,   142,   143,   150,
     155,   156,   157,   158,   161,   165,   169,   170,   171,   172,
     173,   174,   175,   179,   183,   187,   191,   195,   199,   203,
     207,   211,   214,   220,   221,   226,   233,   242,   243,   250,
     251,   255,   264,   265,   269,   270,   271,   275,   286,   299,
     304,   312,   315,   318,   324,   329
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "','", "ASSIGN", "\"||\"", "AND", "'|'",
  "'^'", "'&'", "EQ", "CMPR", "SHIFT", "'+'", "'-'", "'*'", "'/'", "'%'",
  "ID", "TYPE", "NUMBER", "UNSIGNED", "\"if\"", "\"else if\"", "\"else\"",
  "\"for\"", "\"while\"", "\"++\"", "\"--\"", "'('", "')'", "'{'", "'}'",
  "';'", "'['", "']'", "$accept", "input", "global_def", "func_def",
  "type", "pointer_type", "type_name", "id", "args_declare", "block",
  "statement_sequence", "statement", "expr", "func_call", "args_sequence",
  "if_struct", "else_if_seq", "else_body", "while_struct", "empty_or_expr",
  "for_statement_1", "for_struct", "var_def", "var_def_seq",
  "var_def_element", "block_or_line", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    44,   258,   259,   260,   124,    94,    38,
     261,   262,   263,    43,    45,    42,    47,    37,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,    40,
      41,   123,   125,    59,    91,    93
};
# endif

#define YYPACT_NINF -32

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-32)))

#define YYTABLE_NINF -12

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -32,    18,   -32,   -32,   -32,   -13,   -32,   -32,   -16,    -6,
     -32,    -6,   -32,   -15,   -32,    47,   -16,     4,   -32,    47,
       7,   -16,   -32,   -32,   -32,   176,   -14,   -32,    40,    42,
      45,    44,   -32,   -16,   -32,    79,   -32,   -32,   -32,   -32,
      37,    44,    44,   227,    44,    49,    93,    -1,    77,   -32,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,   -32,   -32,   212,     5,   120,   212,
      48,   -32,   147,   -32,    44,    44,   -16,   212,   132,   158,
     105,   248,   256,   238,   262,   267,    25,    25,   -32,   -32,
     -32,    44,   -32,   213,    44,   213,   212,    41,   -32,   212,
     -32,   -32,   -32,   212,    78,   -32,   -32,    -7,    44,   164,
     213,   -32,   146,    44,   -32,   213,   174,   -32,   213,   -32
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,    11,    10,     0,     3,     4,     0,     6,
       8,     7,    12,     0,     9,    13,     0,     0,    14,     0,
       0,     0,    17,     5,    15,     0,    24,    25,     0,     0,
       0,     0,    16,     0,    18,     0,    41,    21,    23,    22,
       0,    43,     0,    54,     0,    24,     0,    61,    58,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    19,    20,    44,     0,     0,    55,
       0,    56,     0,    26,     0,     0,     0,    34,    36,    37,
      39,    40,    38,    35,    33,    32,    27,    28,    29,    30,
      31,     0,    42,     0,    52,     0,    63,     0,    60,    45,
      65,    64,    47,    53,     0,    51,    62,    49,    52,     0,
       0,    46,     0,     0,    50,     0,     0,    57,     0,    48
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -32,   -32,   -32,   -32,    60,   194,   -32,    51,   -32,   180,
     -32,   178,   -31,   -32,   -32,   -32,   -32,   -32,   -32,    98,
     -32,   -32,   166,   -32,   134,    97
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     6,     7,    33,     9,    10,    47,    17,   100,
      25,   101,    35,    36,    67,    37,   107,   111,    38,   104,
      70,    39,    40,    48,    49,   102
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      46,   -11,    12,    74,   -11,     3,     4,    19,    91,    14,
      66,    68,    69,    72,    15,    41,   109,   110,     2,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    75,    20,    92,     3,     4,    22,     5,
      61,    62,    63,    96,    97,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    13,
      99,     8,    45,   103,    27,     3,     4,    18,     5,    42,
      65,    43,    24,    31,    44,    16,   106,   103,    41,    21,
      76,    94,   116,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,   108,    64,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    73,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      93,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,   115,    95,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,   105,   113,    26,     4,    27,     5,    28,    11,
      23,    29,    30,    34,   118,    31,   112,   114,    32,    71,
      98,     0,   117,     0,     0,   119,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
       0,    26,     4,    27,     5,    28,     0,     0,    29,    30,
       0,     0,    31,     0,    22,    26,     4,    27,     5,    57,
      58,    59,    60,    61,    62,    63,    31,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    56,    57,    58,    59,
      60,    61,    62,    63,    58,    59,    60,    61,    62,    63,
      59,    60,    61,    62,    63
};

static const yytype_int8 yycheck[] =
{
      31,    15,    18,     4,    18,    18,    19,     3,     3,    15,
      41,    42,    43,    44,    29,    29,    23,    24,     0,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    34,    30,    30,    18,    19,    31,    21,
      15,    16,    17,    74,    75,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,     8,
      91,     1,    18,    94,    20,    18,    19,    16,    21,    29,
      33,    29,    21,    29,    29,    15,    35,   108,    29,    19,
       3,    33,   113,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    33,    33,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    30,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      30,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    30,    30,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    95,    29,    18,    19,    20,    21,    22,     5,
      20,    25,    26,    25,    30,    29,   108,   110,    32,    43,
      76,    -1,   115,    -1,    -1,   118,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    18,    19,    20,    21,    22,    -1,    -1,    25,    26,
      -1,    -1,    29,    -1,    31,    18,    19,    20,    21,    11,
      12,    13,    14,    15,    16,    17,    29,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    10,    11,    12,    13,
      14,    15,    16,    17,    12,    13,    14,    15,    16,    17,
      13,    14,    15,    16,    17
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    37,     0,    18,    19,    21,    38,    39,    40,    41,
      42,    41,    18,    43,    15,    29,    40,    44,    43,     3,
      30,    40,    31,    45,    43,    46,    18,    20,    22,    25,
      26,    29,    32,    40,    47,    48,    49,    51,    54,    57,
      58,    29,    29,    29,    29,    18,    48,    43,    59,    60,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    33,    33,    48,    50,    48,    48,
      56,    58,    48,    30,     4,    34,     3,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,     3,    30,    30,    33,    30,    48,    48,    60,    48,
      45,    47,    61,    48,    55,    61,    35,    52,    33,    23,
      24,    53,    55,    29,    61,    30,    48,    61,    30,    61
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    37,    38,    39,    40,    40,    41,    41,
      42,    42,    43,    44,    44,    44,    45,    46,    46,    47,
      47,    47,    47,    47,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    49,    50,    50,    50,    51,    52,    52,    53,
      53,    54,    55,    55,    56,    56,    56,    57,    58,    59,
      59,    60,    60,    60,    61,    61
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     6,     1,     2,     1,     2,
       1,     1,     1,     0,     2,     4,     3,     0,     2,     2,
       2,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     4,     0,     1,     3,     7,     0,     6,     0,
       2,     5,     0,     1,     0,     1,     1,     9,     2,     1,
       3,     1,     4,     3,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 60 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        auto ast = new ASTTree;
        ASTCallback(ast);
        (yyval) = ast;
    }
#line 1352 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 65 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
                ASTTree* root = (ASTTree*)(yyvsp[-1]);
                root->globals->push_back((FunctionDefine*)(yyvsp[0]));
                (yyval) = root;
            }
#line 1362 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 72 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1368 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 75 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
    auto f = new FunctionDefine;
    f->name = ((TokenNode*)(yyvsp[-4]))->token.name;
    f->type = (TypeNode*)(yyvsp[-5]);
    f->id = (TokenNode*)(yyvsp[-4]);
    f->args = (ListNode<ParameterNode>*)(yyvsp[-2]);
    f->body = (BlockNode*)(yyvsp[0]);
    (yyval) = f;
 }
#line 1382 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 86 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        TypeNode* type = (TypeNode*)(yyvsp[0]);
        type->sign = true;
        (yyval) = type;
    }
#line 1392 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 91 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        TypeNode* type = (TypeNode*)(yyvsp[0]);
        type->sign = false;
        (yyval) = type;
    }
#line 1402 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 98 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        EXTRACT_TOKEN(type, (yyvsp[0]))
        (yyval) = new TypeNode(true, type);
    }
#line 1411 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 102 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        TypeNode* type = (TypeNode*)(yyvsp[-1]);
        type->pointerLevel++;
        (yyval) = type;
    }
#line 1421 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 109 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1427 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 110 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1433 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 113 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1439 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 116 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new ListNode<ParameterNode>; }
#line 1445 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 117 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto list = new ListNode<ParameterNode>;
        auto p = new ParameterNode;
        p->type = (TypeNode*)(yyvsp[-1]);
        p->id = (TokenNode*)(yyvsp[0]);
        list->list->push_back(p);
        (yyval) = list;
    }
#line 1458 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 125 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        ListNode<ParameterNode>* list = (ListNode<ParameterNode>*)(yyvsp[-3]);
        auto p = new ParameterNode;
        p->type = (TypeNode*)(yyvsp[-1]);
        p->id = (TokenNode*)(yyvsp[0]);
        list->list->push_back(p);
        (yyval) = list;
    }
#line 1471 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 134 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        auto block = new BlockNode; 
        block->statements = ((ListNode<Statement>*)(yyvsp[-1]))->list;
        (yyval) = block;
        delete (yyvsp[-1]);
    }
#line 1482 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 142 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new ListNode<Statement>; }
#line 1488 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 143 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto list = (ListNode<Statement>*) (yyvsp[-1]);
        list->list->push_back((Statement*)(yyvsp[0]));
        (yyval) = list;
    }
#line 1498 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 150 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        auto s = new ExpressionStatement;
        s->expression = (Expression*)(yyvsp[-1]);
        (yyval) = s;
    }
#line 1508 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 155 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1514 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 156 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1520 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 157 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1526 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 158 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1532 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 161 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
            EXTRACT_TOKEN(token, (yyvsp[0]))
            (yyval) = new Variable(token);
        }
#line 1541 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 165 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
            EXTRACT_TOKEN(token, (yyvsp[0]))
            (yyval) = new Constant(token);
        }
#line 1550 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 169 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (Expression*)(yyvsp[-1]); }
#line 1556 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 170 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new InfixExpr("+", (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0])); }
#line 1562 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 171 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new InfixExpr("-", (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0])); }
#line 1568 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 172 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new InfixExpr("*", (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0])); }
#line 1574 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 173 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new InfixExpr("/", (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0])); }
#line 1580 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 174 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new InfixExpr("%", (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0])); }
#line 1586 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 175 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[-1]))
        (yyval) = new InfixExpr(op.name, (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1595 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 179 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[-1]))
        (yyval) = new InfixExpr(op.name, (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1604 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 183 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[-1]))
        (yyval) = new InfixExpr(op.name, (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1613 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 187 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[-1]))
        (yyval) = new InfixExpr(op.name, (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1622 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 191 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[-1]))
        (yyval) = new InfixExpr(op.name, (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1631 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 195 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[-1]))
        (yyval) = new InfixExpr(op.name, (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1640 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 199 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        //EXTRACT_TOKEN(op, $2)
        (yyval) = new InfixExpr("&", (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1649 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 203 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        //EXTRACT_TOKEN(op, $2)
        (yyval) = new InfixExpr("|", (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1658 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 207 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        //EXTRACT_TOKEN(op, $2)
        (yyval) = new InfixExpr("^", (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1667 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 211 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1673 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 214 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        EXTRACT_TOKEN(id, (yyvsp[-3]))
        (yyval) = new FunctionInvokeNode(id, (ListNode<Expression>*)(yyvsp[-1]));
    }
#line 1682 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 220 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new ListNode<Expression>; }
#line 1688 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 221 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto list = new ListNode<Expression>;
        list->list->push_back((Expression*) (yyvsp[0]));
        (yyval) = list;
    }
#line 1698 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 226 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        ListNode<Expression>* list = (ListNode<Expression>*)(yyvsp[-2]);
        list->list->push_back((Expression*) (yyvsp[0]));
        (yyval) = list;
    }
#line 1708 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 233 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto if_struct = new If((Expression*)(yyvsp[-4]), (BlockNode*)(yyvsp[-2]));
        if_struct->elseif = ((ListNode<ConditionStructure>*)(yyvsp[-1]))->list;
        delete (yyvsp[-1]);
        if_struct->elseBody = (BlockNode*)(yyvsp[0]);
        (yyval) = if_struct;
    }
#line 1720 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 242 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new ListNode<ConditionStructure>; }
#line 1726 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 243 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        ListNode<ConditionStructure>* node = (ListNode<ConditionStructure>*)(yyvsp[-5]);
        node->list->push_back(new ConditionStructure((Expression*)(yyvsp[-2]), (BlockNode*)(yyvsp[0])));
        (yyval) = node;
    }
#line 1736 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 250 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = nullptr; }
#line 1742 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 251 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1748 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 255 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto loop = new ForLoop;
        loop->s2 = (Expression*)(yyvsp[-2]);
        loop->body = (BlockNode*)(yyvsp[0]);
        (yyval) = loop;
    }
#line 1759 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 264 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = nullptr; }
#line 1765 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 265 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1771 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 269 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = nullptr; }
#line 1777 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 270 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1783 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 271 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1789 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 275 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto loop = new ForLoop;
        loop->s1 = (Expression*)(yyvsp[-6]);
        loop->s2 = (Expression*)(yyvsp[-4]);
        loop->s3 = (Expression*)(yyvsp[-2]);
        loop->body = (BlockNode*)(yyvsp[0]);
        (yyval) = loop;
    }
#line 1802 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 286 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto def = new VariableDefStatement;
        def->vars = ((ListNode<VariableDefine>*)(yyvsp[0]))->list;
        delete (yyvsp[0]);
        for(auto & var : *(def->vars))
        {
            var->type = (TypeNode*)(yyvsp[-1]);
        }
        (yyval) = def;
    }
#line 1817 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 299 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        auto seq = new ListNode<VariableDefine>;
        seq->list->push_back((VariableDefine*)(yyvsp[0]));
        (yyval) =  seq;
    }
#line 1827 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 304 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        ListNode<VariableDefine>* seq = (ListNode<VariableDefine>*)(yyvsp[-2]);
        seq->list->push_back((VariableDefine*)(yyvsp[0]));
        (yyval) = seq;
    }
#line 1837 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 312 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        (yyval) = new VariableDefine(nullptr, (TokenNode*)(yyvsp[0]), nullptr, nullptr); 
    }
#line 1845 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 315 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        (yyval) = new VariableDefine(nullptr, (TokenNode*)(yyvsp[-3]), nullptr, (Expression*)(yyvsp[-1])); 
    }
#line 1853 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 318 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        (yyval) = new VariableDefine(nullptr, (TokenNode*)(yyvsp[-2]), (Expression*)(yyvsp[0]), nullptr); 
    }
#line 1861 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 324 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        auto block = new BlockNode;
        block->statements->push_back((Statement*)(yyvsp[0]));
        (yyval) = (yyvsp[0]);
    }
#line 1871 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 329 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1877 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;


#line 1881 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 332 "../core/src/parser/c.y" /* yacc.c:1906  */


enum LexerState
{
    LEX_NEXT,
    LEX_OUTPUT,
};

map<string, int> TokenMap;
vector<Token>* TokenList;
int idx = 0;
int subIdx = -1;

void set_tokens(vector<Token>* tokens)
{
    TokenList = tokens;
}

void set_ast_callback(void (*callback)(ASTTree*))
{
    ASTCallback = callback;
}
void reset_parser()
{
    TokenList = nullptr;
    idx = 0;
    subIdx = -1;
    TokenMap["id"] = ID;
    TokenMap["number"] = NUMBER;
    TokenMap["bool"] = TYPE;
    TokenMap["char"] = TYPE;
    TokenMap["byte"] = TYPE;
    TokenMap["short"] = TYPE;
    TokenMap["int"] = TYPE;
    TokenMap["long"] = TYPE;
    TokenMap["long long"] = TYPE;
    TokenMap["float"] = TYPE;
    TokenMap["double"] = TYPE;
    TokenMap["void"] = TYPE;
    TokenMap["unsigned"] = UNSIGNED;
    TokenMap["if"] = IF;
    TokenMap["else if"] = ELSEIF;
    TokenMap["else"] = ELSE;
    TokenMap["for"] = FOR;
    TokenMap["while"] = WHILE;
    TokenMap["||"] = OR;
    TokenMap["&&"] = AND;
    TokenMap["<"] = TokenMap[">"] = TokenMap["<="] = TokenMap[">="] = CMPR;
    TokenMap["<<"] = TokenMap[">>"] = SHIFT;
    TokenMap["=="] = TokenMap["!="] = EQ;
    TokenMap["="]
        =TokenMap["+="]
        =TokenMap["-="]
        =TokenMap["*="]
        =TokenMap["/="]
        =TokenMap["%="]
        =TokenMap["<<="]
        =TokenMap[">>="]
        =TokenMap["&="]
        =TokenMap["^="]
        =TokenMap["|="] = ASSIGN;
    
}

int yylex()
{
    auto t = (int)idx >= (int)(TokenList->size());
    if(t)
        return 0;

    if(subIdx < 0)
    {
        if(TokenMap.find(TokenList->at(idx).name) != TokenMap.end())
        {
            auto node = new TokenNode;
            node->token = TokenList->at(idx);
            idx++;
            subIdx = -1;
            yylval = node;
            return TokenMap[node->token.name];
        }
        else
        {
            subIdx = 0;
        }
    }
    
    char chr = TokenList->at(idx).name[subIdx++];
    if(subIdx >= TokenList->at(idx).name.size())
    {
        idx++;
        subIdx = -1;
    }
    return chr;
}
}
}
