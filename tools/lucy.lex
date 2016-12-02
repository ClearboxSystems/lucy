%{
#include "lucy.tab.hpp"
#define YY_DECL extern "C" int yylex()
%}
%%
"+"         { return ADD; }
"-"         { return SUB; }
"*"         { return MUL; }
"/"         { return DIV; }
"|"         { return ABS; }
[0-9]+      { yylval = atoi(yytext); return NUMBER; }
\n          { return EOL; }
[ \t]       {}
.           { printf("Unexpected character %c\n", *yytext); }
%%
