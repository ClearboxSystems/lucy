#include "IntegerNode.hh"
#include "Type.hh"

namespace lucy {

IntegerNode::IntegerNode(long val) : ASTNode(LucyType::getPrimitive(Integer)), val(val) {}

std::string IntegerNode::toString() {
	return std::to_string(val);
}

}
