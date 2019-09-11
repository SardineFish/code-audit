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
    #include <iostream>

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
    Token latestToken;
    void yyerror (char *s)
    {
        cout << s;
        cout << " ";
        cout << "<" << latestToken.name <<" "<<latestToken.attribute << ">";
        cout << " at " << latestToken.pos << endl;
    }
    int yylex();
    
    void (*ASTCallback)(ASTTree*);

#line 96 "../core/src/parser/parser.yy.cpp" /* yacc.c:339  */

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
    OP_ASSIGN = 259,
    OR = 260,
    AND = 261,
    EQ = 262,
    CMPR = 263,
    SHIFT = 264,
    PTR_MBR = 265,
    ID = 266,
    TYPE = 267,
    NUMBER = 268,
    UNSIGNED = 269,
    IF = 270,
    ELSEIF = 271,
    ELSE = 272,
    FOR = 273,
    WHILE = 274,
    INC = 275,
    DEC = 276,
    STRING = 277,
    CHAR = 278,
    PREPROC = 279,
    RETURN = 280,
    VOID = 281,
    SIZEOF = 282,
    OTHER_KEYWORD = 283
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

#line 173 "../core/src/parser/parser.yy.cpp" /* yacc.c:358  */

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
#define YYLAST   901

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  191

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    21,     2,     2,     2,    18,    10,     2,
      42,    43,    16,    14,     3,    15,    19,    17,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    41,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,     9,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     8,    47,    22,     2,     2,     2,
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
       6,     7,    11,    12,    13,    20,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    76,    76,    81,    88,    89,    90,    91,    95,    98,
     111,   116,   123,   127,   134,   135,   136,   139,   143,   154,
     155,   160,   168,   175,   183,   187,   192,   200,   208,   209,
     216,   221,   222,   223,   224,   225,   226,   227,   231,   236,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   255,   259,   263,   267,   271,   275,   279,   282,
     285,   288,   291,   295,   296,   299,   303,   307,   313,   318,
     323,   327,   331,   335,   339,   343,   347,   351,   357,   361,
     367,   373,   379,   388,   389,   394,   401,   410,   411,   418,
     419,   423,   432,   433,   437,   438,   439,   443,   454,   467,
     472,   480,   490,   491,   492,   496,   506,   507,   508,   513,
     518,   526,   531
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "','", "ASSIGN", "OP_ASSIGN", "\"||\"",
  "\"&&\"", "'|'", "'^'", "'&'", "EQ", "CMPR", "SHIFT", "'+'", "'-'",
  "'*'", "'/'", "'%'", "'.'", "\"->\"", "'!'", "'~'", "ID", "TYPE",
  "NUMBER", "UNSIGNED", "\"if\"", "\"else if\"", "\"else\"", "\"for\"",
  "\"while\"", "\"++\"", "\"--\"", "STRING", "CHAR", "PREPROC", "RETURN",
  "VOID", "SIZEOF", "OTHER_KEYWORD", "';'", "'('", "')'", "'['", "']'",
  "'{'", "'}'", "$accept", "syntax", "global_def", "preprocessor",
  "func_def", "type", "pointer_type", "type_name", "id", "func_declare",
  "args_declare", "args_declare_element", "array_dimensions", "block",
  "statement_sequence", "statement", "expr", "constant", "array_subscript",
  "type_cast", "prefix_expr", "subfix_expr", "func_call", "sizeof",
  "args_sequence", "if_struct", "else_if_seq", "else_body", "while_struct",
  "empty_or_expr", "for_statement_1", "for_struct", "var_def",
  "var_def_seq", "var_def_element", "var_def_init", "element_init",
  "element_seq", "block_or_line", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    44,   258,   259,   260,   261,   124,    94,
      38,   262,   263,   264,    43,    45,    42,    47,    37,    46,
     265,    33,   126,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,    59,    40,    41,    91,    93,   123,   125
};
# endif

#define YYPACT_NINF -152

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-152)))

