#include "FunctionDef.hh"
#include <sstream>

namespace lucy {
using namespace std;

FunctionDef::FunctionDef(FunctionPrototype *proto, ASTNode *body) 
	: proto(proto), body(body) {}

std::string FunctionDef::toString() {
	stringstream result;

	result << proto->toString();
	result << " := ";
	result << body->toString();

	return result.str();
}

} // namespace lucy