#include "BinaryNode.hh"
#include <sstream>

namespace lucy {
using namespace std;

BinaryNode::BinaryNode(char opcode, ASTNode *lhs, ASTNode *rhs)
    : opcode(opcode), lhs(lhs), rhs(rhs), lucyType(undefined) {}

std::string BinaryNode::toString() {
	stringstream result;

	result << "(" << lhs->toString() << " " << opcode << " " << rhs->toString() << ")";

	return result.str();
}

bool BinaryNode::typeCheck() {
	if (lhs->getLucyType() == undefined)
		if (!lhs->typeCheck())
			return false;

 	if (rhs->getLucyType() == undefined)
		if (!rhs->typeCheck())
			return false;

	if (lhs->getLucyType() == rhs->getLucyType()) {
		lucyType = lhs->getLucyType();
		return true;
	} 

	return false;
}

}