#define YYTABLE_NINF -16

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -152,     5,  -152,  -152,  -152,    -5,  -152,  -152,  -152,  -152,
    -152,    -8,     7,  -152,  -152,   -15,     7,  -152,    -6,    37,
    -152,  -152,  -152,   107,     0,    -8,    -8,     4,  -152,   606,
     639,  -152,  -152,  -152,  -152,   107,    32,   795,   795,   795,
     795,   795,   795,     9,  -152,   795,   795,  -152,  -152,    38,
     735,   606,   483,  -152,  -152,  -152,  -152,  -152,  -152,  -152,
    -152,  -152,   153,    -2,  -152,  -152,  -152,  -152,   721,   102,
     102,    96,    70,    70,   795,   483,   483,   735,    11,     6,
      80,   483,  -152,     3,   795,   795,   795,   795,   795,   795,
     795,   795,   795,   795,   795,   795,   795,   795,   795,   795,
     795,  -152,  -152,   795,  -152,   498,   483,    29,    39,   237,
     795,  -152,   606,  -152,   483,   483,   539,   593,   676,   711,
     721,   826,   834,   857,   102,   102,    96,    96,    96,    70,
      70,   195,    59,    62,    63,   765,    66,  -152,  -152,    -8,
    -152,   278,  -152,  -152,  -152,    67,   795,  -152,  -152,  -152,
     483,   483,  -152,  -152,   795,   735,   795,  -152,   319,  -152,
    -152,  -152,   483,   360,   483,    68,  -152,   401,  -152,   554,
     795,   554,  -152,  -152,  -152,   483,    69,  -152,    48,   795,
      90,   554,  -152,    93,   795,  -152,   554,   442,  -152,   554,
    -152
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,    15,    14,     0,     8,    16,     3,     6,
       4,     0,    10,    12,     7,     0,    11,    17,    24,    98,
      99,    13,     5,    19,   102,     0,    23,     0,    20,     0,
       0,   101,    24,   100,    24,     0,     0,     0,     0,     0,
       0,     0,     0,    39,    65,     0,     0,    66,    67,     0,
       0,   106,   103,    40,    44,    45,    42,    43,    63,    64,
     104,    25,     0,    22,    21,    18,    28,     9,    77,    72,
      73,    76,    74,    75,    83,    70,    71,     0,    39,     0,
       0,   108,   107,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    78,    79,     0,    26,     0,    84,     0,     0,     0,
       0,    41,     0,   105,    54,    53,    56,    57,    59,    60,
      58,    55,    52,    51,    46,    47,    48,    49,    50,    61,
      62,     0,     0,     0,     0,     0,     0,    38,    27,     0,
      29,     0,    32,    34,    33,     0,     0,    80,    82,    81,
      69,   109,   110,    68,     0,    94,     0,    36,     0,    37,
      30,    31,    85,     0,    95,     0,    96,     0,    35,     0,
      92,     0,   112,   111,    87,    93,     0,    91,    89,    92,
       0,     0,    86,     0,     0,    90,     0,     0,    97,     0,
      88
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -152,  -152,  -152,  -152,  -152,     2,    41,  -152,    13,  -152,
    -152,    76,   103,   106,  -152,    33,   -29,  -152,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,   -40,
    -152,  -152,     1,  -152,   118,  -152,   -37,  -152,  -151
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     8,     9,    10,   139,    12,    13,    32,    14,
      27,    28,    24,   172,   105,   173,   141,    53,    54,    55,
      56,    57,    58,    59,   107,   142,   178,   182,   143,   176,
     165,   144,   145,    19,    20,    31,    60,    83,   174
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      52,    62,    15,    11,    29,     2,   112,    35,    68,    69,
      70,    71,    72,    73,    82,    17,    75,    76,     3,     4,
     177,    80,    81,    21,    18,    26,    22,   -15,     3,     4,
     185,     5,   146,     7,   -15,   188,    23,    26,   190,    34,
      25,     6,    30,     7,    30,   106,    16,    36,   109,   110,
     113,    74,    79,    74,   -15,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   147,    65,   131,   152,   180,   181,    66,   108,
      77,   150,   148,   151,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   154,   101,   102,   155,   156,   158,   159,   161,   170,
     179,    64,   101,   102,   103,    99,   100,   162,    96,    97,
      98,    99,   100,   111,   103,   163,   164,   167,   101,   102,
       3,     4,   184,     5,   101,   102,   186,    63,   140,   183,
     103,   175,    67,    33,     0,     7,   103,     0,     0,     0,
     175,     0,     0,     0,     0,   187,   166,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   101,   102,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   103,   104,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   101,   102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     153,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   101,
     102,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     149,   103,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     101,   102,     0,     0,     0,     0,     0,     0,     0,   160,
       0,     0,   103,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   101,   102,     0,     0,     0,     0,     0,     0,     0,
     168,     0,     0,   103,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   101,   102,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   169,   103,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   101,   102,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   171,   103,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   101,   102,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   189,   103,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,     0,     0,     0,     0,    37,     0,
       0,     0,    38,    39,    40,   101,   102,     0,     0,    41,
      42,    78,     4,    44,     5,   132,     0,   103,   133,   134,
      45,    46,    47,    48,     0,   135,     7,    49,   136,   137,
      50,     0,     0,     0,     0,   138,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
       0,     0,     0,     0,    37,     0,     0,     0,    38,    39,
      40,   101,   102,     0,     0,    41,    42,    78,     4,    44,
       5,   132,     0,   103,   133,   134,    45,    46,    47,    48,
       0,   135,     7,    49,   136,   137,    50,     0,     0,     0,
      66,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,     0,     0,    37,     0,     0,     0,
      38,    39,    40,     0,     0,   101,   102,    41,    42,    43,
       0,    44,     0,     0,     0,     0,     0,   103,    45,    46,
      47,    48,     0,     0,     0,    49,     0,     0,    50,    37,
       0,     0,    51,    38,    39,    40,     0,     0,     0,     0,
      41,    42,    43,     0,    44,     0,     0,     0,     0,     0,
       0,    45,    46,    47,    48,     0,     0,     0,    49,     0,
       0,    50,     0,     0,    61,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   101,   102,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     103,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,     0,   101,   102,    37,     0,     0,     0,    38,
      39,    40,     0,   101,   102,   103,    41,    42,    78,     4,
      44,     5,     0,     0,     0,   103,     0,    45,    46,    47,
      48,     0,     0,     7,    49,    37,     0,    50,     0,    38,
      39,    40,     0,     0,     0,     0,    41,    42,    43,     0,
      44,     0,     0,     0,     0,     0,     0,    45,    46,    47,
      48,     0,     0,     0,    49,    37,   157,    50,     0,    38,
      39,    40,     0,     0,     0,     0,    41,    42,    43,     0,
      44,     0,     0,     0,     0,     0,     0,    45,    46,    47,
      48,     0,     0,     0,    49,     0,     0,    50,    92,    93,
      94,    95,    96,    97,    98,    99,   100,    93,    94,    95,
      96,    97,    98,    99,   100,     0,     0,     0,   101,   102,
       0,     0,     0,     0,     0,     0,   101,   102,     0,     0,
     103,    94,    95,    96,    97,    98,    99,   100,   103,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   101,
     102,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   103
};

