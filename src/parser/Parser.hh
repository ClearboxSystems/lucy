#pragma once
#include "../ast.hh"

namespace lucy {

class Parser {
public:
	int testLexer(int argc, char **argv);
	void emitStatement(ASTNode *node);
};

}
