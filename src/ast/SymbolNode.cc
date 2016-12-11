#include "SymbolNode.hh"

namespace lucy {

SymbolNode::SymbolNode(const std::string &name, PrimitiveType lucyType) 
				: name(name), lucyType(lucyType) {}

std::string SymbolNode::toString() {
	return name + " : " + lucyTypeToString(lucyType);
}

PrimitiveType SymbolNode::getLucyType() {
    return lucyType;
}

}
