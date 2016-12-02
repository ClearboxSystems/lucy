/* simplest version of calculator */
%{
#include <stdio.h>
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
 
void yyerror(const char *s);
%}

%union {
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
%token ABS EOL

%type <num> exp factor term
%%

calclist: /* nothing */ 
 | calclist exp EOL { printf("= %d\n", $2); }
 ;

list: exp
 | list LS exp { }
 ;

exp: factor 
 | exp ADD factor { $$ = $1 + $3; }
 | exp SUB factor { $$ = $1 - $3; }
 ;

factor: term 
 | factor MUL term { $$ = $1 * $3; }
 | factor DIV term { $$ = $1 / $3; }
 ;

term: NUMBER 
 | ABS term { $$ = $2 >= 0? $2 : - $2; }
 | OP exp CP { $$ = $2; }
 | OL list CL { printf("We have a list!\n"); } 
;

%%
//int main(int argc, char **argv)
//{
// yyparse();
//}

void yyerror(const char *s)
{
 fprintf(stderr, "error: %s\n", s);
}
