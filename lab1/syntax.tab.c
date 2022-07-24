/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./syntax.y"

    #include<stdarg.h>
    #include<stdio.h>
    
    #include<string.h>
    extern int yylineno;
    extern int flagoferror;
    enum NodeType{TypeToken,TypeNontoken};
    enum TokenType{Typeint,Typefloat,Typeid,Typenon};
    struct TreeNode{
        char* Name;
        int Numofline;
        int Numofchild;
        enum NodeType nodetype;
        enum TokenType tokentype;
        union{
            int Intval;
            float Floatval;
            char* Charval;
        }data;
        struct TreeNode* Child;
        struct TreeNode* Sibling;
    };
    struct TreeNode* root = NULL;

    struct TreeNode* BuildTree(char* nodeName, enum NodeType nodeType, int lineNum, int childNum ,...);
    struct TreeNode* CreateLeaf(char* nodeName, enum NodeType nodeType,int lineNum, enum TokenType tokentype, ...);
    void PrintTree(struct TreeNode* Node, int Space);

#line 100 "./syntax.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
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
    SEMI = 258,
    COMMA = 259,
    DOT = 260,
    LP = 261,
    RP = 262,
    LB = 263,
    RB = 264,
    LC = 265,
    RC = 266,
    ASSIGNOP = 267,
    RELOP = 268,
    PLUS = 269,
    MINUS = 270,
    STAR = 271,
    DIV = 272,
    AND = 273,
    OR = 274,
    NOT = 275,
    STRUCT = 276,
    RETURN = 277,
    IF = 278,
    ELSE = 279,
    WHILE = 280,
    INT = 281,
    FLOAT = 282,
    TYPE = 283,
    ID = 284,
    NEGMINUS = 285,
    LOWER_THAN_ELSE = 286
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 32 "./syntax.y"

    int type_int;
    float type_float;
    char* type_string;
    struct TreeNode* Node;

#line 191 "./syntax.tab.c"

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


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   427

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  153

#define YYUNDEFTOK  2
#define YYMAXUTOK   286


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    84,    84,    86,    87,    89,    91,    92,    93,    94,
      96,    97,    98,    99,   100,   102,   103,   107,   109,   111,
     115,   116,   119,   121,   123,   127,   129,   134,   138,   143,
     145,   147,   150,   154,   155,   157,   159,   161,   162,   165,
     166,   170,   171,   172,   177,   178,   182,   185,   186,   188,
     190,   191,   193,   194,   197,   198,   202,   204,   205,   207,
     208,   210,   211,   213,   214,   216,   217,   219,   220,   222,
     223,   225,   226,   229,   230,   232,   233,   235,   236,   240,
     241,   245,   248,   250,   253,   256,   258,   261,   263
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMI", "COMMA", "DOT", "LP", "RP", "LB",
  "RB", "LC", "RC", "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV",
  "AND", "OR", "NOT", "STRUCT", "RETURN", "IF", "ELSE", "WHILE", "INT",
  "FLOAT", "TYPE", "ID", "NEGMINUS", "LOWER_THAN_ELSE", "$accept",
  "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286
};
# endif

