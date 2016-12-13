#include "ASTNode.hh"
#include "Type.hh"

#include <cstdio>
#include <sstream>
namespace lucy {
ASTNode::~ASTNode() {
}

std::string ASTNode::lucyTypeToString(LucyType *type) {
    if (!type)
        return "Undefined";

    if (type->type == LucyType::Primitive) {
        switch (type->primitive) {
            case Integer: return "Integer";
            case Float: return "Float";
            default: return "unknown primitive";
        }       
    }

    if (type->type == LucyType::Alias)
        return type->alias;
    
    if (type->type == LucyType::Tuple) {
        std::stringstream result;
        result << "(";
        
        bool first = true;
        for (auto node = type->tuple.begin(); node != type->tuple.end(); ++node) {
            if (first)
                first = false;
            else
                result << ", ";

            result << lucyTypeToString(*node);
        }

        result << ")";
        return result.str();
    }
    
    if (type->type == LucyType::Function) {
        std::stringstream result;
        
        result << lucyTypeToString(type->function.first);
        result << " -> ";
        result << lucyTypeToString(type->function.second);
        
        return result.str();
    }
    
    return "unknown type";
}

}