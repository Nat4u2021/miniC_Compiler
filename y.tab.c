/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "miniC.y"

#include <stdio.h>
#include "ast.h"
#include <stack>
#include <iostream>
#include <cstring>
void yyerror(const char *);
extern int yylex();
extern int yylex_destroy();
extern FILE *yyin;
extern int yylineno;
extern char* yytext;
astNode *root;

#line 86 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT = 258,                     /* INT  */
    EXTERN = 259,                  /* EXTERN  */
    IF = 260,                      /* IF  */
    WHILE = 261,                   /* WHILE  */
    ELSE = 262,                    /* ELSE  */
    RETURN = 263,                  /* RETURN  */
    VOID = 264,                    /* VOID  */
    NUM = 265,                     /* NUM  */
    STR = 266,                     /* STR  */
    READ = 267,                    /* READ  */
    PRINT = 268                    /* PRINT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INT 258
#define EXTERN 259
#define IF 260
#define WHILE 261
#define ELSE 262
#define RETURN 263
#define VOID 264
#define NUM 265
#define STR 266
#define READ 267
#define PRINT 268

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "miniC.y"

	int ival;
	char* sname;
	astNode *nptr;
	vector<astNode*> *svec_ptr;

#line 172 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_EXTERN = 4,                     /* EXTERN  */
  YYSYMBOL_IF = 5,                         /* IF  */
  YYSYMBOL_WHILE = 6,                      /* WHILE  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_VOID = 9,                       /* VOID  */
  YYSYMBOL_NUM = 10,                       /* NUM  */
  YYSYMBOL_STR = 11,                       /* STR  */
  YYSYMBOL_READ = 12,                      /* READ  */
  YYSYMBOL_PRINT = 13,                     /* PRINT  */
  YYSYMBOL_14_ = 14,                       /* ';'  */
  YYSYMBOL_15_ = 15,                       /* '('  */
  YYSYMBOL_16_ = 16,                       /* ')'  */
  YYSYMBOL_17_ = 17,                       /* '='  */
  YYSYMBOL_18_ = 18,                       /* '<'  */
  YYSYMBOL_19_ = 19,                       /* '>'  */
  YYSYMBOL_20_ = 20,                       /* '!'  */
  YYSYMBOL_21_ = 21,                       /* '+'  */
  YYSYMBOL_22_ = 22,                       /* '-'  */
  YYSYMBOL_23_ = 23,                       /* '*'  */
  YYSYMBOL_24_ = 24,                       /* '/'  */
  YYSYMBOL_25_ = 25,                       /* '{'  */
  YYSYMBOL_26_ = 26,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 27,                  /* $accept  */
  YYSYMBOL_declaration = 28,               /* declaration  */
  YYSYMBOL_definition1 = 29,               /* definition1  */
  YYSYMBOL_definition2 = 30,               /* definition2  */
  YYSYMBOL_return_statement = 31,          /* return_statement  */
  YYSYMBOL_term = 32,                      /* term  */
  YYSYMBOL_eq_cond = 33,                   /* eq_cond  */
  YYSYMBOL_lt_cond = 34,                   /* lt_cond  */
  YYSYMBOL_gt_cond = 35,                   /* gt_cond  */
  YYSYMBOL_gteq_cond = 36,                 /* gteq_cond  */
  YYSYMBOL_lteq_cond = 37,                 /* lteq_cond  */
  YYSYMBOL_neq_cond = 38,                  /* neq_cond  */
  YYSYMBOL_comparison = 39,                /* comparison  */
  YYSYMBOL_add = 40,                       /* add  */
  YYSYMBOL_subtract = 41,                  /* subtract  */
  YYSYMBOL_multiply = 42,                  /* multiply  */
  YYSYMBOL_divide = 43,                    /* divide  */
  YYSYMBOL_expression = 44,                /* expression  */
  YYSYMBOL_assign = 45,                    /* assign  */
  YYSYMBOL_func_call = 46,                 /* func_call  */
  YYSYMBOL_if_block = 47,                  /* if_block  */
  YYSYMBOL_while_block = 48,               /* while_block  */
  YYSYMBOL_else_block = 49,                /* else_block  */
  YYSYMBOL_stmt = 50,                      /* stmt  */
  YYSYMBOL_stmts = 51,                     /* stmts  */
  YYSYMBOL_comnd_block = 52,               /* comnd_block  */
  YYSYMBOL_func_def = 53,                  /* func_def  */
  YYSYMBOL_program = 54                    /* program  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   112

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  120

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   268


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    20,     2,     2,     2,     2,     2,     2,
      15,    16,    23,    21,     2,    22,     2,    24,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    14,
      18,    17,    19,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,     2,    26,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int8 yyrline[] =
{
       0,    31,    31,    33,    35,    37,    37,    39,    39,    41,
      43,    45,    47,    49,    51,    53,    53,    53,    53,    53,
      53,    55,    57,    59,    61,    63,    63,    63,    63,    65,
      66,    67,    68,    70,    71,    72,    74,    74,    76,    78,
      80,    80,    80,    80,    80,    80,    80,    82,    82,    84,
      86,    86,    88
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "EXTERN", "IF",
  "WHILE", "ELSE", "RETURN", "VOID", "NUM", "STR", "READ", "PRINT", "';'",
  "'('", "')'", "'='", "'<'", "'>'", "'!'", "'+'", "'-'", "'*'", "'/'",
  "'{'", "'}'", "$accept", "declaration", "definition1", "definition2",
  "return_statement", "term", "eq_cond", "lt_cond", "gt_cond", "gteq_cond",
  "lteq_cond", "neq_cond", "comparison", "add", "subtract", "multiply",
  "divide", "expression", "assign", "func_call", "if_block", "while_block",
  "else_block", "stmt", "stmts", "comnd_block", "func_def", "program", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-43)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       4,     5,    13,    39,    28,    51,    58,   -43,    52,    54,
      57,   -43,    68,    61,    62,    63,    64,     3,    59,    67,
      71,    53,   -43,   -43,    69,    10,   -43,    53,    72,    73,
      74,    26,    70,    75,    76,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,    -1,   -43,   -43,    78,    26,    26,   -43,   -43,
       6,   -43,   -43,   -43,   -43,   -43,    38,    77,    42,   -43,
     -43,   -43,    40,   -43,   -43,   -43,   -43,   -43,   -43,    79,
      80,   -43,    26,    26,    26,    26,    83,    84,    41,   -43,
     -43,    85,    86,    87,    88,    21,    23,    89,    10,    10,
      90,    93,    94,    95,   -43,   -43,   -43,    96,    97,    26,
      26,   -43,    26,   -43,    26,   105,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,    10,   -43,   -43
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     1,     0,     0,
       0,    52,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     4,     0,     0,    51,     0,     0,     0,
       0,     0,     0,     0,     0,    43,    41,    42,    40,    44,
      45,    48,     0,    46,    50,     0,     0,     0,     7,     8,
       0,    25,    26,    27,    28,     6,     0,     0,     0,    49,
      47,     2,     0,    15,    16,    19,    18,    17,    20,     0,
       0,     5,     0,     0,     0,     0,     7,     8,     0,    29,
      32,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    30,    31,    35,     0,     0,     0,
       0,    10,     0,    11,     0,    36,    38,    21,    22,    23,
      24,    34,    33,     9,    13,    12,    14,     0,    37,    39
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -43,   -43,   -43,   -43,   -43,   -30,   -43,   -43,   -43,   -43,
     -43,   -43,    37,   -43,   -43,   -43,   -43,    30,   -43,    44,
     -43,   -43,   -43,   -42,   -43,   -18,   -43,   -43
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    35,     2,     6,    36,    62,    63,    64,    65,    66,
      67,    68,    69,    51,    52,    53,    54,    55,    37,    38,
      39,    40,   118,    41,    42,    43,    11,     3
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      60,    50,    28,    26,    29,    30,    20,    31,     1,    44,
      32,    33,    34,    28,     4,    29,    30,     5,    31,    21,
      71,    32,    33,    34,    25,    59,    78,    72,    73,    74,
      75,    48,    49,    48,    49,    25,    48,    49,   100,     7,
     102,     8,    90,    91,    92,    93,   105,   106,    76,    77,
      33,    34,    82,    83,     9,   101,   103,    84,    85,    86,
      87,    10,    72,    73,    74,    75,    13,    12,    14,   113,
     114,    15,   115,    22,   116,   119,    16,    17,    25,    18,
      19,    23,    24,    45,    70,    27,    79,    56,    46,    47,
      57,    58,    61,    81,     0,    88,    89,    94,    95,    96,
      80,     0,    97,    98,   107,    99,   104,   108,   109,   110,
     111,   112,   117
};

static const yytype_int8 yycheck[] =
{
      42,    31,     3,    21,     5,     6,     3,     8,     4,    27,
      11,    12,    13,     3,     9,     5,     6,     4,     8,    16,
      14,    11,    12,    13,    25,    26,    56,    21,    22,    23,
      24,    10,    11,    10,    11,    25,    10,    11,    17,     0,
      17,    13,    72,    73,    74,    75,    88,    89,    10,    11,
      12,    13,    10,    11,     3,    85,    86,    17,    18,    19,
      20,     3,    21,    22,    23,    24,    12,    15,    11,    99,
     100,     3,   102,    14,   104,   117,    15,    15,    25,    16,
      16,    14,    11,    11,    47,    16,    56,    17,    15,    15,
      15,    15,    14,    16,    -1,    16,    16,    14,    14,    14,
      56,    -1,    16,    16,    14,    17,    17,    14,    14,    14,
      14,    14,     7
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,    29,    54,     9,     4,    30,     0,    13,     3,
       3,    53,    15,    12,    11,     3,    15,    15,    16,    16,
       3,    16,    14,    14,    11,    25,    52,    16,     3,     5,
       6,     8,    11,    12,    13,    28,    31,    45,    46,    47,
      48,    50,    51,    52,    52,    11,    15,    15,    10,    11,
      32,    40,    41,    42,    43,    44,    17,    15,    15,    26,
      50,    14,    32,    33,    34,    35,    36,    37,    38,    39,
      39,    14,    21,    22,    23,    24,    10,    11,    32,    44,
      46,    16,    10,    11,    17,    18,    19,    20,    16,    16,
      32,    32,    32,    32,    14,    14,    14,    16,    16,    17,
      17,    32,    17,    32,    17,    50,    50,    14,    14,    14,
      14,    14,    14,    32,    32,    32,    32,     7,    49,    50
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    27,    28,    29,    30,    31,    31,    32,    32,    33,
      34,    35,    36,    37,    38,    39,    39,    39,    39,    39,
      39,    40,    41,    42,    43,    44,    44,    44,    44,    45,
      45,    45,    45,    46,    46,    46,    47,    47,    48,    49,
      50,    50,    50,    50,    50,    50,    50,    51,    51,    52,
      53,    53,    54
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     7,     6,     3,     2,     1,     1,     4,
       3,     3,     4,     4,     4,     1,     1,     1,     1,     1,
       1,     4,     4,     4,     4,     1,     1,     1,     1,     3,
       4,     4,     3,     5,     5,     4,     5,     6,     5,     2,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     3,
       7,     5,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* declaration: INT STR ';'  */
