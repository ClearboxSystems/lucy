#pragma once
#include "ASTNode.hh"

namespace lucy {

class NumberNode : public ASTNode {
    int val;

public:
    NumberNode(int val);
  	std::string toString();
};

}
