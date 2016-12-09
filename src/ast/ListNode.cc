#include "ListNode.hh"
#include <sstream>

namespace lucy {
using namespace std;

ListNode::ListNode(std::vector<ASTNode *> *list)
        : list(list) {}

std::string ListNode::toString() {
	stringstream result;

	result << "[";

	bool first = true;
	for (auto node = list->begin(); node != list->end(); ++node) {
		if (first)
			first = false;
		else
			result << ", ";

		result << (*node)->toString();
	}

	result << "]";
	return result.str();
}

std::string ListNode::getType() {
    return "ListNode";
}

}
