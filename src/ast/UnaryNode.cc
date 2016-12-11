#include "UnaryNode.hh"
#include <sstream>

namespace lucy {
using namespace std;

UnaryNode::UnaryNode(char opcode, ASTNode *operand)
    : opcode(opcode), operand(operand), lucyType(undefined) {}

std::string UnaryNode::toString() {
	stringstream result;

	result << "("  << opcode << " " << operand->toString() << ")";

	return result.str();
}

bool UnaryNode::typeCheck() {
 	if (operand->getLucyType() == undefined)
		if (!operand->typeCheck())
			return false;

	lucyType = operand->getLucyType();
	return true;
}

}
