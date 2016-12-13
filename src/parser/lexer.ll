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
<COMMENT>([^*]|\n)+|.   /* ignore comments */
<COMMENT><<EOF>>    { printf("Error: Unterminated comment\n"); return token::END; } 

[ \t\n]+            /* ignore whitespace */
"//"[^\n]*          /* ignore comments */

"fun"       return token::FUN;
"extern"    return token::EXTERN;
"int"       return token::PRIM_INT;
"float"     return token::PRIM_FLOAT;


":="        return token::ASSIGN;
"+"         return token::ADD;
"-"         return token::SUBTRACT;
"*"         return token::MULTIPLY;
"/"         return token::DIVIDE;
"="         return token::EQUALS;
"("         return token::OPEN_PAREN;
")"         return token::CLOSE_PAREN;
"["         return token::LIST_START;
"]"         return token::LIST_END;
","         return token::COMMA;
";"         return token::SEMICOLON;
":"         return token::COLON;

0x[0-9a-fA-F_]+ {
    yylval->ival = strtol(yytext, nullptr, 16);
    return token::INTEGER;
}

0o[0-7_]+ {
    yylval->ival = strtol(yytext, nullptr, 8);
    return token::INTEGER;
}

0b[01_]+ {
    yylval->ival = strtol(yytext, nullptr, 2);
    return token::INTEGER;
}

[0-9][0-9_]* {
    yylval->ival = strtol(yytext, nullptr, 10);
    return token::INTEGER;
}

[0-9][0-9_]*\.[0-9_]*([eE][-\+]?[0-9_]+)? {
	yylval->fval = strtod(yytext, nullptr);
	return token::FLOAT;	
}

[0-9][0-9_]*(\.[0-9_]*)?[eE][-\+]?[0-9_]+ {
	yylval->fval = strtod(yytext, nullptr);
	return token::FLOAT;	
}

[a-zA-Z_][a-zA-Z0-9_]*    { 
    yylval->string = new std::string(yytext); 
    return token::IDENTIFIER;
} 

.   printf("bad input character '%s' at line %d\n", yytext, yylineno);

%%
