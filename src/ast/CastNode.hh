#pragma once
#include "ASTNode.hh"

namespace lucy {

class CastNode : public ASTNode {
public:
    CastNode(ASTNode *node, LucyType *lucyType) : ASTNode(lucyType), node(node) {}
    std::string toString();
    std::string getNodeType() {return "CastNode"; }    

    ASTNode *node;
};

} // namespace lucy
