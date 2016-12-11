#pragma once
#include "ASTNode.hh"

namespace lucy {

class IntegerNode : public ASTNode {

public:
    IntegerNode(long val);
    std::string toString();
    std::string getNodeType() { return "IntegerNode"; }
    PrimitiveType getLucyType() { return Integer; }

    long val;

};

}