static const yytype_int16 yycheck[] =
{
      29,    30,     1,     1,     4,     0,     3,     3,    37,    38,
      39,    40,    41,    42,    51,    23,    45,    46,    23,    24,
     171,    50,    51,    16,    11,    23,    41,    16,    23,    24,
     181,    26,     3,    38,    23,   186,    42,    35,   189,    26,
       3,    36,    44,    38,    44,    74,     5,    43,    77,    43,
      47,    42,    50,    42,    43,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,    43,    41,   103,   112,    28,    29,    46,    77,
      42,   110,    43,   112,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    42,    32,    33,    42,    42,   135,    41,    41,    41,
      41,    35,    32,    33,    44,    19,    20,   146,    16,    17,
      18,    19,    20,    43,    44,   154,   155,   156,    32,    33,
      23,    24,    42,    26,    32,    33,    43,    34,   105,   179,
      44,   170,    36,    25,    -1,    38,    44,    -1,    -1,    -1,
     179,    -1,    -1,    -1,    -1,   184,   155,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      45,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    44,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      -1,    -1,    44,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    -1,    -1,    44,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    44,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    -1,    -1,    -1,    -1,    10,    -1,
      -1,    -1,    14,    15,    16,    32,    33,    -1,    -1,    21,
      22,    23,    24,    25,    26,    27,    -1,    44,    30,    31,
      32,    33,    34,    35,    -1,    37,    38,    39,    40,    41,
      42,    -1,    -1,    -1,    -1,    47,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      -1,    -1,    -1,    -1,    10,    -1,    -1,    -1,    14,    15,
      16,    32,    33,    -1,    -1,    21,    22,    23,    24,    25,
      26,    27,    -1,    44,    30,    31,    32,    33,    34,    35,
      -1,    37,    38,    39,    40,    41,    42,    -1,    -1,    -1,
      46,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    -1,    -1,    10,    -1,    -1,    -1,
      14,    15,    16,    -1,    -1,    32,    33,    21,    22,    23,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    44,    32,    33,
      34,    35,    -1,    -1,    -1,    39,    -1,    -1,    42,    10,
      -1,    -1,    46,    14,    15,    16,    -1,    -1,    -1,    -1,
      21,    22,    23,    -1,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,    34,    35,    -1,    -1,    -1,    39,    -1,
      -1,    42,    -1,    -1,    45,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    -1,    32,    33,    10,    -1,    -1,    -1,    14,
      15,    16,    -1,    32,    33,    44,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    44,    -1,    32,    33,    34,
      35,    -1,    -1,    38,    39,    10,    -1,    42,    -1,    14,
      15,    16,    -1,    -1,    -1,    -1,    21,    22,    23,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    -1,    -1,    -1,    39,    10,    41,    42,    -1,    14,
      15,    16,    -1,    -1,    -1,    -1,    21,    22,    23,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    -1,    -1,    -1,    39,    -1,    -1,    42,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    13,    14,    15,
      16,    17,    18,    19,    20,    -1,    -1,    -1,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    -1,    -1,
      44,    14,    15,    16,    17,    18,    19,    20,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    49,     0,    23,    24,    26,    36,    38,    50,    51,
      52,    53,    54,    55,    57,    80,    54,    23,    56,    81,
      82,    16,    41,    42,    60,     3,    53,    58,    59,     4,
      44,    83,    56,    82,    56,     3,    43,    10,    14,    15,
      16,    21,    22,    23,    25,    32,    33,    34,    35,    39,
      42,    46,    64,    65,    66,    67,    68,    69,    70,    71,
      84,    45,    64,    60,    59,    41,    46,    61,    64,    64,
      64,    64,    64,    64,    42,    64,    64,    42,    23,    53,
      64,    64,    84,    85,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    32,    33,    44,    45,    62,    64,    72,    53,    64,
      43,    43,     3,    47,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    27,    30,    31,    37,    40,    41,    47,    53,
      63,    64,    73,    76,    79,    80,     3,    43,    43,    43,
      64,    64,    84,    45,    42,    42,    42,    41,    64,    41,
      41,    41,    64,    64,    64,    78,    80,    64,    41,    43,
      41,    43,    61,    63,    86,    64,    77,    86,    74,    41,
      28,    29,    75,    77,    42,    86,    43,    64,    86,    43,
      86
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    49,    50,    50,    50,    50,    51,    52,
      53,    53,    54,    54,    55,    55,    55,    56,    57,    58,
      58,    58,    59,    59,    60,    60,    60,    61,    62,    62,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    65,    65,    65,    66,    67,
      68,    68,    68,    68,    68,    68,    68,    68,    69,    69,
      70,    71,    71,    72,    72,    72,    73,    74,    74,    75,
      75,    76,    77,    77,    78,    78,    78,    79,    80,    81,
      81,    82,    83,    83,    83,    84,    85,    85,    85,    85,
      85,    86,    86
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     1,     1,     1,     6,
       1,     2,     1,     2,     1,     1,     1,     1,     6,     0,
       1,     3,     3,     1,     0,     3,     4,     3,     0,     2,
       2,     2,     1,     1,     1,     3,     2,     2,     1,     1,
       1,     3,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     4,     4,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       4,     4,     4,     0,     1,     3,     7,     0,     6,     0,
       2,     5,     0,     1,     0,     1,     1,     9,     2,     1,
       3,     3,     0,     2,     2,     3,     0,     1,     1,     3,
       3,     1,     1
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
#line 76 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        auto ast = new ASTTree;
        ASTCallback(ast);
        (yyval) = ast;
    }
