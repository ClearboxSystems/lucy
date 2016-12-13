#include "FloatNode.hh"
#include "Type.hh"

namespace lucy {

FloatNode::FloatNode(double val) : ASTNode(LucyType::getPrimitive(Float)), val(val) {}

std::string FloatNode::toString() {
	return std::to_string(val);
}

}
