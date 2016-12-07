#pragma once
#include "ASTNode.hh"

namespace lucy {

class SymbolNode : public ASTNode {
  const std::string name;

public:
  SymbolNode(const std::string &name);
  std::string toString();
};

}