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
	long ival;
	double fval;
	std::string *string;
	ASTNode *node;
	SymbolNode *symbol;
	AssignmentNode *assign;
	std::vector<ASTNode *> *list;
	std::vector<std::string> *args;
	FunctionPrototype *proto;
	FunctionDef *func;
	CallNode *call;
}

%define api.token.prefix {}

%token <ival> INTEGER
%token <fval> FLOAT
%token <string> IDENTIFIER
%token ASSIGN
%token ADD SUBTRACT
%token MULTIPLY DIVIDE
%token EQUALS
%token COMMA
%token SEMICOLON
%token OPEN_PAREN CLOSE_PAREN
%token LIST_START LIST_END
%token FUN EXTERN
%token END 0

%nonassoc ASSIGN
%nonassoc EQUALS
%left ADD SUBTRACT
%left MULTIPLY DIVIDE

%type <node> expr statement
%type <symbol> symbol
%type <assign> assignment
%type <list> list
%type <args> args
%type <proto> prototype
%type <func> definition
%type <call> call

%%
%start top;

top :
  | top statement {  }
 ;	

statement :
    expr SEMICOLON { parser.emitStatement($1); }
  | assignment SEMICOLON { parser.emitStatement($1); }
  | definition SEMICOLON { parser.emitDefinition($1); }
  | EXTERN prototype SEMICOLON {parser.emitExtern($2); }
  ;

definition : FUN prototype ASSIGN expr {
	$$ = new FunctionDef($2, $4);	
};

call : IDENTIFIER OPEN_PAREN list CLOSE_PAREN {
	$$ = new CallNode(*$1, *$3);
};

prototype : IDENTIFIER OPEN_PAREN args CLOSE_PAREN {
	$$ = new FunctionPrototype(*$1, *$3);
};

args : { $$ = new std::vector<std::string>(); }
 | IDENTIFIER { 	$$ = new std::vector<std::string>();
 					$$->push_back(*$1); }
 | args COMMA IDENTIFIER { $$ = $1; $$->push_back(*$3); }
 ;

list :	{ $$ = new std::vector<ASTNode *>(); }
 | expr { 
 		$$ = new std::vector<ASTNode *>(); 
 		$$->push_back($1); 
 	}
 | list COMMA expr { $$ = $1; $$->push_back($3); }
 ;

assignment : symbol ASSIGN expr { 
						$$ = new AssignmentNode($1, $3); };

symbol : IDENTIFIER				{ $$ = new SymbolNode(*$1); };

expr :
    expr ADD expr 				{ $$ = new BinaryNode('+', $1, $3); }
  | expr SUBTRACT expr			{ $$ = new BinaryNode('-', $1, $3); }
  | expr MULTIPLY expr 			{ $$ = new BinaryNode('*', $1, $3); }
  | expr DIVIDE expr 			{ $$ = new BinaryNode('/', $1, $3); }
  | expr EQUALS expr 			{ $$ = new BinaryNode('=', $1, $3); }
  | symbol 						{ $$ = $1; }
  |	INTEGER						{ $$ = new IntegerNode($1); }
  |	FLOAT						{ $$ = new FloatNode($1); }
  | OPEN_PAREN expr CLOSE_PAREN { $$ = $2; }
  | LIST_START list LIST_END 	{ $$ = new ListNode($2); }
  | call 						{ $$ = $1; }
  ;

%%
#include "Lexer.hh"

static int yylex(lucy::BisonParser::semantic_type *yylval, lucy::Lexer &lexer) {
	return lexer.yylex(yylval);
}

void lucy::BisonParser::error( const std::string &errorMessage) {
	std::cerr << "Error: " << errorMessage << "\n";
}
