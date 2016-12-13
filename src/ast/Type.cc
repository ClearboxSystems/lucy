#include "Type.hh"
#include "../ast.hh"

#include <iostream>

namespace lucy {
    
bool TypeChecker::typeCheckAST(ASTNode *node) {
    std::cout << "Typechecking " << node->getNodeType() << ": " << node->toString() << std::endl;
    std::cout << "Type: " << node->lucyTypeToString(node->lucyType) << std::endl;
    
    if(node->getNodeType() == "AssignmentNode") return typeCheckAST((AssignmentNode *)node);
    if(node->getNodeType() == "BinaryNode") return typeCheckAST((BinaryNode *)node);
    if(node->getNodeType() == "CastNode") return typeCheckAST((CastNode *)node);
    
    return true;
}

bool TypeChecker::typeCheckAST(AssignmentNode* node) {
    bool result = typeCheckAST(node->rhs);
    if (!result) {
        std::cout << "Returning false" << std::endl;
        return result;
    }

    if (node->symbol->lucyType == nullptr) {
        node->symbol->lucyType = node->rhs->lucyType;
        return true;        
    }
    
    return (node->symbol->lucyType->equals(node->rhs->lucyType));    
}

bool TypeChecker::typeCheckAST(BinaryNode* node) {
    bool result = typeCheckAST(node->lhs);
    if (!result) {
        std::cout << "Returning false" << std::endl;
        return result;
    }
    
    result = typeCheckAST(node->rhs);
    if (!result) {
        std::cout << "Returning false" << std::endl;
        return result;
    }

    if (node->lhs->lucyType->type == LucyType::Primitive && node->rhs->lucyType->type == LucyType::Primitive) {
        if (node->lhs->lucyType->primitive != node->rhs->lucyType->primitive) {
            if (node->lhs->lucyType->primitive == Integer && node->rhs->lucyType->primitive == Float) {
                node->lhs = new CastNode(node->lhs, LucyType::getPrimitive(Float));
            } else if (node->rhs->lucyType->primitive == Integer && node->lhs->lucyType->primitive == Float) {
                node->rhs = new CastNode(node->rhs, LucyType::getPrimitive(Float));
            }
        }
        
        node->lucyType = node->lhs->lucyType;
        return true;
    }

    std::cout << "Returning false" << std::endl;

    return false;
}

bool TypeChecker::typeCheckAST(CastNode* node) {
    bool val = typeCheckAST(node->node);    
    std::cout << "cast returning " << val << std::endl;
    return val;
}

} // namespace lucy
