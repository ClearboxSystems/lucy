#pragma once
#include "ASTNode.hh"

namespace lucy {

class SymbolNode : public ASTNode {

public:
    SymbolNode(const std::string &name, PrimitiveType lucyType = undefined);
    std::string toString();
    std::string getNodeType() { return "SymbolNode"; }
    PrimitiveType getLucyType();

    const std::string name;
    PrimitiveType lucyType;
};

}