#pragma once
#include "ASTNode.hh"

namespace lucy {

class SymbolNode : public ASTNode {

public:
    SymbolNode(const std::string &name, PrimitiveType primType = undefined);
    std::string toString();
    std::string getNodeType() { return "SymbolNode"; }

    const std::string name;
};

}