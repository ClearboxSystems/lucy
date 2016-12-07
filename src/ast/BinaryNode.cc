#include "BinaryNode.hh"
#include <sstream>

namespace lucy {
using namespace std;

BinaryNode::BinaryNode(char opcode, ASTNode *lhs, ASTNode *rhs)
    : opcode(opcode), lhs(lhs), rhs(rhs) {}

std::string BinaryNode::toString() {
	stringstream result;

	result << "(" << lhs->toString() << " " << opcode << " " << rhs->toString() << ")";

	return result.str();
}

}
