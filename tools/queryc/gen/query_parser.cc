// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "query_parser.h"


// Unqualified %code blocks.
#line 43 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"

imlab::queryc::QueryParser::symbol_type yylex(imlab::queryc::QueryParseContext& qc);

#line 49 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 12 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"
namespace  imlab { namespace queryc  {
#line 141 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  QueryParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
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
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  QueryParser::QueryParser (imlab::queryc::QueryParseContext &qc_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      qc (qc_yyarg)
  {}

  QueryParser::~QueryParser ()
  {}

  QueryParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  QueryParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  QueryParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  QueryParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  QueryParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  QueryParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  QueryParser::symbol_number_type
  QueryParser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  QueryParser::stack_symbol_type::stack_symbol_type ()
  {}

  QueryParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 23: // pred_clause
        value.YY_MOVE_OR_COPY< std::pair<std::string, PredType> > (YY_MOVE (that.value));
        break;

      case 3: // "integer_value"
      case 4: // "identifier"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case 22: // where_clause
        value.YY_MOVE_OR_COPY< std::tuple<std::string, std::string, PredType> > (YY_MOVE (that.value));
        break;

      case 17: // non_empty_identifier_list
      case 18: // identifier_list
        value.YY_MOVE_OR_COPY< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      case 19: // optional_where_list
      case 20: // non_empty_where_list
      case 21: // where_list
        value.YY_MOVE_OR_COPY< std::vector<std::tuple<std::string, std::string, PredType>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  QueryParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 23: // pred_clause
        value.move< std::pair<std::string, PredType> > (YY_MOVE (that.value));
        break;

      case 3: // "integer_value"
      case 4: // "identifier"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case 22: // where_clause
        value.move< std::tuple<std::string, std::string, PredType> > (YY_MOVE (that.value));
        break;

      case 17: // non_empty_identifier_list
      case 18: // identifier_list
        value.move< std::vector<std::string> > (YY_MOVE (that.value));
        break;

      case 19: // optional_where_list
      case 20: // non_empty_where_list
      case 21: // where_list
        value.move< std::vector<std::tuple<std::string, std::string, PredType>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  QueryParser::stack_symbol_type&
  QueryParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 23: // pred_clause
        value.copy< std::pair<std::string, PredType> > (that.value);
        break;

      case 3: // "integer_value"
      case 4: // "identifier"
        value.copy< std::string > (that.value);
        break;

      case 22: // where_clause
        value.copy< std::tuple<std::string, std::string, PredType> > (that.value);
        break;

      case 17: // non_empty_identifier_list
      case 18: // identifier_list
        value.copy< std::vector<std::string> > (that.value);
        break;

      case 19: // optional_where_list
      case 20: // non_empty_where_list
      case 21: // where_list
        value.copy< std::vector<std::tuple<std::string, std::string, PredType>> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  QueryParser::stack_symbol_type&
  QueryParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 23: // pred_clause
        value.move< std::pair<std::string, PredType> > (that.value);
        break;

      case 3: // "integer_value"
      case 4: // "identifier"
        value.move< std::string > (that.value);
        break;

      case 22: // where_clause
        value.move< std::tuple<std::string, std::string, PredType> > (that.value);
        break;

      case 17: // non_empty_identifier_list
      case 18: // identifier_list
        value.move< std::vector<std::string> > (that.value);
        break;

      case 19: // optional_where_list
      case 20: // non_empty_where_list
      case 21: // where_list
        value.move< std::vector<std::tuple<std::string, std::string, PredType>> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  QueryParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  QueryParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  QueryParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  QueryParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  QueryParser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  QueryParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  QueryParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  QueryParser::debug_level_type
  QueryParser::debug_level () const
  {
    return yydebug_;
  }

  void
  QueryParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  QueryParser::state_type
  QueryParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  QueryParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  QueryParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  QueryParser::operator() ()
  {
    return parse ();
  }

  int
  QueryParser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (qc));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 23: // pred_clause
        yylhs.value.emplace< std::pair<std::string, PredType> > ();
        break;

      case 3: // "integer_value"
      case 4: // "identifier"
        yylhs.value.emplace< std::string > ();
        break;

      case 22: // where_clause
        yylhs.value.emplace< std::tuple<std::string, std::string, PredType> > ();
        break;

