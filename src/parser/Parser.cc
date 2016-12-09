#include "Parser.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Lexer.hh"

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

        void emitDefinition(FunctionDef *definition) {
            cout << definition->toString() << endl;
            callback.handleDefinition(definition);
            if (repl) cout << "> ";
        }
        
        void emitExtern(FunctionPrototype *proto) {
            cout << "extern " << proto->toString() << endl;
            callback.handleExtern(proto);
            if (repl) cout << "> ";
        }
        
private:    
    Parser &parent;
    IParserCallback &callback;
    
    bool debugLexer = false;
    bool debugParser = false;
    bool repl = false;
};

Parser::Parser(IParserCallback &parserCallback) : pImpl(new ParserImpl(*this, parserCallback)) {}
void Parser::setDebugLexer(bool on) { pImpl->setDebugLexer(on); }
void Parser::setDebugParser(bool on) { pImpl->setDebugParser(on); }
void Parser::parseFiles(std::vector<std::string> &files) { pImpl->parseFiles(files); }
void Parser::parseConsole() { pImpl->parseConsole(); }
void Parser::emitStatement(ASTNode *node) { pImpl->emitStatement(node); }
void Parser::emitDefinition(FunctionDef *definition) { pImpl->emitDefinition(definition); }
void Parser::emitExtern(FunctionPrototype *proto) { pImpl->emitExtern(proto); }

} // namespace lucy

