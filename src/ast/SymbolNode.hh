#pragma once
#include "ASTNode.hh"

namespace lucy {

class SymbolNode : public ASTNode {

public:
    SymbolNode(const std::string &name);
    std::string toString();
    std::string getType();

    const std::string name;
};

}