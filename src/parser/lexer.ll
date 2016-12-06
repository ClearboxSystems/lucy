%{
#include "BisonParser.hh"
#include "Lexer.hh"

typedef lucy::Parser::token token;

#define yyterminate() return ( token::END )
%}

%option debug
%option c++
%option yyclass="Lexer"
%option noyywrap

%%

[ \t]+

"+" return token::ADD;
";" return token::SEMICOLON;

[0-9]+ {
	yylval->ival = atoi(yytext);
	return token::INTEGER;
}

.	printf("bad input character '%s' at line %d\n", yytext, yylineno);
