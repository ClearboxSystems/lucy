%{
#include "BisonParser.hh"
#include "Lexer.hh"

typedef lucy::BisonParser::token token;

#define yyterminate() return ( token::END )
%}

%option c++
%option yyclass="Lexer"
%option noyywrap
%option debug

%x COMMENT

%%
"/*"                { BEGIN(COMMENT); }
<COMMENT>"*/"       { BEGIN(INITIAL); }
<COMMENT>([^*]|\n)+|. 	/* ignore comments */
<COMMENT><<EOF>>    { printf("Error: Unterminated comment\n"); return token::END; } 

[ \t\n]+			/* ignore whitespace */
"//"[^\n]*	   		/* ignore comments */

":=" return token::ASSIGN;
"+" return token::ADD;
"=" return token::EQUALS;
"(" return token::OPEN_PAREN;
")" return token::CLOSE_PAREN;
"[" return token::LIST_START;
"]" return token::LIST_END;
"," return token::COMMA;
";" return token::SEMICOLON;

[0-9]+ {
	yylval->ival = atoi(yytext);
	return token::INTEGER;
}
[a-zA-Z][a-zA-Z0-9]*    { 
	yylval->symbol = yytext; 
	return token::IDENTIFIER;
} 

.	printf("bad input character '%s' at line %d\n", yytext, yylineno);

%%
