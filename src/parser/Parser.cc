#include "Parser.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Lexer.hh"

void doLexing(Lexer &lexer) {
    lucy::Parser::semantic_type tokval;

    int tok;
    while ((tok = lexer.yylex(&tokval)) != lucy::Parser::token::END) {
        printf("Lex: %d", tok);
        if (tok == lucy::Parser::token::INTEGER)
            printf("\t INT -> %d", tokval.ival);
        printf("\n");               
    }
    printf("Lex: %d\n", tok);

}

int testLexer(int argc, char **argv) {
	std::string input;
    std::vector<std::string> files;

    bool debugLexer = false;
    for (int i = 1; i < argc; ++i)
        if (argv[i] == std::string ("-s"))
            debugLexer = true;
        else if (argv[i][0] != '-')
            files.push_back(argv[i]);

    Lexer lexer = Lexer();
    if (debugLexer) 
        lexer.set_debug(true);


    if (files.size() > 0) {
        for (auto file = files.begin(); file != files.end(); ++file) {
            std::cout << "Lexing file: " << *file << std::endl;
            std::ifstream fileStream;
            fileStream.open(*file);
            if (fileStream.is_open()) {
                lexer.setInput(&fileStream);
                doLexing(lexer);
                fileStream.close();
            } else {
                fprintf(stderr, "Unable to open: %s\n" , (*file).c_str());
            }
        }
    } else {
        fprintf(stderr, "ready> ");
        while (std::getline(std::cin, input)) {
            std::istringstream iss(input);
            lexer.setInput(&iss);
            doLexing(lexer);
            fprintf(stderr, "ready> ");
        }
        fprintf(stderr, "\n");
    }
    return 0;
}
