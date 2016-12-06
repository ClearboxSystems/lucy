%skeleton "lalr1.cc"
%require "3.0.2"

%verbose

%defines 
%define parser_class_name {BisonParser}
%define api.namespace {lucy}

%define parse.trace
%define parse.error verbose

%code requires {
	namespace lucy {
		class Lexer;
		class Parser;
	}
}

%param { Lexer &lexer }
%parse-param { lucy::Parser &parser}

%code {
	static int yylex(lucy::BisonParser::semantic_type *yylval, lucy::Lexer &lexer);
}

%union {
	int ival;
	char *symbol;
}

%define api.token.prefix {}

%token <ival> INTEGER
%token <symbol> IDENTIFIER
%token ASSIGN
%token ADD
%token EQUALS
%token COMMA
%token SEMICOLON
%token OPEN_PAREN CLOSE_PAREN
%token LIST_START LIST_END
%token END 0

%type <ival> top expr

%left ADD

%%
%start top;

top :
  | top expr SEMICOLON { printf(" = %d\n", $2); $$ = $2; }
 ;	

expr :
 	expr ADD expr 	{ $$ = $1 + $3; }
  |	INTEGER			{ $$ = $1; }
  ;

%%
#include "Lexer.hh"

static int yylex(lucy::BisonParser::semantic_type *yylval, lucy::Lexer &lexer) {
	return lexer.yylex(yylval);
}

void lucy::BisonParser::error( const std::string &errorMessage) {
	std::cerr << "Error: " << errorMessage << "\n";
}
