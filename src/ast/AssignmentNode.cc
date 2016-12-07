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

}
