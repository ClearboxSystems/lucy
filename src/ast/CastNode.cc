#include "CastNode.hh"
#include <sstream>
namespace lucy {

std::string CastNode::toString() {
    std::stringstream result;
    result << "((" << lucyTypeToString(lucyType) << ") " << node->toString() << ")";
    return result.str();
}
    
} // namespace lucy
