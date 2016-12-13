#pragma once
#include "ASTNode.hh"
#include "SymbolNode.hh"

namespace lucy {

class AssignmentNode : public ASTNode {
public:
  AssignmentNode(SymbolNode *symbol, ASTNode *rhs);
  std::string toString();
  std::string getNodeType() { return "AssignmentNode"; }
  
  SymbolNode *symbol;
  ASTNode *rhs;
};

}