#define YYPACT_NINF (-41)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-35)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      42,    16,   -28,   -41,    15,   -41,    42,     8,   -41,   -41,
      -5,   -41,    -3,    10,   -41,   -41,   -41,    55,   -41,    25,
      84,    58,    11,    27,     7,    -5,    -5,   -41,   -41,    61,
      38,   -41,    30,    35,   -41,    87,   -41,    59,   164,    69,
      54,   116,   129,   133,   242,    78,    88,   -41,   -41,    96,
     -41,   104,     7,   286,   -41,    13,   -41,    30,   109,   115,
     -41,   -41,   119,   -41,   242,   130,   -41,    30,   -41,   -41,
     125,   317,   -41,    70,   -41,    70,   269,   146,   162,    85,
     -41,   -41,   -41,   111,   170,   178,   186,   194,   202,   210,
     218,   226,   234,   135,   -41,   142,   -41,    -5,   -41,   377,
     -41,   -41,   -41,   -41,   -41,   -41,   134,   332,   144,   347,
     147,   -41,   302,   150,   -41,   155,   362,   -41,   377,   -41,
     410,   -41,   121,   -41,   121,   -41,    70,   -41,    70,   -41,
     406,   -41,   392,   -41,   -41,    98,    98,    98,    98,   -41,
     242,   -41,   -41,   -41,   145,   154,   -41,   -41,   -41,    98,
      98,   -41,   -41
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    23,    17,     0,     2,     0,     0,    18,    10,
      48,    14,    24,     0,    21,     1,     3,    11,     9,    25,
       0,    15,     0,     0,     0,    48,    48,     7,    13,     0,
       8,     5,     0,     0,    12,     0,    25,    54,     0,    52,
       0,     0,     0,     0,     0,     0,     0,    85,    86,    84,
      37,     0,     0,     0,    47,     0,    28,     0,     0,    30,
       6,    16,     0,    50,     0,     0,    49,     0,    36,    42,
       0,     0,    75,    74,    77,    76,     0,     0,     0,     0,
      32,    33,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    19,    31,    27,     0,    26,    55,
      51,    53,    73,    72,    39,    38,     0,     0,     0,     0,
       0,    80,    88,     0,    83,     0,     0,    57,    56,    63,
      62,    65,    64,    67,    66,    69,    68,    71,    70,    59,
      58,    61,    60,    20,    29,     0,     0,     0,     0,    79,
       0,    78,    82,    81,    41,    40,    46,    45,    87,     0,
       0,    44,    43
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -41,   -41,   168,   -41,   138,     6,   -41,   -41,   -41,   -13,
     -41,    83,   -41,    71,   131,   -40,    81,   -41,   114,   -41,
     -39,    46
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    20,    23,     8,    13,    14,    21,
      22,    58,    59,    50,    51,    52,    24,    25,    38,    39,
      53,   113
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      69,    12,    71,    73,    75,    76,     7,   -22,    40,    17,
      37,    18,     7,    41,    93,    15,     2,    10,   -34,     9,
      26,    10,    42,     3,    94,    99,    10,    43,    35,    44,
      45,    29,    46,    47,    48,    57,    49,    19,   107,   109,
     112,    60,    -4,     1,    95,   116,   118,   120,   122,   124,
     126,   128,   130,   132,    37,    40,    36,    68,    27,    36,
      41,    62,    32,     2,    10,    10,    33,    33,    56,    42,
       3,    64,    11,    67,    43,    83,    44,    45,    84,    46,
      47,    48,     2,    49,    77,    30,   110,    31,    28,     3,
      63,    41,   111,    34,    78,   144,   145,   146,   147,    40,
      42,   112,    79,    57,    41,    43,    54,    55,    10,   151,
     152,    47,    48,    42,    49,    80,    96,    70,    43,    97,
      44,    45,    41,    46,    47,    48,    83,    49,    98,    84,
      72,    42,   102,   100,    74,    41,    43,    89,    90,    41,
     114,   135,    47,    48,    42,    49,   133,   106,    42,    43,
      33,   137,    41,    43,   139,    47,    48,   141,    49,    47,
      48,    42,    49,   108,   142,    65,    43,    66,    41,   149,
      61,   115,    47,    48,    16,    49,    41,    42,   150,   117,
     134,   101,    43,    81,    41,    42,   148,   119,    47,    48,
      43,    49,    41,    42,     0,   121,    47,    48,    43,    49,
      41,    42,     0,   123,    47,    48,    43,    49,    41,    42,
       0,   125,    47,    48,    43,    49,    41,    42,     0,   127,
      47,    48,    43,    49,    41,    42,     0,   129,    47,    48,
      43,    49,    41,    42,     0,   131,    47,    48,    43,    49,
      41,    42,     0,     0,    47,    48,    43,    49,    41,    42,
       0,     0,    47,    48,    43,    49,     0,    42,     0,     0,
      47,    48,    43,    49,     0,     0,     0,     0,    47,    48,
     104,    49,   105,     0,    83,     0,     0,    84,     0,     0,
       0,    85,    86,    87,    88,    89,    90,    91,    92,    82,
       0,    83,     0,     0,    84,     0,     0,     0,    85,    86,
      87,    88,    89,    90,    91,    92,   140,    83,     0,     0,
      84,     0,     0,     0,    85,    86,    87,    88,    89,    90,
      91,    92,    83,     0,   103,    84,     0,     0,     0,    85,
      86,    87,    88,    89,    90,    91,    92,    83,     0,   136,
      84,     0,     0,     0,    85,    86,    87,    88,    89,    90,
      91,    92,    83,     0,   138,    84,     0,     0,     0,    85,
      86,    87,    88,    89,    90,    91,    92,    83,     0,     0,
      84,   143,     0,     0,    85,    86,    87,    88,    89,    90,
      91,    92,    83,     0,     0,    84,     0,     0,     0,    85,
      86,    87,    88,    89,    90,    91,    92,    83,     0,     0,
      84,     0,     0,     0,     0,    86,    87,    88,    89,    90,
      91,    83,     0,     0,    84,    83,     0,     0,    84,    86,
      87,    88,    89,    90,    87,    88,    89,    90
};

