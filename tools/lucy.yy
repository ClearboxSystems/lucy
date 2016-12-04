/* simplest version of calculator */
%{
#include <stdio.h>
#include "ast.h"
extern "C" int yylex();
extern "C" FILE *yyin;
 
%}

%union {
	struct ast *a;
	struct list *l;
    int num;
    char *symbol;
}

/* declare tokens */
%token <num> NUMBER 
%token <symbol> IDENT
%token ASSIGN
%token ADD SUB MUL DIV EQUAL
%token OP CP OL CL LS
%token EOS

%type <a> exp assign
%type <l> list

%nonassoc ASSIGN
%left ADD SUB
%left MUL DIV
%nonassoc UMINUS

%%

calclist: /* nothing */ 
 | calclist exp EOS { printAst($2); printf(" = %d\n", evalAst($2)); freeAst($2); }
 | calclist assign EOS { printf("Assign expression\n"); }
 ;

assign: IDENT ASSIGN exp {  printf("Assign\n"); }

list: { $$ = newlist(); }
 | exp { $$ = newlist($1); }
 | exp LS list { $$ = growlist($1, $3); }
 ;

exp: exp ADD exp 	{ $$ = newast('+', $1, $3); }
 | exp SUB exp 		{ $$ = newast('-', $1, $3); }
 | exp MUL exp 		{ $$ = newast('*', $1, $3); }
 | exp DIV exp 		{ $$ = newast('/', $1, $3); }
 | OP exp CP 		{ $$ = $2; }
 | OL list CL 		{ $$ = newast('L', NULL, (struct ast *)$2); } 
 | SUB exp %prec UMINUS { $$ = newast('M', NULL, $2); }
 | NUMBER			{ $$ = newnum($1); }
 ;

%%
