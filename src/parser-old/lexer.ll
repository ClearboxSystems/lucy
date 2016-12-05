%{
#include "bison_parser.hpp"
typedef bison::Parser::token token;
#define yyterminate() return token::END
%}


%option noyywrap nodefault yylineno

%x COMMENT

%%
"/*"                { BEGIN(COMMENT); }
<COMMENT>"*/"       { BEGIN(INITIAL); }
<COMMENT>([^*]|\n)+|.
<COMMENT><<EOF>>    { printf("Unterminated comment\n"); } 
"//".*\n    /* ignore comments */

"let"       { return token::LET; }

"+"         { return token::ADD; }
"-"         { return token::SUB; }
"*"         { return token::MUL; }
"/"         { return token::DIV; }
"("         { return token::OP;  }
")"         { return token::CP;  }
"["         { return token::OL;  }
"]"         { return token::CL;  }
"="         { return token::EQUAL;  }
","         { return token::LS;  }
";"         { return token::SEMICOLON; }
":="        { return token::ASSIGN; }
[0-9]+      { yylval->num = atoi(yytext); return token::NUMBER; }
[a-zA-Z][a-zA-Z0-9]*    { yylval->symbol = yytext; return token::IDENT; }
[ \t\n]     /* ignore whitespace */
.           { printf("Unexpected character %c\n", *yytext); }

%%