static const yytype_int16 yycheck[] =
{
      40,    29,    41,    42,    43,    44,     0,    10,     1,     1,
      23,     3,     6,     6,     1,     0,    21,    10,    11,     3,
      10,    10,    15,    28,    11,    64,    10,    20,     1,    22,
      23,     6,    25,    26,    27,    29,    29,    29,    77,    78,
      79,     3,     0,     1,    57,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    67,     1,    29,     3,     3,    29,
       6,    26,     4,    21,    10,    10,     8,     8,     7,    15,
      28,    12,     1,     4,    20,     5,    22,    23,     8,    25,
      26,    27,    21,    29,     6,     1,     1,     3,    17,    28,
       3,     6,     7,    22,     6,   135,   136,   137,   138,     1,
      15,   140,     6,    97,     6,    20,    25,    26,    10,   149,
     150,    26,    27,    15,    29,    11,     7,     1,    20,     4,
      22,    23,     6,    25,    26,    27,     5,    29,     9,     8,
       1,    15,     7,     3,     1,     6,    20,    16,    17,     6,
      29,     7,    26,    27,    15,    29,    11,     1,    15,    20,
       8,     7,     6,    20,     7,    26,    27,     7,    29,    26,
      27,    15,    29,     1,     9,     1,    20,     3,     6,    24,
      32,     1,    26,    27,     6,    29,     6,    15,    24,     1,
      97,    67,    20,    52,     6,    15,   140,     1,    26,    27,
      20,    29,     6,    15,    -1,     1,    26,    27,    20,    29,
       6,    15,    -1,     1,    26,    27,    20,    29,     6,    15,
      -1,     1,    26,    27,    20,    29,     6,    15,    -1,     1,
      26,    27,    20,    29,     6,    15,    -1,     1,    26,    27,
      20,    29,     6,    15,    -1,     1,    26,    27,    20,    29,
       6,    15,    -1,    -1,    26,    27,    20,    29,     6,    15,
      -1,    -1,    26,    27,    20,    29,    -1,    15,    -1,    -1,
      26,    27,    20,    29,    -1,    -1,    -1,    -1,    26,    27,
       1,    29,     3,    -1,     5,    -1,    -1,     8,    -1,    -1,
      -1,    12,    13,    14,    15,    16,    17,    18,    19,     3,
      -1,     5,    -1,    -1,     8,    -1,    -1,    -1,    12,    13,
      14,    15,    16,    17,    18,    19,     4,     5,    -1,    -1,
       8,    -1,    -1,    -1,    12,    13,    14,    15,    16,    17,
      18,    19,     5,    -1,     7,     8,    -1,    -1,    -1,    12,
      13,    14,    15,    16,    17,    18,    19,     5,    -1,     7,
       8,    -1,    -1,    -1,    12,    13,    14,    15,    16,    17,
      18,    19,     5,    -1,     7,     8,    -1,    -1,    -1,    12,
      13,    14,    15,    16,    17,    18,    19,     5,    -1,    -1,
       8,     9,    -1,    -1,    12,    13,    14,    15,    16,    17,
      18,    19,     5,    -1,    -1,     8,    -1,    -1,    -1,    12,
      13,    14,    15,    16,    17,    18,    19,     5,    -1,    -1,
       8,    -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,
      18,     5,    -1,    -1,     8,     5,    -1,    -1,     8,    13,
      14,    15,    16,    17,    14,    15,    16,    17
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    21,    28,    33,    34,    35,    37,    38,     3,
      10,    45,    29,    39,    40,     0,    34,     1,     3,    29,
      36,    41,    42,    37,    48,    49,    10,     3,    45,     6,
       1,     3,     4,     8,    45,     1,    29,    41,    50,    51,
       1,     6,    15,    20,    22,    23,    25,    26,    27,    29,
      45,    46,    47,    52,    48,    48,     7,    37,    43,    44,
       3,    36,    26,     3,    12,     1,     3,     4,     3,    47,
       1,    52,     1,    52,     1,    52,    52,     6,     6,     6,
      11,    46,     3,     5,     8,    12,    13,    14,    15,    16,
      17,    18,    19,     1,    11,    41,     7,     4,     9,    52,
       3,    50,     7,     7,     1,     3,     1,    52,     1,    52,
       1,     7,    52,    53,    29,     1,    52,     1,    52,     1,
      52,     1,    52,     1,    52,     1,    52,     1,    52,     1,
      52,     1,    52,    11,    43,     7,     7,     7,     7,     7,
       4,     7,     9,     9,    47,    47,    47,    47,    53,    24,
      24,    47,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    35,    35,
      35,    35,    35,    35,    35,    36,    36,    37,    37,    38,
      38,    38,    39,    39,    40,    41,    41,    42,    42,    43,
      43,    44,    45,    46,    46,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    48,    48,    49,
      49,    49,    50,    50,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    53,    53
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     4,     3,     3,     2,
       2,     2,     3,     3,     2,     1,     3,     1,     1,     5,
       6,     2,     1,     0,     1,     1,     4,     4,     3,     3,
       1,     2,     4,     2,     0,     2,     2,     1,     3,     3,
       5,     5,     2,     7,     7,     5,     5,     2,     0,     3,
       3,     4,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     2,     4,     4,
       3,     4,     4,     3,     1,     1,     1,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 84 "./syntax.y"
                     {(yyval.Node) = BuildTree("Program",TypeNontoken,(yyloc).first_line,1,(yyvsp[0].Node));root = (yyval.Node); }
#line 1634 "./syntax.tab.c"
    break;

  case 3:
#line 86 "./syntax.y"
                               {(yyval.Node) = BuildTree("ExtDefList",TypeNontoken,(yyloc).first_line,2,(yyvsp[-1].Node),(yyvsp[0].Node));}
#line 1640 "./syntax.tab.c"
    break;

  case 4:
#line 87 "./syntax.y"
      {(yyval.Node) = NULL;}
#line 1646 "./syntax.tab.c"
    break;

  case 5:
#line 89 "./syntax.y"
                                   {struct TreeNode* nodeSEMI = CreateLeaf("SEMI", TypeToken, (yylsp[0]).first_line, Typenon);
                                    (yyval.Node) = BuildTree("ExtDef",TypeNontoken,(yyloc).first_line,3,(yyvsp[-2].Node),(yyvsp[-1].Node),nodeSEMI);}
#line 1653 "./syntax.tab.c"
    break;

  case 9:
#line 94 "./syntax.y"
                     {struct TreeNode* nodeSEMI = CreateLeaf("SEMI", TypeToken, (yylsp[0]).first_line, Typenon);
                        (yyval.Node) = BuildTree("ExtDef",TypeNontoken,(yyloc).first_line,2,(yyvsp[-1].Node),nodeSEMI);}
#line 1660 "./syntax.tab.c"
    break;

  case 12:
#line 98 "./syntax.y"
                              {(yyval.Node) = BuildTree("ExtDef",TypeNontoken,(yyloc).first_line,3,(yyvsp[-2].Node),(yyvsp[-1].Node),(yyvsp[0].Node));}
#line 1666 "./syntax.tab.c"
    break;

  case 15:
#line 102 "./syntax.y"
                    {(yyval.Node) = BuildTree("ExtDecList",TypeNontoken,(yyloc).first_line,1,(yyvsp[0].Node));}
#line 1672 "./syntax.tab.c"
    break;

  case 16:
#line 103 "./syntax.y"
                              {struct TreeNode* nodeCOMMA = CreateLeaf("COMMA", TypeToken, (yylsp[-1]).first_line, Typenon);
                                (yyval.Node) = BuildTree("ExtDecList",TypeNontoken,(yyloc).first_line,3,(yyvsp[-2].Node),nodeCOMMA,(yyvsp[0].Node));}
#line 1679 "./syntax.tab.c"
    break;

  case 17:
#line 107 "./syntax.y"
                 {struct TreeNode* nodeTYPE = CreateLeaf("TYPE", TypeToken, (yylsp[0]).first_line, Typeid, (yyvsp[0].type_string));
                    (yyval.Node) = BuildTree("Specifier",TypeNontoken,(yyloc).first_line,1,nodeTYPE);}
#line 1686 "./syntax.tab.c"
    break;

  case 18:
#line 109 "./syntax.y"
                      {(yyval.Node) = BuildTree("Specifier",TypeNontoken,(yyloc).first_line,1,(yyvsp[0].Node));}
#line 1692 "./syntax.tab.c"
    break;

  case 19:
#line 111 "./syntax.y"
                                              {struct TreeNode* nodeSTRUCT = CreateLeaf("STRUCT", TypeToken, (yylsp[-4]).first_line, Typenon);
                                                struct TreeNode* nodeLC = CreateLeaf("LC", TypeToken, (yylsp[-2]).first_line, Typenon);
                                                struct TreeNode* nodeRC = CreateLeaf("RC", TypeToken, (yylsp[0]).first_line, Typenon);
                                                (yyval.Node) = BuildTree("StructSpecifier",TypeNontoken,(yyloc).first_line,5,nodeSTRUCT,(yyvsp[-3].Node),nodeLC,(yyvsp[-1].Node),nodeRC);}
#line 1701 "./syntax.tab.c"
    break;

  case 21:
#line 116 "./syntax.y"
                 {struct TreeNode* nodeSTRUCT = CreateLeaf("STRUCT", TypeToken, (yylsp[-1]).first_line, Typenon);
                    (yyval.Node) = BuildTree("StructSpecifier",TypeNontoken,(yyloc).first_line,2,nodeSTRUCT,(yyvsp[0].Node));}
#line 1708 "./syntax.tab.c"
    break;

  case 22:
#line 119 "./syntax.y"
            {struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, (yylsp[0]).first_line, Typeid, (yyvsp[0].type_string));
            (yyval.Node) = BuildTree("OptTag",TypeNontoken,(yyloc).first_line,1,nodeID);}
