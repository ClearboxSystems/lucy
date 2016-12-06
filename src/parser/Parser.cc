#include "Parser.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Lexer.hh"

namespace lucy {
using namespace std;




void doLexing(Lexer &lexer) {
    BisonParser::semantic_type tokval;

    int tok;
    while ((tok = lexer.yylex(&tokval)) != BisonParser::token::END) {
        printf("Lex: %d", tok);
        if (tok == BisonParser::token::INTEGER)
            printf("\t INT -> %d", tokval.ival);
        printf("\n");               
    }
    printf("Lex: %d\n", tok);

}

int Parser::testLexer(int argc, char **argv) {
	string input;
    vector<string> files;

    bool debugLexer = false;
    bool debugParser = false;
    for (int i = 1; i < argc; ++i)
        if (argv[i] == string ("-s"))
            debugLexer = true;
        else if (argv[i] == string ("-p"))
            debugParser = true;
        else if (argv[i][0] != '-')
            files.push_back(argv[i]);

    Lexer lexer = Lexer();
    BisonParser parser(lexer, *this);

    if (debugLexer) 
        lexer.set_debug(true);

    if (debugParser) 
        parser.set_debug_level(true);

    if (files.size() > 0) {
        for (auto file = files.begin(); file != files.end(); ++file) {
            cout << "Lexing file: " << *file << endl;
            ifstream fileStream;
            fileStream.open(*file);
            if (fileStream.is_open()) {
                lexer.setInput(&fileStream);
                parser.parse();
//                doLexing(lexer);
                fileStream.close();
            } else {
                fprintf(stderr, "Unable to open: %s\n" , (*file).c_str());
            }
        }
    } else {
        fprintf(stderr, "ready> ");
//        while (std::getline(std::cin, input)) {
//            std::istringstream iss(input);
            lexer.setInput(&std::cin);
            parser.parse();
//            doLexing(lexer);
//            fprintf(stderr, "ready> ");
//        }
        fprintf(stderr, "\n");
    }
    return 0;
}
}

