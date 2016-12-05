#include "binary.hpp"

BinaryNode::BinaryNode(char op, ASTNode *lhs, ASTNode *rhs)
    : op(op), lhs(lhs), rhs(rhs) {}