#line 31 "miniC.y"
                          {(yyval.nptr) = createDecl((yyvsp[-1].sname));}
#line 1272 "y.tab.c"
    break;

  case 3: /* definition1: EXTERN VOID PRINT '(' INT ')' ';'  */
#line 33 "miniC.y"
                                                {(yyval.nptr) = createExtern((yyvsp[-4].sname)); freeExtern((yyval.nptr));}
#line 1278 "y.tab.c"
    break;

  case 4: /* definition2: EXTERN INT READ '(' ')' ';'  */
#line 35 "miniC.y"
                                          {(yyval.nptr) = createExtern((yyvsp[-3].sname)); freeExtern((yyval.nptr));}
#line 1284 "y.tab.c"
    break;

  case 5: /* return_statement: RETURN term ';'  */
#line 37 "miniC.y"
                                   {(yyval.nptr) = createRet((yyvsp[-1].nptr));}
#line 1290 "y.tab.c"
    break;

  case 6: /* return_statement: RETURN expression  */
#line 37 "miniC.y"
                                                                             {(yyval.nptr) = createRet((yyvsp[0].nptr));}
#line 1296 "y.tab.c"
    break;

  case 7: /* term: NUM  */
#line 39 "miniC.y"
          {(yyval.nptr) = createCnst((yyvsp[0].ival));}
