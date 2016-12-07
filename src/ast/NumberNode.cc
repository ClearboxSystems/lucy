#include "NumberNode.hh"

namespace lucy {

NumberNode::NumberNode(int val) : val(val) {}

std::string NumberNode::toString() {
	return std::to_string(val);
}

}
