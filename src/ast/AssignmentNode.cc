#include "AssignmentNode.hh"
#include <sstream>

namespace lucy {
using namespace std;

AssignmentNode::AssignmentNode(SymbolNode *symbol, ASTNode *rhs)
    : symbol(symbol), rhs(rhs) {}

std::string AssignmentNode::toString() {
	stringstream result;

	result << symbol->toString() << " := " << rhs->toString();

	return result.str();
}

bool AssignmentNode::typeCheck() {
	if (rhs->getLucyType() == undefined)
		if (!rhs->typeCheck())
			return false;

	if (symbol->lucyType == undefined) {
		symbol->lucyType = rhs->getLucyType();	
		return true;
	}

	return symbol->lucyType == rhs->getLucyType();
}

}
