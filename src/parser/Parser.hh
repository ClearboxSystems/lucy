#pragma once
#include "../ast.hh"
#include <vector>
#include <string>

namespace lucy {

class IParserCallback {
public:
    virtual void handleStatement(ASTNode *node) = 0;
};    
    
class ParserImpl;    
class Parser {
public:
    Parser(IParserCallback &parserCallback);
    
    void setDebugLexer(bool on);
    void setDebugParser(bool on);

    void parseFiles(std::vector<std::string> &files);
    void parseConsole();
    
    void emitStatement(ASTNode *node);    
private:
    ParserImpl *pImpl;
};

}
