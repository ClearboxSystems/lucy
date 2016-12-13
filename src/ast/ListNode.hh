#pragma once
#include "ASTNode.hh"
#include <vector>

namespace lucy {

class ListNode : public ASTNode {
    std::vector<ASTNode *> *list;
public:
    ListNode(std::vector<ASTNode *> *list);
    std::string toString();
    std::string getNodeType() { return "ListNode" ;}
};

}
