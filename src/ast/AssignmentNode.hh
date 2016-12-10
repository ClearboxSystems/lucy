#pragma once
#include "ASTNode.hh"
#include "SymbolNode.hh"

namespace lucy {

class AssignmentNode : public ASTNode {
public:
  AssignmentNode(SymbolNode *symbol, ASTNode *rhs);
  std::string toString();
  std::string getType();

  SymbolNode *symbol;
  ASTNode *rhs;

};

}
