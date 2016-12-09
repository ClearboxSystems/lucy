#include "FunctionPrototype.hh"
#include <sstream>

namespace lucy {
using namespace std;

FunctionPrototype::FunctionPrototype(const std::string &name, 
	std::vector<std::string> &args) 
		: name(name), 
		  args(std::move(args)) {}

std::string FunctionPrototype::toString() {
	stringstream result;

	result << name << "(";
	bool first = true;
	for (auto arg = args.begin(); arg != args.end(); ++arg) {
		if (first)
			first = false;
		else
			result << ", ";

		result << (*arg);
	}

	result << ")";
	return result.str();
}

std::string FunctionPrototype::getType() {
    return "FunctionPrototype";
}

} // namespace lucy