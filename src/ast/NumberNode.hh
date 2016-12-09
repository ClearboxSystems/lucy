#pragma once
#include "ASTNode.hh"

namespace lucy {

class NumberNode : public ASTNode {

public:
    NumberNode(long val);
    std::string toString();
    std::string getType();

    long val;

};

}