#line 1715 "./syntax.tab.c"
    break;

  case 23:
#line 121 "./syntax.y"
      {(yyval.Node) = NULL;}
#line 1721 "./syntax.tab.c"
    break;

  case 24:
#line 123 "./syntax.y"
         {struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, (yylsp[0]).first_line, Typeid, (yyvsp[0].type_string));
            (yyval.Node) = BuildTree("Tag",TypeNontoken,(yyloc).first_line,1,nodeID);}
#line 1728 "./syntax.tab.c"
    break;

  case 25:
#line 127 "./syntax.y"
            {struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, (yylsp[0]).first_line, Typeid, (yyvsp[0].type_string));
            (yyval.Node) = BuildTree("VarDec",TypeNontoken,(yyloc).first_line,1,nodeID);}
#line 1735 "./syntax.tab.c"
    break;

  case 26:
#line 129 "./syntax.y"
                       {struct TreeNode* nodeLB = CreateLeaf("LB", TypeToken, (yylsp[-2]).first_line, Typenon);
                struct TreeNode* nodeINT = CreateLeaf("INT", TypeToken, (yylsp[-1]).first_line, Typeint, (yyvsp[-1].type_int));
                struct TreeNode* nodeRB = CreateLeaf("RB", TypeToken, (yylsp[0]).first_line, Typenon);
                (yyval.Node) = BuildTree("VarDec",TypeNontoken,(yyloc).first_line,4,(yyvsp[-3].Node),nodeLB,nodeINT,nodeRB);}
