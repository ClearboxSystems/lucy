#include "UnaryNode.hh"
#include <sstream>

namespace lucy {
using namespace std;

UnaryNode::UnaryNode(char opcode, ASTNode *operand)
    : opcode(opcode), operand(operand) {}

std::string UnaryNode::toString() {
	stringstream result;

	result << "("  << opcode << " " << operand->toString() << ")";

	return result.str();
}

}
