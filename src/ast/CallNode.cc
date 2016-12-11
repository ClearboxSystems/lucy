#include "CallNode.hh"
#include <sstream>

namespace lucy {
using namespace std;

CallNode::CallNode(const std::string &name, 
	std::vector<ASTNode *> &args) 
		: name(name), 
		  args(std::move(args)) {}

std::string CallNode::toString() {
	stringstream result;

	result << name << "(";
	bool first = true;
	for (auto arg = args.begin(); arg != args.end(); ++arg) {
		if (first)
			first = false;
		else
			result << ", ";

		result << (*arg)->toString();
	}

	result << ")";
	return result.str();
}

} // namespace lucy