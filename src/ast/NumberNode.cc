#include "NumberNode.hh"

namespace lucy {

NumberNode::NumberNode(long val) : val(val) {}

std::string NumberNode::toString() {
	return std::to_string(val);
}

std::string NumberNode::getType() {
    return "NumberNode";
}

}