#line 1744 "./syntax.tab.c"
    break;

  case 27:
#line 134 "./syntax.y"
                          {struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, (yylsp[-3]).first_line, Typeid, (yyvsp[-3].type_string));
                struct TreeNode* nodeLP = CreateLeaf("LP", TypeToken, (yylsp[-2]).first_line, Typenon);
                struct TreeNode* nodeRP = CreateLeaf("RP", TypeToken, (yylsp[0]).first_line, Typenon);
                (yyval.Node) = BuildTree("FunDec",TypeNontoken,(yyloc).first_line,4,nodeID,nodeLP,(yyvsp[-1].Node),nodeRP);}
#line 1753 "./syntax.tab.c"
    break;

  case 28:
#line 138 "./syntax.y"
               {struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, (yylsp[-2]).first_line, Typeid, (yyvsp[-2].type_string));
                struct TreeNode* nodeLP = CreateLeaf("LP", TypeToken, (yylsp[-1]).first_line, Typenon);
                struct TreeNode* nodeRP = CreateLeaf("RP", TypeToken, (yylsp[0]).first_line, Typenon);
                (yyval.Node) = BuildTree("FunDec",TypeNontoken,(yyloc).first_line,3,nodeID,nodeLP,nodeRP);}
#line 1762 "./syntax.tab.c"
    break;

  case 29:
#line 143 "./syntax.y"
                                 {struct TreeNode* nodeCOMMA = CreateLeaf("COMMA", TypeToken, (yylsp[-1]).first_line, Typenon);
                                    (yyval.Node) = BuildTree("VarList",TypeNontoken,(yyloc).first_line,3,(yyvsp[-2].Node),nodeCOMMA,(yyvsp[0].Node));}
#line 1769 "./syntax.tab.c"
    break;

  case 30:
#line 145 "./syntax.y"
               {(yyval.Node) = BuildTree("VarList",TypeNontoken,(yyloc).first_line,1,(yyvsp[0].Node));}
#line 1775 "./syntax.tab.c"
    break;

  case 31:
#line 147 "./syntax.y"
                            {(yyval.Node) = BuildTree("ParamDec",TypeNontoken,(yyloc).first_line,2,(yyvsp[-1].Node),(yyvsp[0].Node));}
#line 1781 "./syntax.tab.c"
    break;

  case 32:
#line 150 "./syntax.y"
                                {struct TreeNode* nodeLC = CreateLeaf("LC", TypeToken, (yylsp[-3]).first_line, Typenon);
                                struct TreeNode* nodeRC = CreateLeaf("RC", TypeToken, (yylsp[0]).first_line, Typenon);
                                (yyval.Node) = BuildTree("CompSt",TypeNontoken,(yyloc).first_line,4,nodeLC,(yyvsp[-2].Node),(yyvsp[-1].Node),nodeRC);}
#line 1789 "./syntax.tab.c"
    break;

  case 33:
#line 154 "./syntax.y"
                         {(yyval.Node) = BuildTree("StmtList",TypeNontoken,(yyloc).first_line,2,(yyvsp[-1].Node),(yyvsp[0].Node));}
#line 1795 "./syntax.tab.c"
    break;

  case 34:
#line 155 "./syntax.y"
      {(yyval.Node) = NULL;}
#line 1801 "./syntax.tab.c"
    break;

  case 35:
#line 157 "./syntax.y"
                {struct TreeNode* nodeSEMI = CreateLeaf("SEMI", TypeToken, (yylsp[0]).first_line, Typenon);
                (yyval.Node) = BuildTree("Stmt",TypeNontoken,(yyloc).first_line,2,(yyvsp[-1].Node),nodeSEMI);}
#line 1808 "./syntax.tab.c"
    break;

  case 37:
#line 161 "./syntax.y"
             {(yyval.Node) = BuildTree("Stmt",TypeNontoken,(yyloc).first_line,1,(yyvsp[0].Node));}
#line 1814 "./syntax.tab.c"
    break;

  case 38:
#line 162 "./syntax.y"
                      {struct TreeNode* nodeRETURN = CreateLeaf("RETURN", TypeToken, (yylsp[-2]).first_line, Typenon);
                        struct TreeNode* nodeSEMI = CreateLeaf("SEMI", TypeToken, (yylsp[0]).first_line, Typenon);
                        (yyval.Node) = BuildTree("Stmt",TypeNontoken,(yyloc).first_line,3,nodeRETURN,(yyvsp[-1].Node),nodeSEMI);}
#line 1822 "./syntax.tab.c"
    break;

  case 40:
#line 166 "./syntax.y"
                                              {struct TreeNode* nodeIF = CreateLeaf("IF", TypeToken, (yylsp[-4]).first_line, Typenon);
                            struct TreeNode* nodeLP = CreateLeaf("LP", TypeToken, (yylsp[-3]).first_line, Typenon);
                            struct TreeNode* nodeRP = CreateLeaf("RP", TypeToken, (yylsp[-1]).first_line, Typenon);
                            (yyval.Node) = BuildTree("Stmt",TypeNontoken,(yyloc).first_line,5,nodeIF,nodeLP,(yyvsp[-2].Node),nodeRP,(yyvsp[0].Node));}