#line 1302 "y.tab.c"
    break;

  case 8: /* term: STR  */
#line 39 "miniC.y"
                                        {(yyval.nptr) = createVar((yyvsp[0].sname));}
#line 1308 "y.tab.c"
    break;

  case 9: /* eq_cond: term '=' '=' term  */
#line 41 "miniC.y"
                           {(yyval.nptr) = createRExpr((yyvsp[-3].nptr), (yyvsp[0].nptr), eq);}
#line 1314 "y.tab.c"
    break;

  case 10: /* lt_cond: term '<' term  */
#line 43 "miniC.y"
                         {(yyval.nptr) = createRExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), lt);}
#line 1320 "y.tab.c"
    break;

  case 11: /* gt_cond: term '>' term  */
#line 45 "miniC.y"
                         {(yyval.nptr) = createRExpr((yyvsp[-2].nptr), (yyvsp[0].nptr), gt);}
#line 1326 "y.tab.c"
    break;

  case 12: /* gteq_cond: term '>' '=' term  */
#line 47 "miniC.y"
                             {(yyval.nptr) = createRExpr((yyvsp[-3].nptr), (yyvsp[0].nptr), ge);}
#line 1332 "y.tab.c"
    break;

  case 13: /* lteq_cond: term '<' '=' term  */
