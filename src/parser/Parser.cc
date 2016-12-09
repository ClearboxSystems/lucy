#include "Parser.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Lexer.hh"

//extern void processASTNode(lucy::ASTNode *node);

namespace lucy {
using namespace std;

class ParserImpl {
public:
    ParserImpl(Parser &parent, IParserCallback &parserCallback) 
        : parent(parent), 
          callback(parserCallback) {}

        void setDebugLexer(bool on) { debugLexer = on; }
        void setDebugParser(bool on) { debugParser = on; }
        
        void parseConsole() {
            Lexer lexer = Lexer();
            BisonParser parser(lexer, parent);

            repl = true;
            
            if (debugLexer) 
                lexer.set_debug(true);

            if (debugParser) 
                parser.set_debug_level(true);
            
            lexer.setInput(&std::cin);
            cout << "> ";
            parser.parse();
        }

        void parseFiles(std::vector<std::string> &files) {
            Lexer lexer = Lexer();
            BisonParser parser(lexer, parent);

            repl = false;
            
            if (debugLexer) 
                lexer.set_debug(true);

            if (debugParser) 
                parser.set_debug_level(true);

            for (auto file = files.begin(); file != files.end(); ++file) {
                cout << "Lexing file: " << *file << endl;
                ifstream fileStream;
                fileStream.open(*file);
                if (fileStream.is_open()) {
                    lexer.setInput(&fileStream);
                    parser.parse();
                    fileStream.close();
                } else {
                    fprintf(stderr, "Unable to open: %s\n" , (*file).c_str());
                }
            }
        }

        void emitStatement(ASTNode *node) {
            cout << node->toString() << endl;
            callback.handleStatement(node);
            if (repl) cout << "> ";
        }
        
private:    
    Parser &parent;
    IParserCallback &callback;
    
    bool debugLexer = false;
    bool debugParser = false;
    bool repl = false;
};

//void Parser::emitStatement(ASTNode *node) {
//    cout << node->toString() << endl;
//    processASTNode(node);
//    cout << "> ";
//}
//

//void doLexing(Lexer &lexer) {
//    BisonParser::semantic_type tokval;
//
//    int tok;
//    while ((tok = lexer.yylex(&tokval)) != BisonParser::token::END) {
//        printf("Lex: %d", tok);
//        if (tok == BisonParser::token::INTEGER)
//            printf("\t INT -> %d", tokval.ival);
//        printf("\n");               
//    }
//    printf("Lex: %d\n", tok);
//
//}

//int Parser::testLexer(int argc, char **argv) {
//    string input;
//    vector<string> files;
//
//    bool debugLexer = false;
//    bool debugParser = false;
//    for (int i = 1; i < argc; ++i)
//        if (argv[i] == string ("-s"))
//            debugLexer = true;
//        else if (argv[i] == string ("-p"))
//            debugParser = true;
//        else if (argv[i][0] != '-')
//            files.push_back(argv[i]);
//
//    Lexer lexer = Lexer();
//    BisonParser parser(lexer, *this);
//
//    if (debugLexer) 
//        lexer.set_debug(true);
//
//    if (debugParser) 
//        parser.set_debug_level(true);
//
//    if (files.size() > 0) {
//        for (auto file = files.begin(); file != files.end(); ++file) {
//            cout << "Lexing file: " << *file << endl;
//            ifstream fileStream;
//            fileStream.open(*file);
//            if (fileStream.is_open()) {
//                lexer.setInput(&fileStream);
//                parser.parse();
////                doLexing(lexer);
//                fileStream.close();
//            } else {
//                fprintf(stderr, "Unable to open: %s\n" , (*file).c_str());
//            }
//        }
//    } else {
//        fprintf(stderr, "> ");
////        while (std::getline(std::cin, input)) {
////            std::istringstream iss(input);
//            lexer.setInput(&std::cin);
//            parser.parse();
////            doLexing(lexer);
////            fprintf(stderr, "ready> ");
////        }
//        fprintf(stderr, "\n");
//    }
//    return 0;
//}

Parser::Parser(IParserCallback &parserCallback) : pImpl(new ParserImpl(*this, parserCallback)) {}
void Parser::setDebugLexer(bool on) { pImpl->setDebugLexer(on); }
void Parser::setDebugParser(bool on) { pImpl->setDebugParser(on); }
void Parser::parseFiles(std::vector<std::string> &files) { pImpl->parseFiles(files); }
void Parser::parseConsole() { pImpl->parseConsole(); }
void Parser::emitStatement(ASTNode *node) { pImpl->emitStatement(node); }



} // namespace lucy