#line 1538 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 81 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
                ASTTree* root = (ASTTree*)(yyvsp[-1]);
                root->globals->push_back((FunctionDefine*)(yyvsp[0]));
                (yyval) = root;
            }
#line 1548 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 88 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1554 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 89 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1560 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 90 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1566 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 91 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1572 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 95 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1578 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 98 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
    auto f = new FunctionDefine;
    ListNode<VariableDefine>* args = (ListNode<VariableDefine>*)(yyvsp[-2]);
    f->name = ((TokenNode*)(yyvsp[-4]))->token.name;
    f->type = (TypeNode*)(yyvsp[-5]);
    f->id = (TokenNode*)(yyvsp[-4]);
    f->args = args->list;
    f->body = (BlockNode*)(yyvsp[0]);
    delete args;
    (yyval) = f;
 }
#line 1594 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 111 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        TypeNode* type = (TypeNode*)(yyvsp[0]);
        type->sign = true;
        (yyval) = type;
    }
#line 1604 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 116 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        TypeNode* type = (TypeNode*)(yyvsp[0]);
        type->sign = false;
        (yyval) = type;
    }
#line 1614 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 123 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        EXTRACT_TOKEN(type, (yyvsp[0]))
        (yyval) = new TypeNode(true, type);
    }
#line 1623 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 127 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        TypeNode* type = (TypeNode*)(yyvsp[-1]);
        type->pointerLevel++;
        (yyval) = type;
    }
