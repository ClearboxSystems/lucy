%skeleton "lalr1.cc"
%require "3.0.2"

%verbose

%defines 
%define parser_class_name {Parser}
%define api.namespace {lucy}

%code requires {
	class Lexer;
}

%param { Lexer &lexer }

%code {
	static int yylex(lucy::Parser::semantic_type *yylval, Lexer &lexer);
}

%union {
	int ival;
}

%define api.token.prefix {}

%token <ival> INTEGER
%token ADD
%token SEMICOLON
%token END

%type <ival> top expr

%left ADD

%%
%start top;

top :
 	expr SEMICOLON 	{ printf("= %d", $1); $$ = $1; }
 ;	

 expr :
 	expr ADD expr 	{ $$ = $1 + $3; }
  |	INTEGER			{ $$ = $1; }
  ;

%%
#include "Lexer.hh"

static int yylex(lucy::Parser::semantic_type *yylval, Lexer &lexer) {
	return lexer.yylex(yylval);
}

void lucy::Parser::error( const std::string &errorMessage) {
	std::cerr << "Error: " << errorMessage << "\n";
}