      case 17: // non_empty_identifier_list
      case 18: // identifier_list
        yylhs.value.emplace< std::vector<std::string> > ();
        break;

      case 19: // optional_where_list
      case 20: // non_empty_where_list
      case 21: // where_list
        yylhs.value.emplace< std::vector<std::tuple<std::string, std::string, PredType>> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 73 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"
    {
        bison_query_parse_result.select_list = std::move(yystack_[4].value.as < std::vector<std::string> > ());
        bison_query_parse_result.from_list = std::move(yystack_[2].value.as < std::vector<std::string> > ());
        bison_query_parse_result.where_list = std::move(yystack_[1].value.as < std::vector<std::tuple<std::string, std::string, PredType>> > ());
    }
#line 692 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"
    break;

  case 3:
#line 82 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"
    {
        yylhs.value.as < std::vector<std::string> > () = {std::move(yystack_[0].value.as < std::string > ())};
    }
#line 700 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"
    break;

  case 4:
#line 86 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"
    {
        yystack_[1].value.as < std::vector<std::string> > ().push_back(std::move(yystack_[0].value.as < std::string > ()));
        yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[1].value.as < std::vector<std::string> > ());
    }
#line 709 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"
    break;

  case 5:
#line 94 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"
    {
        yystack_[2].value.as < std::vector<std::string> > ().push_back(std::move(yystack_[1].value.as < std::string > ()));
        yylhs.value.as < std::vector<std::string> > () = std::move(yystack_[2].value.as < std::vector<std::string> > ());
    }
#line 718 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"
    break;

  case 6:
#line 98 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"
                     { yylhs.value.as < std::vector<std::string> > () = {std::move(yystack_[1].value.as < std::string > ())}; }
#line 724 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"
    break;

  case 7:
#line 102 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"
                               { yylhs.value.as < std::vector<std::tuple<std::string, std::string, PredType>> > () = std::move(yystack_[0].value.as < std::vector<std::tuple<std::string, std::string, PredType>> > ()); }
#line 730 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"
    break;

  case 8:
#line 103 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"
           { yylhs.value.as < std::vector<std::tuple<std::string, std::string, PredType>> > () = {}; }
#line 736 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"
    break;

  case 9:
#line 107 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"
                 { yylhs.value.as < std::vector<std::tuple<std::string, std::string, PredType>> > () = {std::move(yystack_[0].value.as < std::tuple<std::string, std::string, PredType> > ())}; }
#line 742 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"
    break;

  case 10:
#line 109 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"
    {
        yystack_[1].value.as < std::vector<std::tuple<std::string, std::string, PredType>> > ().push_back(std::move(yystack_[0].value.as < std::tuple<std::string, std::string, PredType> > ()));
        yylhs.value.as < std::vector<std::tuple<std::string, std::string, PredType>> > () = std::move(yystack_[1].value.as < std::vector<std::tuple<std::string, std::string, PredType>> > ());
    }
#line 751 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"
    break;

  case 11:
#line 117 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"
    {
        yystack_[2].value.as < std::vector<std::tuple<std::string, std::string, PredType>> > ().push_back(std::move(yystack_[1].value.as < std::tuple<std::string, std::string, PredType> > ()));
        yylhs.value.as < std::vector<std::tuple<std::string, std::string, PredType>> > () = std::move(yystack_[2].value.as < std::vector<std::tuple<std::string, std::string, PredType>> > ());
    }
#line 760 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"
    break;

  case 12:
#line 121 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"
                     { yylhs.value.as < std::vector<std::tuple<std::string, std::string, PredType>> > () = {std::move(yystack_[1].value.as < std::tuple<std::string, std::string, PredType> > ())}; }
#line 766 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"
    break;

  case 13:
#line 126 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"
    {
        std::get<0>(yylhs.value.as < std::tuple<std::string, std::string, PredType> > ()) = std::move(yystack_[2].value.as < std::string > ());
        std::get<1>(yylhs.value.as < std::tuple<std::string, std::string, PredType> > ()) = yystack_[0].value.as < std::pair<std::string, PredType> > ().first;
        std::get<2>(yylhs.value.as < std::tuple<std::string, std::string, PredType> > ()) = yystack_[0].value.as < std::pair<std::string, PredType> > ().second;
    }
#line 776 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"
    break;

