%option noyywrap

%x COMMENT

%{
#include "lucy.tab.hpp"
#define YY_DECL extern "C" int yylex()
%}

%%
"/*"                { BEGIN(COMMENT); }
<COMMENT>"*/"       { BEGIN(INITIAL); }
<COMMENT>([^*]|\n)+|.
<COMMENT><<EOF>>    { printf("Unterminated comment\n"); } 
"//".*\n    /* ignore comments */

"+"         { return ADD; }
"-"         { return SUB; }
"*"         { return MUL; }
"/"         { return DIV; }
"("         { return OP;  }
")"         { return CP;  }
"["         { return OL;  }
"]"         { return CL;  }
"="         { return EQUAL;  }
","         { return LS;  }
";"         { return EOS; }
":="        { return ASSIGN; }
[0-9]+      { yylval.num = atoi(yytext); return NUMBER; }
[a-zA-Z][a-zA-Z0-9]*    { yylval.symbol = yytext; return IDENT; }
[ \t\n]     /* ignore whitespace */
.           { printf("Unexpected character %c\n", *yytext); }
%%

void doLex() {
    int tok;
    while( (tok = yylex()) ) {
        printf("%d", tok);
        if(tok == NUMBER) printf(" = %d\n", yylval.num); else
        if(tok == IDENT) printf(" = %s\n", yylval.symbol);
        else printf("\n");
    }
}

int main(int argc, char **argv) {
    int i;
    if(argc < 2) { /* just read stdin */
//        curfilename = "(stdin)";
//        yylineno = 1;
        doLex();
    } else
    for(i = 1; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");

        if(!f) {
            perror(argv[1]);
            return (1);
        }
//        curfilename = argv[i]; /* for addref */
        yyrestart(f);
//        yylineno = 1;
        doLex();
        fclose(f);
    }
}