#line 1633 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 134 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1639 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 135 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1645 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 136 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1651 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 139 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1657 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 143 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto declare = new FunctionDeclare;
        declare->type = (TypeNode*)(yyvsp[-5]);
        declare->id = (TokenNode*)(yyvsp[-4]);
        declare->args = ((ListNode<VariableDefine>*)(yyvsp[-2]))->list;
        delete (yyvsp[-2]);
        (yyval) = declare;
    }
#line 1670 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 154 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new ListNode<VariableDefine>; }
#line 1676 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 155 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto list = new ListNode<VariableDefine>;
        list->list->push_back((VariableDefine*)(yyvsp[0]));
        (yyval) = list;
    }
#line 1686 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 160 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        ListNode<VariableDefine>* list = (ListNode<VariableDefine>*)(yyvsp[-2]);
        list->list->push_back((VariableDefine*)(yyvsp[0]));
        (yyval) = list;
    }
#line 1696 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 168 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto arg = new VariableDefine((TypeNode*)(yyvsp[-2]), (TokenNode*)(yyvsp[-1]), nullptr);
        ListNode<Expression>* arr = (ListNode<Expression>*)(yyvsp[0]);
        arg->arrayDimensions = arr->list;
        delete arr;
        (yyval) = arg;
    }
#line 1708 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 175 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto arg = new VariableDefine((TypeNode*)(yyvsp[0]), nullptr, nullptr);
        arg->arrayDimensions = new vector<Expression*>;
        (yyval) = arg;
    }
#line 1718 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 183 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto node = new ListNode<Expression>;
        (yyval) = node;
    }
#line 1727 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 187 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        ListNode<Expression>* node = (ListNode<Expression>*)(yyvsp[-2]);
        node->list->push_back(nullptr);
        (yyval) = node;
    }
