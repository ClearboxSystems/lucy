#include "FloatNode.hh"

namespace lucy {

FloatNode::FloatNode(double val) : val(val) {}

std::string FloatNode::toString() {
	return std::to_string(val);
}

}
