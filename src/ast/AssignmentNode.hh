#pragma once
#include "ASTNode.hh"
#include "SymbolNode.hh"

namespace lucy {

class AssignmentNode : public ASTNode {
  SymbolNode *symbol;
  ASTNode *rhs;

public:
  AssignmentNode(SymbolNode *symbol, ASTNode *rhs);
  std::string toString();
};

}