  case 14:
#line 134 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"
               { yylhs.value.as < std::pair<std::string, PredType> > () = {yystack_[0].value.as < std::string > (), PredType::ColumnRef}; }
#line 782 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"
    break;

  case 15:
#line 135 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"
                  { yylhs.value.as < std::pair<std::string, PredType> > () = {yystack_[0].value.as < std::string > (), PredType::IntConstant}; }
#line 788 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"
    break;

  case 16:
#line 136 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"
                           { yylhs.value.as < std::pair<std::string, PredType> > () = {yystack_[1].value.as < std::string > (), PredType::StringConstant}; }
#line 794 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"
    break;


#line 798 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
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


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  QueryParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  QueryParser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char QueryParser::yypact_ninf_ = -11;

  const signed char QueryParser::yytable_ninf_ = -1;

  const signed char
  QueryParser::yypact_[] =
  {
     -10,    -1,     4,    -5,    -6,     5,   -11,   -11,    -1,     0,
      -4,   -11,     8,    -2,     6,   -11,     8,     7,   -11,    -3,
       9,   -11,   -11,   -11,    10,   -11,   -11,    11,   -11
  };

  const signed char
  QueryParser::yydefact_[] =
  {
       0,     0,     0,     3,     0,     0,     1,     6,     0,     4,
       8,     5,     0,     0,     0,     7,     0,     9,     2,     0,
      10,    12,    15,    14,     0,    13,    11,     0,    16
  };

  const signed char
  QueryParser::yypgoto_[] =
  {
     -11,   -11,    12,   -11,   -11,   -11,   -11,     1,   -11
  };

  const signed char
  QueryParser::yydefgoto_[] =
  {
      -1,     2,     4,     5,    13,    15,    16,    17,    25
  };

  const signed char
  QueryParser::yytable_[] =
  {
      22,    23,     1,     3,     6,    24,     7,     8,    18,     9,
      12,    11,    14,    19,    27,     0,    21,    20,    26,    28,
      10
  };

  const signed char
  QueryParser::yycheck_[] =
  {
       3,     4,    12,     4,     0,     8,    11,    13,    10,     4,
      14,    11,     4,     7,     4,    -1,     9,    16,     9,     8,
       8
  };

  const signed char
  QueryParser::yystos_[] =
  {
       0,    12,    16,     4,    17,    18,     0,    11,    13,     4,
      17,    11,    14,    19,     4,    20,    21,    22,    10,     7,
      22,     9,     3,     4,     8,    23,     9,     4,     8
  };

  const signed char
  QueryParser::yyr1_[] =
  {
       0,    15,    16,    17,    17,    18,    18,    19,    19,    20,
      20,    21,    21,    22,    23,    23,    23
  };

  const signed char
  QueryParser::yyr2_[] =
  {
       0,     2,     6,     1,     2,     3,     2,     2,     0,     1,
       2,     3,     2,     3,     1,     1,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const QueryParser::yytname_[] =
  {
  "\"eof\"", "error", "$undefined", "\"integer_value\"", "\"identifier\"",
  "\"left_brackets\"", "\"right_brackets\"", "\"equals\"", "\"quote\"",
  "\"and\"", "\"semicolon\"", "\"comma\"", "\"select\"", "\"from\"",
  "\"where\"", "$accept", "sql_query", "non_empty_identifier_list",
  "identifier_list", "optional_where_list", "non_empty_where_list",
  "where_list", "where_clause", "pred_clause", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  QueryParser::yyrline_[] =
  {
       0,    72,    72,    81,    85,    93,    98,   102,   103,   107,
     108,   116,   121,   125,   134,   135,   136
  };

  // Print the state stack on the debug stream.
  void
  QueryParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  QueryParser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 12 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"
} } //  imlab::queryc 
#line 1194 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/gen/query_parser.cc"

#line 139 "/home/benjamin-fire/Documents/uni/dbimpl/dbimpl-tasks/tools/queryc/query_parser.y"

// ---------------------------------------------------------------------------------------------------
// Define error function
void imlab::queryc::QueryParser::error(const location_type& l, const std::string& m) {
    qc.Error(l.begin.line, l.begin.column, m);
}
// ---------------------------------------------------------------------------------------------------

