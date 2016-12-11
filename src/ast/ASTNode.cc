#include "ASTNode.hh"
#include <cstdio>

namespace lucy {
ASTNode::~ASTNode() {
}

std::string ASTNode::lucyTypeToString(PrimitiveType type) {
	switch (type) {
		case undefined: return "undefined";
		case Integer: return "Integer";
		case Float: return "Float";
	}

	return "UNKNOWN TYPE";
}

}