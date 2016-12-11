#include "IntegerNode.hh"

namespace lucy {

IntegerNode::IntegerNode(long val) : val(val) {}

std::string IntegerNode::toString() {
	return std::to_string(val);
}

}
