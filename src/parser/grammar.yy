%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.2"
%defines
%define parser_class_name {BisonParser}

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
# include <string>
class Parser;
}

// The parsing context.
%param { Parser& parser }

%locations
%initial-action
{
  // Initialize the initial location.
  @$.begin.filename = @$.end.filename = &parser.file;
};

%define parse.trace
%define parse.error verbose

%code
{
# include "parser.hpp"
}

%define api.token.prefix {TOK_}
%token
  END  0  "end of file"
  PLUS    "+"
  SEMICOLON ";"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%type  <int> exp

%printer { yyoutput << $$; } <*>;

%%
%start unit;

unit: 
  exp SEMICOLON { std::cout << "MATCH" << std::endl; parser.result = $1; };

%left "+" "-";
%left "*" "/";
exp:
  exp "+" exp   { $$ = $1 + $3; }
| "(" exp ")"   { std::swap ($$, $2); }
| "identifier"  { $$ = parser.variables[$1]; }
| "number"      { std::swap ($$, $1); };


%%

void yy::BisonParser::error (const location_type& l, const std::string& m) {
  parser.error (l, m);
}