#line 49 "miniC.y"
                             {(yyval.nptr) = createRExpr((yyvsp[-3].nptr), (yyvsp[0].nptr), le);}
#line 1338 "y.tab.c"
    break;

  case 14: /* neq_cond: term '!' '=' term  */
#line 51 "miniC.y"
                            {(yyval.nptr) = createRExpr((yyvsp[-3].nptr), (yyvsp[0].nptr), neq);}
#line 1344 "y.tab.c"
    break;

  case 15: /* comparison: eq_cond  */
#line 53 "miniC.y"
                     {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1350 "y.tab.c"
    break;

  case 16: /* comparison: lt_cond  */
#line 53 "miniC.y"
                                          {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1356 "y.tab.c"
    break;

  case 17: /* comparison: lteq_cond  */
#line 53 "miniC.y"
                                                                 {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1362 "y.tab.c"
    break;

  case 18: /* comparison: gteq_cond  */
#line 53 "miniC.y"
                                                                                        {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1368 "y.tab.c"
    break;

  case 19: /* comparison: gt_cond  */
#line 53 "miniC.y"
                                                                                                            {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1374 "y.tab.c"
    break;

  case 20: /* comparison: neq_cond  */
#line 53 "miniC.y"
                                                                                                                                  {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1380 "y.tab.c"
    break;

  case 21: /* add: term '+' term ';'  */
#line 55 "miniC.y"
                        {(yyval.nptr) = createBExpr((yyvsp[-3].nptr), (yyvsp[-1].nptr), add);}
#line 1386 "y.tab.c"
    break;

  case 22: /* subtract: term '-' term ';'  */
#line 57 "miniC.y"
                              {(yyval.nptr) = createBExpr((yyvsp[-3].nptr), (yyvsp[-1].nptr), sub);}
#line 1392 "y.tab.c"
    break;

  case 23: /* multiply: term '*' term ';'  */
#line 59 "miniC.y"
                              {(yyval.nptr) = createBExpr((yyvsp[-3].nptr), (yyvsp[-1].nptr), mul);}
#line 1398 "y.tab.c"
    break;

  case 24: /* divide: term '/' term ';'  */
#line 61 "miniC.y"
                              {(yyval.nptr) = createBExpr((yyvsp[-3].nptr), (yyvsp[-1].nptr), divide);}
#line 1404 "y.tab.c"
    break;

  case 25: /* expression: add  */
#line 63 "miniC.y"
                 {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1410 "y.tab.c"
    break;

  case 26: /* expression: subtract  */
#line 63 "miniC.y"
                                      {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1416 "y.tab.c"
    break;

  case 27: /* expression: multiply  */
#line 63 "miniC.y"
                                                            {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1422 "y.tab.c"
    break;

  case 28: /* expression: divide  */
#line 63 "miniC.y"
                                                                                 {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1428 "y.tab.c"
    break;

  case 29: /* assign: STR '=' expression  */
#line 65 "miniC.y"
                            {astNode* tnptr = createVar((yyvsp[-2].sname)); (yyval.nptr) = createAsgn(tnptr, (yyvsp[0].nptr));}
#line 1434 "y.tab.c"
    break;

  case 30: /* assign: STR '=' NUM ';'  */
#line 66 "miniC.y"
                                   {astNode* tnptr = createVar((yyvsp[-3].sname)); astNode* tnptr2 = createCnst((yyvsp[-1].ival)); (yyval.nptr) = createAsgn(tnptr, tnptr2);}
#line 1440 "y.tab.c"
    break;

  case 31: /* assign: STR '=' STR ';'  */
#line 67 "miniC.y"
                                   {astNode* tnptr = createVar((yyvsp[-3].sname)); astNode* tnptr2 = createVar((yyvsp[-1].sname)); (yyval.nptr) = createAsgn(tnptr, tnptr2);}
#line 1446 "y.tab.c"
    break;

  case 32: /* assign: STR '=' func_call  */
#line 68 "miniC.y"
                                    {astNode* tnptr = createVar((yyvsp[-2].sname)); (yyval.nptr) = createAsgn(tnptr, (yyvsp[0].nptr));}
#line 1452 "y.tab.c"
    break;

  case 33: /* func_call: PRINT '(' STR ')' ';'  */
#line 70 "miniC.y"
                                   {astNode* tnptr = createVar((yyvsp[-2].sname)); (yyval.nptr) = createCall((yyvsp[-4].sname), tnptr);}
#line 1458 "y.tab.c"
    break;

  case 34: /* func_call: PRINT '(' NUM ')' ';'  */
#line 71 "miniC.y"
                                                {astNode* tnptr = createCnst((yyvsp[-2].ival)); (yyval.nptr) = createCall((yyvsp[-4].sname), tnptr);}
#line 1464 "y.tab.c"
    break;

  case 35: /* func_call: READ '(' ')' ';'  */
#line 72 "miniC.y"
                                          {(yyval.nptr) = createCall((yyvsp[-3].sname));}
#line 1470 "y.tab.c"
    break;

  case 36: /* if_block: IF '(' comparison ')' stmt  */
#line 74 "miniC.y"
                                      {(yyval.nptr) = createIf((yyvsp[-2].nptr), (yyvsp[0].nptr));}
#line 1476 "y.tab.c"
    break;

  case 37: /* if_block: IF '(' comparison ')' stmt else_block  */
#line 74 "miniC.y"
                                                                                                       {(yyval.nptr) = createIf((yyvsp[-3].nptr), (yyvsp[-1].nptr), (yyvsp[0].nptr));}
#line 1482 "y.tab.c"
    break;

  case 38: /* while_block: WHILE '(' comparison ')' stmt  */
#line 76 "miniC.y"
                                            {(yyval.nptr) = createWhile((yyvsp[-2].nptr), (yyvsp[0].nptr));}
#line 1488 "y.tab.c"
    break;

  case 39: /* else_block: ELSE stmt  */
#line 78 "miniC.y"
                       {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1494 "y.tab.c"
    break;

  case 40: /* stmt: func_call  */
#line 80 "miniC.y"
                 {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1500 "y.tab.c"
    break;

  case 41: /* stmt: return_statement  */
#line 80 "miniC.y"
                                               {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1506 "y.tab.c"
    break;

  case 42: /* stmt: assign  */
#line 80 "miniC.y"
                                                                   {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1512 "y.tab.c"
    break;

  case 43: /* stmt: declaration  */
#line 80 "miniC.y"
                                                                                             {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1518 "y.tab.c"
    break;

  case 44: /* stmt: if_block  */
#line 80 "miniC.y"
                                                                                                                   {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1524 "y.tab.c"
    break;

  case 45: /* stmt: while_block  */
#line 80 "miniC.y"
                                                                                                                                             {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1530 "y.tab.c"
    break;

  case 46: /* stmt: comnd_block  */
#line 80 "miniC.y"
                                                                                                                                                                      {(yyval.nptr) = (yyvsp[0].nptr);}
#line 1536 "y.tab.c"
    break;

  case 47: /* stmts: stmts stmt  */
#line 82 "miniC.y"
                   {(yyval.svec_ptr) = (yyvsp[-1].svec_ptr); (yyval.svec_ptr)->push_back((yyvsp[0].nptr));}
#line 1542 "y.tab.c"
    break;

  case 48: /* stmts: stmt  */
#line 82 "miniC.y"
                                                        {(yyval.svec_ptr) = new vector<astNode*>(); (yyval.svec_ptr)->push_back((yyvsp[0].nptr));}
#line 1548 "y.tab.c"
    break;

  case 49: /* comnd_block: '{' stmts '}'  */
#line 84 "miniC.y"
                            {(yyval.nptr) = createBlock((yyvsp[-1].svec_ptr));}
#line 1554 "y.tab.c"
    break;

  case 50: /* func_def: INT STR '(' INT STR ')' comnd_block  */
#line 86 "miniC.y"
                                                {astNode* tnptr = createVar((yyvsp[-2].sname)); (yyval.nptr) = createFunc((yyvsp[-5].sname), tnptr , (yyvsp[0].nptr));}
#line 1560 "y.tab.c"
    break;

  case 51: /* func_def: INT STR '(' ')' comnd_block  */
#line 86 "miniC.y"
                                                                                                                                                 {(yyval.nptr) = createFunc((yyvsp[-3].sname), NULL, (yyvsp[0].nptr));}
#line 1566 "y.tab.c"
    break;

  case 52: /* program: definition1 definition2 func_def  */
#line 88 "miniC.y"
                                           {(yyval.nptr) = createProg((yyvsp[-2].nptr), (yyvsp[-1].nptr), (yyvsp[0].nptr)); root = (yyval.nptr);}
#line 1572 "y.tab.c"
    break;


#line 1576 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 89 "miniC.y"


bool check(vector<vector<char*>*> stackOfVectors, char* searchString) {
    for (vector<char*>* topVector: stackOfVectors) { // loop until stack is empty
        for (char* s : *topVector) { // loop through the elements of the top vector
            if (strcmp(s, searchString) == 0) { // if the search string is found in the top vector, return true
                return true;
            }
        }
    }
    return false; // if the search string was not found in any vector, return false
}

void helper(vector<astNode*> nodes, vector<vector<char*>*> temp){
	while (!nodes.empty()){
		vector<char*> *currvector = new vector<char*>();
		astNode* currnode = nodes.front();
		nodes.erase(nodes.begin());
	
		if (currnode->type == ast_stmt){
			if (currnode->stmt.type == ast_block){
				temp.push_back(currvector);
				helper(*currnode->stmt.block.stmt_list, temp);
				temp.pop_back();
			}
			else if (currnode->stmt.type == ast_decl){
				currvector = temp.back();
				currvector->push_back(currnode->stmt.decl.name);
			}
			else if (currnode->stmt.type == ast_call){
				vector<astNode*> newnodes;
				newnodes.push_back(currnode->stmt.call.param);
				helper(newnodes, temp);				
			}
			else if (currnode->stmt.type == ast_ret){
				printf("in return\n");
				vector<astNode*> newnodes;
				newnodes.push_back(currnode->stmt.ret.expr);
				helper(newnodes, temp);				
			}
			else if (currnode->stmt.type == ast_while){
				vector<astNode*> newnodes;
				newnodes.push_back(currnode->stmt.whilen.cond);
				newnodes.push_back(currnode->stmt.whilen.body);
				helper(newnodes, temp);				
			}
			else if (currnode->stmt.type == ast_if){
				vector<astNode*> newnodes;
				newnodes.push_back(currnode->stmt.ifn.cond);
				newnodes.push_back(currnode->stmt.ifn.if_body);
				if (currnode->stmt.ifn.else_body != NULL) newnodes.push_back(currnode->stmt.ifn.else_body);
				helper(newnodes, temp);				
			}
			else if (currnode->stmt.type == ast_asgn){
				vector<astNode*> newnodes;
				newnodes.push_back(currnode->stmt.asgn.lhs);
				newnodes.push_back(currnode->stmt.asgn.rhs);
				helper(newnodes, temp);				
			}						
		}
		else if (currnode->type == ast_var){
			bool declared = check(temp, currnode->var.name);
			if (!declared){
				printf("ERROR: variable %s has not been declared\n", currnode->var.name);
			}
		}
		else if (currnode->type == ast_rexpr){
			vector<astNode*> newnodes;
			newnodes.push_back(currnode->rexpr.lhs);
			newnodes.push_back(currnode->rexpr.rhs);
			helper(newnodes, temp);
		}
		else if (currnode->type == ast_bexpr){
			vector<astNode*> newnodes;
			newnodes.push_back(currnode->bexpr.lhs);
			newnodes.push_back(currnode->bexpr.rhs);
			helper(newnodes, temp);
		}
		else if (currnode->type == ast_uexpr){
			vector<astNode*> newnodes;
			newnodes.push_back(currnode->uexpr.expr);
			helper(newnodes, temp);
		}		
	}
	return;
}

void semantic_analysis(astNode *root){

	vector<vector<char*>*> symbol_table_stack;
	vector<char*> *currvector = new vector<char*> ();
	symbol_table_stack.push_back(currvector);

	if (root->func.param != NULL){
		currvector->push_back(root->func.param->var.name);
	}

	root = root->func.body;
	vector<astNode*> nodes = *root->stmt.block.stmt_list;

	helper(nodes, symbol_table_stack);

	symbol_table_stack.pop_back();
}


int main(int argc, char** argv){
	if (argc == 2){
		yyin = fopen(argv[1], "r");
	}

	yyparse();

	semantic_analysis(root->prog.func);

	if (yyin != stdin)
		fclose(yyin);

	yylex_destroy();
	
	return 0;
}

void yyerror(const char *){
	fprintf(stdout, "Syntax error %d\n", yylineno);
}
