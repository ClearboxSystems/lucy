#pragma once
#include "node.hpp"
#include <vector>

class ListNode : public ASTNode {
    std::vector<ASTNode *> *list;
public:
    ListNode(std::vector<ASTNode *> *list);
  
};