#line 1737 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 192 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        ListNode<Expression>* node = (ListNode<Expression>*)(yyvsp[-3]);
        node->list->push_back((Expression*)(yyvsp[-1]));
        (yyval) = node;
    }
#line 1747 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 200 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        auto block = new BlockNode; 
        block->statements = ((ListNode<Statement>*)(yyvsp[-1]))->list;
        delete (yyvsp[-1]);
        (yyval) = block;
    }
#line 1758 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 208 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new ListNode<Statement>; }
#line 1764 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 209 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto list = (ListNode<Statement>*) (yyvsp[-1]);
        list->list->push_back((Statement*)(yyvsp[0]));
        (yyval) = list;
    }
#line 1774 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 216 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        auto s = new ExpressionStatement;
        s->expression = (Expression*)(yyvsp[-1]);
        (yyval) = s;
    }
#line 1784 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 221 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); }
#line 1790 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 222 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1796 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 223 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1802 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 224 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1808 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 225 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new ReturnStatement((Expression*)(yyvsp[-1])); }
#line 1814 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 226 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new ReturnStatement(nullptr); }
#line 1820 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 227 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(keyword, (yyvsp[-1]))
        (yyval) = new KeywordStatement(keyword);
    }
#line 1829 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 231 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new EmptyStatement; }
#line 1835 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 236 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
            EXTRACT_TOKEN(token, (yyvsp[0]))
            (yyval) = new Variable(token);
        }
#line 1844 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 240 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1850 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 241 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (Expression*)(yyvsp[-1]); }
#line 1856 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 242 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1862 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 243 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1868 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 244 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1874 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 245 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1880 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 246 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new InfixExpr("+", (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0])); }
#line 1886 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 247 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new InfixExpr("-", (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0])); }
#line 1892 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 248 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new InfixExpr("*", (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0])); }
#line 1898 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 249 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new InfixExpr("/", (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0])); }
#line 1904 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 250 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new InfixExpr("%", (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0])); }
#line 1910 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 251 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[-1]))
        (yyval) = new InfixExpr(op.name, (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1919 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 255 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[-1]))
        (yyval) = new InfixExpr(op.name, (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1928 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 259 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[-1]))
        (yyval) = new InfixExpr(op.name, (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1937 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 263 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[-1]))
        (yyval) = new InfixExpr(op.name, (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1946 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 267 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[-1]))
        (yyval) = new InfixExpr(op.name, (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1955 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 271 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[-1]))
        (yyval) = new InfixExpr(op.name, (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1964 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 275 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[-1]))
        (yyval) = new InfixExpr(op.name, (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1973 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 279 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        (yyval) = new InfixExpr("&", (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1981 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 282 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        (yyval) = new InfixExpr("|", (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1989 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 285 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        (yyval) = new InfixExpr("^", (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 1997 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 288 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        (yyval) = new InfixExpr(".", (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 2005 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 291 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[-1]))
        (yyval) = new InfixExpr(op.name, (Expression*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
    }
#line 2014 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 295 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2020 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 296 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2026 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 299 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(num, (yyvsp[0]))
        (yyval) = new Constant(num);
    }
#line 2035 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 303 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(str, (yyvsp[0]))
        (yyval) = new Constant(str);
    }
#line 2044 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 307 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(chr, (yyvsp[0]))
        (yyval) = new Constant(chr);
    }
#line 2053 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 313 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        (yyval) =  new ArraySubscript((Expression*)(yyvsp[-3]), (Expression*)(yyvsp[-1]));
    }
#line 2061 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 318 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
    (yyval) = new TypeCast((TypeNode*)(yyvsp[-2]), (Expression*)(yyvsp[0]));
}
#line 2069 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 323 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[-1]))
        (yyval) = new PrefixExpr(op, (Expression*) (yyvsp[0]));
    }
#line 2078 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 327 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[-1]))
        (yyval) = new PrefixExpr(op, (Expression*) (yyvsp[0]));
    }
#line 2087 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 331 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        Token op = {"+", "+"};
        (yyval) = new PrefixExpr(op, (Expression*) (yyvsp[0]));
    }
#line 2096 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 335 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        Token op = {"-", "-"};
        (yyval) = new PrefixExpr(op, (Expression*) (yyvsp[0]));
    }