#line 1831 "./syntax.tab.c"
    break;

  case 42:
#line 171 "./syntax.y"
                 {yyerrok;}
#line 1837 "./syntax.tab.c"
    break;

  case 43:
#line 172 "./syntax.y"
                                  {struct TreeNode* nodeIF = CreateLeaf("IF", TypeToken, (yylsp[-6]).first_line, Typenon);
                            struct TreeNode* nodeLP = CreateLeaf("LP", TypeToken, (yylsp[-5]).first_line, Typenon);
                            struct TreeNode* nodeRP = CreateLeaf("RP", TypeToken, (yylsp[-3]).first_line, Typenon);
                            struct TreeNode* nodeELSE = CreateLeaf("ELSE", TypeToken, (yylsp[-1]).first_line, Typenon);
                            (yyval.Node) = BuildTree("Stmt",TypeNontoken,(yyloc).first_line,7,nodeIF,nodeLP,(yyvsp[-4].Node),nodeRP,(yyvsp[-2].Node),nodeELSE,(yyvsp[0].Node));}
#line 1847 "./syntax.tab.c"
    break;

  case 45:
#line 178 "./syntax.y"
                           {struct TreeNode* nodeWHILE = CreateLeaf("WHILE", TypeToken, (yylsp[-4]).first_line, Typenon);
                            struct TreeNode* nodeLP = CreateLeaf("LP", TypeToken, (yylsp[-3]).first_line, Typenon);
                            struct TreeNode* nodeRP = CreateLeaf("RP", TypeToken, (yylsp[-1]).first_line, Typenon);
                            (yyval.Node) = BuildTree("Stmt",TypeNontoken,(yyloc).first_line,5,nodeWHILE,nodeLP,(yyvsp[-2].Node),nodeRP,(yyvsp[0].Node));}
#line 1856 "./syntax.tab.c"
    break;

  case 47:
#line 185 "./syntax.y"
                      {(yyval.Node) = BuildTree("DefList",TypeNontoken,(yyloc).first_line,2,(yyvsp[-1].Node),(yyvsp[0].Node));}
#line 1862 "./syntax.tab.c"
    break;

  case 48:
#line 186 "./syntax.y"
      {(yyval.Node) = NULL;}
#line 1868 "./syntax.tab.c"
    break;

  case 49:
#line 188 "./syntax.y"
                             {struct TreeNode* nodeSEMI = CreateLeaf("SEMI", TypeToken, (yylsp[0]).first_line, Typenon);
                                (yyval.Node) = BuildTree("Def",TypeNontoken,(yyloc).first_line,3,(yyvsp[-2].Node),(yyvsp[-1].Node),nodeSEMI);}
#line 1875 "./syntax.tab.c"
    break;

  case 52:
#line 193 "./syntax.y"
              {(yyval.Node) = BuildTree("DecList",TypeNontoken,(yyloc).first_line,1,(yyvsp[0].Node));}
#line 1881 "./syntax.tab.c"
    break;

  case 53:
#line 194 "./syntax.y"
                        {struct TreeNode* nodeCOMMA = CreateLeaf("COMMA", TypeToken, (yylsp[-1]).first_line, Typenon);
                        (yyval.Node) = BuildTree("DecList",TypeNontoken,(yyloc).first_line,3,(yyvsp[-2].Node),nodeCOMMA,(yyvsp[0].Node));}
#line 1888 "./syntax.tab.c"
    break;

  case 54:
#line 197 "./syntax.y"
             {(yyval.Node) = BuildTree("Dec",TypeNontoken,(yyloc).first_line,1,(yyvsp[0].Node));}
#line 1894 "./syntax.tab.c"
    break;

  case 55:
#line 198 "./syntax.y"
                          {struct TreeNode* nodeASSIGNOP = CreateLeaf("ASSIGNOP", TypeToken, (yylsp[-1]).first_line, Typenon);
                            (yyval.Node) = BuildTree("Dec",TypeNontoken,(yyloc).first_line,3,(yyvsp[-2].Node),nodeASSIGNOP,(yyvsp[0].Node));}
#line 1901 "./syntax.tab.c"
    break;

  case 56:
#line 202 "./syntax.y"
                       {struct TreeNode* nodeASSIGNOP = CreateLeaf("ASSIGNOP", TypeToken, (yylsp[-1]).first_line, Typenon);
                        (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,3,(yyvsp[-2].Node),nodeASSIGNOP,(yyvsp[0].Node));}
#line 1908 "./syntax.tab.c"
    break;

  case 58:
#line 205 "./syntax.y"
                  {struct TreeNode* nodeAND = CreateLeaf("AND", TypeToken, (yylsp[-1]).first_line, Typenon);
                    (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,3,(yyvsp[-2].Node),nodeAND,(yyvsp[0].Node));}
#line 1915 "./syntax.tab.c"
    break;

  case 60:
#line 208 "./syntax.y"
                 {struct TreeNode* nodeOR = CreateLeaf("OR", TypeToken, (yylsp[-1]).first_line, Typenon);
                    (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,3,(yyvsp[-2].Node),nodeOR,(yyvsp[0].Node));}
