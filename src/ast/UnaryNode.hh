#pragma once
#include "ASTNode.hh"

namespace lucy {

class UnaryNode : public ASTNode {
public:
    UnaryNode(char opcode, ASTNode *operand);
    std::string toString();  
    std::string getNodeType() { return "UnaryNode"; }

    bool typeCheck();


    char opcode;
    ASTNode *operand;

};

}
