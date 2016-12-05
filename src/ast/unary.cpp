#include "unary.hpp"


UnaryNode::UnaryNode(char opcode, ASTNode *operand)
    : opcode(opcode), operand(operand) {}