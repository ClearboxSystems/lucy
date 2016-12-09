%skeleton "lalr1.cc"
%require "3.0.2"

%verbose

%defines 
%define parser_class_name {BisonParser}
%define api.namespace {lucy}

%define parse.trace
%define parse.error verbose

%code requires {
	#include "../ast.hh"
	#include "Parser.hh"

	namespace lucy {
		class Lexer;
	}
}

%param { Lexer &lexer }
%parse-param { lucy::Parser &parser}

%code {
	static int yylex(lucy::BisonParser::semantic_type *yylval, lucy::Lexer &lexer);
}

%union {
	int ival;
	char *string;
	ASTNode *node;
	SymbolNode *symbol;
	AssignmentNode *assign;
	std::vector<ASTNode *> *list;
}

%define api.token.prefix {}

%token <ival> INTEGER
%token <string> IDENTIFIER
%token ASSIGN
%token ADD SUBTRACT
%token MULTIPLY DIVIDE
%token EQUALS
%token COMMA
%token SEMICOLON
%token OPEN_PAREN CLOSE_PAREN
%token LIST_START LIST_END
%token END 0

%nonassoc ASSIGN
%nonassoc EQUALS
%left ADD SUBTRACT
%left MULTIPLY DIVIDE

%type <node> expr statement
%type <symbol> symbol
%type <assign> assignment
%type <list> list

%%
%start top;

top :
  | top statement { parser.emitStatement($2); }
 ;	

statement :
    expr SEMICOLON { $$ = $1; }
  | assignment SEMICOLON { $$ = $1; }
  ;

list :	{ $$ = new std::vector<ASTNode *>(); }
 | expr { 
 		$$ = new std::vector<ASTNode *>(); 
 		$$->push_back($1); 
 	}
 | list COMMA expr { $$ = $1; $$->push_back($3); }
 ;

assignment : symbol ASSIGN expr { 
						$$ = new AssignmentNode($1, $3); }

symbol : IDENTIFIER				{ $$ = new SymbolNode($1); }

expr :
    expr ADD expr 				{ $$ = new BinaryNode('+', $1, $3); }
  | expr SUBTRACT expr			{ $$ = new BinaryNode('-', $1, $3); }
  | expr MULTIPLY expr 			{ $$ = new BinaryNode('*', $1, $3); }
  | expr DIVIDE expr 			{ $$ = new BinaryNode('/', $1, $3); }
  | expr EQUALS expr 			{ $$ = new BinaryNode('=', $1, $3); }
  | symbol 						{ $$ = $1; }
  |	INTEGER						{ $$ = new NumberNode($1); }
  | OPEN_PAREN expr CLOSE_PAREN { $$ = $2; }
  | LIST_START list LIST_END 	{ $$ = new ListNode($2); }
  ;

%%
#include "Lexer.hh"

static int yylex(lucy::BisonParser::semantic_type *yylval, lucy::Lexer &lexer) {
	return lexer.yylex(yylval);
}

void lucy::BisonParser::error( const std::string &errorMessage) {
	std::cerr << "Error: " << errorMessage << "\n";
}