#line 2105 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 339 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        Token op = {"!", "!"};
        (yyval) = new PrefixExpr(op, (Expression*) (yyvsp[0]));
    }
#line 2114 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 343 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        Token op = {"~", "~"};
        (yyval) = new PrefixExpr(op, (Expression*) (yyvsp[0]));
    }
#line 2123 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 347 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        Token op = {"*", "*"};
        (yyval) = new PrefixExpr(op, (Expression*) (yyvsp[0]));
    }
#line 2132 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 351 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        Token op = {"&", "&"};
        (yyval) = new PrefixExpr(op, (Expression*) (yyvsp[0]));
    }
#line 2141 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 357 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[0]))
        (yyval) = new SubfixExpr((Expression*)(yyvsp[-1]), op);
    }
#line 2150 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 361 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(op, (yyvsp[0]))
        (yyval) = new SubfixExpr((Expression*)(yyvsp[-1]), op);
    }
#line 2159 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 367 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        EXTRACT_TOKEN(id, (yyvsp[-3]))
        (yyval) = new FunctionInvokeNode(id, (ListNode<Expression>*)(yyvsp[-1]));
    }
#line 2168 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 373 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(id, (yyvsp[-3]))
        auto listNode = new ListNode<Expression>;
        listNode->list->push_back((Expression*)(yyvsp[-1]));
        (yyval) = new FunctionInvokeNode(id, listNode);
    }
#line 2179 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 379 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        EXTRACT_TOKEN(id, (yyvsp[-3]))
        auto listNode = new ListNode<Expression>;
        listNode->list->push_back((Expression*)(yyvsp[-1]));
        (yyval) = new FunctionInvokeNode(id, listNode);
    }
#line 2190 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 388 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new ListNode<Expression>; }
#line 2196 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 389 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto list = new ListNode<Expression>;
        list->list->push_back((Expression*) (yyvsp[0]));
        (yyval) = list;
    }
#line 2206 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 394 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        ListNode<Expression>* list = (ListNode<Expression>*)(yyvsp[-2]);
        list->list->push_back((Expression*) (yyvsp[0]));
        (yyval) = list;
    }
#line 2216 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 401 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto if_struct = new If((Expression*)(yyvsp[-4]), (BlockNode*)(yyvsp[-2]));
        if_struct->elseif = ((ListNode<ConditionStructure>*)(yyvsp[-1]))->list;
        delete (yyvsp[-1]);
        if_struct->elseBody = (BlockNode*)(yyvsp[0]);
        (yyval) = if_struct;
    }
#line 2228 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 410 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new ListNode<ConditionStructure>; }
#line 2234 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 411 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        ListNode<ConditionStructure>* node = (ListNode<ConditionStructure>*)(yyvsp[-5]);
        node->list->push_back(new ConditionStructure((Expression*)(yyvsp[-2]), (BlockNode*)(yyvsp[0])));
        (yyval) = node;
    }
#line 2244 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 418 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = nullptr; }
#line 2250 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 419 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2256 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 423 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto loop = new ForLoop;
        loop->s2 = (Expression*)(yyvsp[-2]);
        loop->body = (BlockNode*)(yyvsp[0]);
        (yyval) = loop;
    }
#line 2267 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 432 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = nullptr; }
#line 2273 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 433 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2279 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 437 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = nullptr; }
#line 2285 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 438 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2291 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 439 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2297 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 443 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto loop = new ForLoop;
        loop->s1 = (Expression*)(yyvsp[-6]);
        loop->s2 = (Expression*)(yyvsp[-4]);
        loop->s3 = (Expression*)(yyvsp[-2]);
        loop->body = (BlockNode*)(yyvsp[0]);
        (yyval) = loop;
    }
