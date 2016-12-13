#pragma once
#include "ASTNode.hh"

namespace lucy {

class BinaryNode : public ASTNode {

public:
  BinaryNode(char opcode, ASTNode *lhs, ASTNode *rhs);
  std::string toString();
  std::string getNodeType() { return "BinaryNode"; }
  
  bool typeCheck();

  char opcode;
  ASTNode *lhs, *rhs;

};

}
