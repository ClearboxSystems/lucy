#pragma once
#include "node.hpp"

class NumberNode : public ASTNode {
    int val;

public:
    NumberNode(int val);

};
