#pragma once
#include "ASTNode.hh"

namespace lucy {

class UnaryNode : public ASTNode {
    char opcode;
    ASTNode *operand;

public:
    UnaryNode(char opcode, ASTNode *operand);
  	std::string toString();  
};

}