#line 2310 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 454 "../core/src/parser/c.y" /* yacc.c:1646  */
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
#line 2325 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 467 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        auto seq = new ListNode<VariableDefine>;
        seq->list->push_back((VariableDefine*)(yyvsp[0]));
        (yyval) =  seq;
    }
#line 2335 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 472 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        ListNode<VariableDefine>* seq = (ListNode<VariableDefine>*)(yyvsp[-2]);
        seq->list->push_back((VariableDefine*)(yyvsp[0]));
        (yyval) = seq;
    }
#line 2345 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 480 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        auto var = new VariableDefine(nullptr, (TokenNode*)(yyvsp[-2]), (Expression*)(yyvsp[0])); 
        ListNode<Expression>* arr = (ListNode<Expression>*)(yyvsp[-1]);
        var->arrayDimensions = arr->list;
        delete arr;
        (yyval) = var;
    }
#line 2357 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 490 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = nullptr; }
#line 2363 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 491 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2369 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 492 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2375 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 496 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto init = new StructInit;
        ListNode<Expression>* elements = (ListNode<Expression>*)(yyvsp[-1]);
        init->elements = elements->list;
        delete elements;
        (yyval) = init;
    }
#line 2387 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 506 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = new ListNode<Expression>; }
#line 2393 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 507 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2399 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 508 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        auto elements = new ListNode<Expression>;
        elements->list->push_back((Expression*)(yyvsp[0]));
        (yyval) = elements;
    }
#line 2409 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 513 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        ListNode<Expression>* elements = (ListNode<Expression>*)(yyvsp[-2]);
        elements->list->push_back((Expression*)(yyvsp[0]));
        (yyval) = elements;
    }
#line 2419 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 518 "../core/src/parser/c.y" /* yacc.c:1646  */
    {
        ListNode<Expression>* elements = (ListNode<Expression>*)(yyvsp[-2]);
        elements->list->push_back((Expression*)(yyvsp[0]));
        (yyval) = elements;
    }
#line 2429 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 526 "../core/src/parser/c.y" /* yacc.c:1646  */
    { 
        auto block = new BlockNode;
        block->statements->push_back((Statement*)(yyvsp[0]));
        (yyval) = block;
    }
#line 2439 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 531 "../core/src/parser/c.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2445 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
    break;


#line 2449 "../core/src/parser/parser.yy.cpp" /* yacc.c:1646  */
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
#line 534 "../core/src/parser/c.y" /* yacc.c:1906  */


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
    TokenMap["void"] = VOID;
    TokenMap["unsigned"] = UNSIGNED;
    TokenMap["if"] = IF;
    TokenMap["else if"] = ELSEIF;
    TokenMap["else"] = ELSE;
    TokenMap["for"] = FOR;
    TokenMap["while"] = WHILE;
    TokenMap["sizeof"] = SIZEOF;
    TokenMap["||"] = OR;
    TokenMap["&&"] = AND;
    TokenMap["<"] = TokenMap[">"] = TokenMap["<="] = TokenMap[">="] = CMPR;
    TokenMap["<<"] = TokenMap[">>"] = SHIFT;
    TokenMap["=="] = TokenMap["!="] = EQ;
    TokenMap["="] = ASSIGN;
    TokenMap["+="]
        =TokenMap["-="]
        =TokenMap["*="]
        =TokenMap["/="]
        =TokenMap["%="]
        =TokenMap["<<="]
        =TokenMap[">>="]
        =TokenMap["&="]
        =TokenMap["^="]
        =TokenMap["|="] = OP_ASSIGN;
    TokenMap["++"] = INC;
    TokenMap["--"] = DEC;
    TokenMap["->"] = PTR_MBR;
    TokenMap["const-string"] = STRING;
    TokenMap["const-char"] = CHAR;
    TokenMap["preprocessor"] = PREPROC;
    TokenMap["return"] = RETURN;
    TokenMap["break"]
        =TokenMap["continue"]
        = OTHER_KEYWORD;
}

int yylex()
{
    auto t = (int)idx >= (int)(TokenList->size());
    if(t)
        return 0;
    
    latestToken = TokenList->at(idx);

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
