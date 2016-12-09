#pragma once
#include "FunctionPrototype.hh"
#include "ASTNode.hh"

namespace lucy {

class FunctionDef {

public:
    FunctionDef(FunctionPrototype *proto, ASTNode *body);
    std::string toString();
    std::string getType();

    FunctionPrototype *proto;
    ASTNode *body;
};

}
