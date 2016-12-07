#pragma once
#include "ASTNode.hh"

namespace lucy {

class BinaryNode : public ASTNode {
  char opcode;
  ASTNode *lhs, *rhs;

public:
  BinaryNode(char opcode, ASTNode *lhs, ASTNode *rhs);
  std::string toString();
};

}
