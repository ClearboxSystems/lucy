#include "Parser.hh"

#include <iostream>
#include <sstream>
#include <string>
#include "Lexer.hh"

int parserRun(int argc, char **argv) {
	lucy::Parser::semantic_type tokval;

	std::string input;
    fprintf(stderr, "ready> ");
    int i = 0;
    while (std::getline(std::cin, input)) {
        std::istringstream iss(input);
        Lexer lexer = Lexer(&iss);

        while (int tok = lexer.yylex(&tokval)) {
        	printf("Lex: %d", tok);
        	if (tok == lucy::Parser::token::INTEGER)
	        	printf("\t INT -> %d", tokval.ival);
			printf("\n");        		
			i++;
			 if ( i > 10) break;
        }

        fprintf(stderr, "ready> ");
        i++

        if (i > 20) break;
    }

}