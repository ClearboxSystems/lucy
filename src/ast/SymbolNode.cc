#include "SymbolNode.hh"

namespace lucy {

SymbolNode::SymbolNode(const std::string &name) : name(name) {}

std::string SymbolNode::toString() {
	return name;
}

std::string SymbolNode::getType() {
    return "SymbolNode";
}

}
