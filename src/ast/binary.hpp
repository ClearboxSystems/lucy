#pragma once
#include "node.hpp"

class BinaryNode : public ASTNode {
  char op;
  ASTNode *lhs, *rhs;

public:
  BinaryNode(char op, ASTNode *lhs, ASTNode *rhs);
};
