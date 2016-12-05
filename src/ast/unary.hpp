#pragma once
#include "node.hpp"


class UnaryNode : public ASTNode {
    char opcode;
    ASTNode *operand;

public:
    UnaryNode(char opcode, ASTNode *operand);
  
};
