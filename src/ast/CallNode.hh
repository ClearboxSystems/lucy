#pragma once
#include "ASTNode.hh"

#include <vector>
#include <string>

namespace lucy {

class CallNode : public ASTNode {

public:
  CallNode(const std::string &name, std::vector<ASTNode *> &args);
  std::string toString();
  std::string getNodeType() { return "CallNode"; }

  std::string name;
  std::vector<ASTNode *> args;  
};

} // namespace lucy
