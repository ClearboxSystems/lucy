#include "parser/Parser.hh"
#include "codegen/IRRenderer.hh"
#include "ast.hh"

#include <vector>
#include <string>
#include <iostream>

namespace lucy {
using namespace std;
    
class Lucy : public IParserCallback {
    IRRenderer renderer;
    Parser &parser;

public:
    Lucy() : parser(*(new Parser(*this))) {}
    
    void handleStatement(ASTNode *node) {
        if (node->typeCheck()) {
            renderer.handleTopLevel(node);
        } else {
            cerr << "Typecheck Failed!" << endl;            
        }
    };
    
    void handleDefinition(FunctionDef *definition) {
        llvm::Function *fun = renderer.generateIR(definition);
//        fun->dump();
    };
    
    void handleExtern(FunctionPrototype *proto) {
        renderer.handleExtern(proto);
    };
    
    int main(int argc, char **argv) {
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

        parser.setDebugLexer(debugLexer);
        parser.setDebugParser(debugParser);

        if (files.size() > 0) 
            parser.parseFiles(files);
        else
            parser.parseConsole();

        return 0;        
    }
};

} // namespace lucy;

int main(int argc, char **argv) {
    lucy::Lucy lucy;    
    return lucy.main(argc, argv);
}


