// #include "parser/tree.hpp"
// #include <iostream>
// #include <sstream>
// #include <string>

// int main(int argc, char **argv) {
//     void *l_val;
    
//     STree *tree = new STree();
    
//     std::string input;
//     fprintf(stderr, "ready> ");
//     while (std::getline(std::cin, input, ';')) {
//         std::istringstream iss(input);

//         tree->parse(iss);
//         fprintf(stderr, "ready> ");
//     }
    
//     return 0;
// }

#include "parser/Parser.hh"
#include "codegen/IRRenderer.hh"
#include "ast.hh"

#include <vector>
#include <string>
#include <iostream>

using namespace lucy;
using namespace std;

class Lucy : public IParserCallback {
    IRRenderer renderer;
    Parser &parser;

public:
    Lucy() : parser(*(new Parser(*this))) {}
    
    void handleStatement(ASTNode *node) {
        llvm::Value *val = renderer.generateIR(node);
        val->dump();        
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

int main(int argc, char **argv) {
    Lucy lucy;    
    return lucy.main(argc, argv);
}


