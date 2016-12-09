#pragma once
#include "../ast.hh"
#include <vector>
#include <string>

namespace lucy {

class IParserCallback {
public:
    virtual void handleStatement(ASTNode *node) = 0;
    virtual void handleDefinition(FunctionDef *definition) = 0;
    virtual void handleExtern(FunctionPrototype *proto) = 0;
    virtual ~IParserCallback(){}
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
    void emitDefinition(FunctionDef *definition);    
    void emitExtern(FunctionPrototype *proto);    
private:
    ParserImpl *pImpl;
};

}
