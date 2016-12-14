#include "SymbolNode.hh"
#include "Type.hh"
#include "../codegen/SymbolTable.hh"

namespace lucy {

SymbolNode::SymbolNode(const std::string &name, PrimitiveType primType) 
                : ASTNode(LucyType::getPrimitive(primType)), name(name) {}

std::string SymbolNode::toString() {
    return name + " : " + lucyTypeToString(lucyType);
}

}