#line 1922 "./syntax.tab.c"
    break;

  case 62:
#line 211 "./syntax.y"
                    {struct TreeNode* nodeRELOP = CreateLeaf("RELOP", TypeToken, (yylsp[-1]).first_line, Typenon);
                    (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,3,(yyvsp[-2].Node),nodeRELOP,(yyvsp[0].Node));}
#line 1929 "./syntax.tab.c"
    break;

  case 64:
#line 214 "./syntax.y"
                   {struct TreeNode* nodePLUS = CreateLeaf("PLUS", TypeToken, (yylsp[-1]).first_line, Typenon);
                    (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,3,(yyvsp[-2].Node),nodePLUS,(yyvsp[0].Node));}
#line 1936 "./syntax.tab.c"
    break;

  case 66:
#line 217 "./syntax.y"
                    {struct TreeNode* nodeMINUS = CreateLeaf("MINUS", TypeToken, (yylsp[-1]).first_line, Typenon);
                    (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,3,(yyvsp[-2].Node),nodeMINUS,(yyvsp[0].Node));}
#line 1943 "./syntax.tab.c"
    break;

  case 68:
#line 220 "./syntax.y"
                   {struct TreeNode* nodeSTAR = CreateLeaf("STAR", TypeToken, (yylsp[-1]).first_line, Typenon);
                    (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,3,(yyvsp[-2].Node),nodeSTAR,(yyvsp[0].Node));}
#line 1950 "./syntax.tab.c"
    break;

  case 70:
#line 223 "./syntax.y"
                  {struct TreeNode* nodeDIV = CreateLeaf("DIV", TypeToken, (yylsp[-1]).first_line, Typenon);
                    (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,3,(yyvsp[-2].Node),nodeDIV,(yyvsp[0].Node));}
#line 1957 "./syntax.tab.c"
    break;

  case 72:
#line 226 "./syntax.y"
                {struct TreeNode* nodeLP = CreateLeaf("LP", TypeToken, (yylsp[-2]).first_line, Typenon);
                struct TreeNode* nodeRP = CreateLeaf("RP", TypeToken, (yylsp[0]).first_line, Typenon);
                (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,3,nodeLP,(yyvsp[-1].Node),nodeRP);}
#line 1965 "./syntax.tab.c"
    break;

  case 74:
#line 230 "./syntax.y"
                               {struct TreeNode* nodeMINUS = CreateLeaf("MINUS", TypeToken, (yylsp[-1]).first_line, Typenon);
                                (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,2,nodeMINUS,(yyvsp[0].Node));}
#line 1972 "./syntax.tab.c"
    break;

  case 76:
#line 233 "./syntax.y"
              {struct TreeNode* nodeNOT = CreateLeaf("NOT", TypeToken, (yylsp[-1]).first_line, Typenon);
                (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,2,nodeNOT,(yyvsp[0].Node));}
#line 1979 "./syntax.tab.c"
    break;

  case 78:
#line 236 "./syntax.y"
                    {struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, (yylsp[-3]).first_line, Typeid ,(yyvsp[-3].type_string));
                struct TreeNode* nodeLP = CreateLeaf("LP", TypeToken, (yylsp[-2]).first_line, Typenon);
                struct TreeNode* nodeRP = CreateLeaf("RP", TypeToken, (yylsp[0]).first_line, Typenon);
                (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,4,nodeID,nodeLP,(yyvsp[-1].Node),nodeRP);}
#line 1988 "./syntax.tab.c"
    break;

  case 80:
#line 241 "./syntax.y"
               {struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, (yylsp[-2]).first_line, Typeid ,(yyvsp[-2].type_string));
                struct TreeNode* nodeLP = CreateLeaf("LP", TypeToken, (yylsp[-1]).first_line, Typenon);
                struct TreeNode* nodeRP = CreateLeaf("RP", TypeToken, (yylsp[0]).first_line, Typenon);
                (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,3,nodeID,nodeLP,nodeRP);}
#line 1997 "./syntax.tab.c"
    break;

  case 81:
#line 245 "./syntax.y"
                    {struct TreeNode* nodeLB = CreateLeaf("LB", TypeToken, (yylsp[-2]).first_line, Typenon);
                    struct TreeNode* nodeRB = CreateLeaf("RB", TypeToken, (yylsp[0]).first_line, Typenon);
                    (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,4,(yyvsp[-3].Node),nodeLB,(yyvsp[-1].Node),nodeRB);}
#line 2005 "./syntax.tab.c"
    break;

  case 83:
#line 250 "./syntax.y"
                 {struct TreeNode* nodeDOT = CreateLeaf("DOT", TypeToken, (yylsp[-1]).first_line, Typenon);
                struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, (yylsp[0]).first_line, Typeid ,(yyvsp[0].type_string));
                (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,3,(yyvsp[-2].Node),nodeDOT,nodeID);}
#line 2013 "./syntax.tab.c"
    break;

  case 84:
#line 253 "./syntax.y"
         {struct TreeNode* nodeID = CreateLeaf("ID", TypeToken, (yylsp[0]).first_line, Typeid ,(yyvsp[0].type_string));
            //printf("id1 = %s\n",$1);
            (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,1,nodeID);}
