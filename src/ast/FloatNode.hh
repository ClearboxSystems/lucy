#pragma once
#include "ASTNode.hh"

namespace lucy {

class FloatNode : public ASTNode {

public:
    FloatNode(double val);
    std::string toString();
    std::string getNodeType() {return "FloatNode"; }

    double val;
};

}