#line 2021 "./syntax.tab.c"
    break;

  case 85:
#line 256 "./syntax.y"
          {struct TreeNode* nodeINT = CreateLeaf("INT", TypeToken, (yylsp[0]).first_line, Typeint ,(yyvsp[0].type_int));
            (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,1,nodeINT);}
#line 2028 "./syntax.tab.c"
    break;

  case 86:
#line 258 "./syntax.y"
            {struct TreeNode* nodeFLOAT = CreateLeaf("FLOAT", TypeToken, (yylsp[0]).first_line, Typefloat ,(yyvsp[0].type_float));
            (yyval.Node) = BuildTree("Exp",TypeNontoken,(yyloc).first_line,1,nodeFLOAT);}
#line 2035 "./syntax.tab.c"
    break;

  case 87:
#line 261 "./syntax.y"
                      {struct TreeNode* nodeCOMMA = CreateLeaf("COMMA", TypeToken, (yylsp[-1]).first_line, Typenon);
                        (yyval.Node) = BuildTree("Args",TypeNontoken,(yyloc).first_line,3,(yyvsp[-2].Node),nodeCOMMA,(yyvsp[0].Node));}
#line 2042 "./syntax.tab.c"
    break;

  case 88:
#line 263 "./syntax.y"
          {(yyval.Node) = BuildTree("Args",TypeNontoken,(yyloc).first_line,1,(yyvsp[0].Node));}
#line 2048 "./syntax.tab.c"
    break;


#line 2052 "./syntax.tab.c"

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
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
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
#line 266 "./syntax.y"

#include "lex.yy.c"
yyerror(char* msg){
    flagoferror++;
    //fprintf(stderr, "Error type B at Line %d: %s\n", yylineno,msg);
    printf("Error type B at Line %d: %s\n",yylineno,msg);
}


struct TreeNode* BuildTree(char* nodeName, enum NodeType nodeType, int lineNum,int childNum,...){
    struct TreeNode* newnode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if(flagoferror == 0){
    newnode->Name = nodeName;
    newnode->nodetype = nodeType;
    newnode->Numofline = lineNum;
    newnode->Numofchild = childNum;
    newnode->Child = NULL;
    newnode->Sibling = NULL;

    va_list valist;
    va_start(valist, childNum);
    struct TreeNode* firstChild = NULL;
    struct TreeNode* lastSibiling = NULL;
    int j = 0;
    for (int i = 0; i < childNum; i++) {
        struct TreeNode* curnode = va_arg(valist, struct TreeNode*);
        if(curnode!= NULL)
        {
            firstChild = curnode;
            lastSibiling = firstChild;
            j = i + 1;
            break;
        }
    }
    
    for(; j < childNum;j++){
        //printf("j=%d, %d\n",j,childNum);
        lastSibiling->Sibling = va_arg(valist, struct TreeNode*);
        if(lastSibiling->Sibling != NULL) 
            lastSibiling = lastSibiling->Sibling;
    }
    va_end(valist);
    newnode->Child = firstChild;
    }
    return newnode;
}

struct TreeNode* CreateLeaf(char* nodeName, enum NodeType nodeType, int lineNum, enum TokenType tokentype, ...)
{
    struct TreeNode* newnode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newnode->Name = nodeName;
    newnode->nodetype = nodeType;
    newnode->Numofline = lineNum;
    newnode->Child = NULL;
    newnode->Sibling = NULL;
    newnode->tokentype = tokentype;
    switch(newnode->tokentype){
        case Typeint:
        {
            va_list valist;
            va_start(valist,tokentype);
            newnode->data.Intval = va_arg(valist, int);
            va_end(valist);
            break;
        }
        case Typefloat:
        {
            va_list valist;
            va_start(valist,tokentype);
            newnode->data.Floatval = va_arg(valist, double);
            va_end(valist);
            break;
        }
        case Typeid:
        {
            va_list valist;
            va_start(valist,tokentype);
            newnode->data.Charval = va_arg(valist, char*);
            //printf("%s\n",newnode->data.Charval);
            va_end(valist);
            break;
        }
        case Typenon:
            break;
        default: break;
    }

    return newnode;
}

void PrintTree(struct TreeNode* Node,int Space)
{
    if (Node == NULL)
        return;
    for(int i = 0;i < Space;i++){
        printf(" ");
    }
    printf("%s",Node->Name);
    switch(Node->nodetype){
        case TypeToken:{
            switch(Node->tokentype){
                case Typeint:
                    printf(": %d\n",Node->data.Intval);
                    break;
                case Typefloat:
                    printf(": %f\n",Node->data.Floatval);
                    break;
                case Typeid:
                    printf(": %s\n",Node->data.Charval);
                    //printf("\n");
                    break;
                case Typenon:
                    printf("\n");
                    break;
                default: break;
            }
            break;
        }
        case TypeNontoken:{
            printf(" (%d)\n",Node->Numofline);
            break;
        }
        default: break;
    }
    int newSpace = Space + 2;
    PrintTree(Node->Child,newSpace);
    PrintTree(Node->Sibling,Space);
}
