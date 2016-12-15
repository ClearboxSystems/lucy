#include "Type.hh"
#include "../ast.hh"
#include "../codegen/SymbolTable.hh"

#include <iostream>

namespace lucy {
    
bool TypeChecker::typeCheckAST(ASTNode *node, SymbolTable *symbolTable) {
    node->symbolTable = symbolTable;

    std::cout << "Typechecking " << node->getNodeType() << ": " << node->toString() << std::endl;
    std::cout << "Type: " << node->lucyTypeToString(node->lucyType) << std::endl;
    
    if(node->getNodeType() == "AssignmentNode") return typeCheckAST((AssignmentNode *)node, symbolTable);
    if(node->getNodeType() == "BinaryNode") return typeCheckAST((BinaryNode *)node, symbolTable);
    if(node->getNodeType() == "CastNode") return typeCheckAST((CastNode *)node, symbolTable);
    if(node->getNodeType() == "SymbolNode") return typeCheckAST((SymbolNode *)node, symbolTable);
    
    return true;
}

bool TypeChecker::typeCheckAST(AssignmentNode* node, SymbolTable *symbolTable) {
    bool result = typeCheckAST(node->rhs, symbolTable);
    if (!result) {
        std::cout << "Returning false" << std::endl;
        return result;
    }

    Symbol *symbol = symbolTable->getSymbol(node->symbol->name, false);
    if (symbol) {
        std::cerr << "Cannot redefine symbol: " << node->symbol->name << std::endl;
        return false;
    }

    if (node->symbol->lucyType) {
        if (!node->symbol->lucyType->equals(node->rhs->lucyType)) {
            if (node->symbol->lucyType->type == LucyType::Primitive && node->rhs->lucyType->type == LucyType::Primitive) {
                if (node->rhs->lucyType->primitive == Integer && node->symbol->lucyType->primitive == Float) {
                    node->rhs = new CastNode(node->rhs, LucyType::getPrimitive(Float));
                } else if (node->symbol->lucyType->primitive == Integer && node->rhs->lucyType->primitive == Float) {
                    node->rhs = new CastNode(node->rhs, LucyType::getPrimitive(Integer));
                    std::cerr << "Warning, casting float to int, loss of precision" << std::endl;
                } else {
                    std::cerr << "Unable to cast unknown primitive types" << std::endl;
                    return false;
                }
            }  else {
                std::cerr << "Unable to cast non-primitive types" << std::endl;
                return false;
            }
        }
    } else {
        node->symbol->lucyType = node->rhs->lucyType;
    }

    // Add to symbol table.
    symbol = new Symbol();
    symbol->name = node->symbol->name;
    symbol->lucyType = node->symbol->lucyType;

    node->lucyType = node->symbol->lucyType;
    return symbolTable->addSymbol(symbol);
}

bool TypeChecker::typeCheckAST(BinaryNode* node, SymbolTable *symbolTable) {
    bool result = typeCheckAST(node->lhs, symbolTable);
    if (!result) {
        std::cout << "Returning false" << std::endl;
        return result;
    }
    
    result = typeCheckAST(node->rhs, symbolTable);
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

bool TypeChecker::typeCheckAST(CastNode* node, SymbolTable *symbolTable) {
    bool val = typeCheckAST(node->node, symbolTable);    
    std::cout << "cast returning " << val << std::endl;
    return val;
}

bool TypeChecker::typeCheckAST(SymbolNode* node, SymbolTable *symbolTable) {
    if (node->lucyType)
        return true;
    
    Symbol *symbol = symbolTable->getSymbol(node->name);
    if (symbol && symbol->lucyType) {
        node->lucyType = symbol->lucyType;            
        return true;
    }

    std::cerr << "Unresolved symbol: " << node->name << std::endl;
    return false;
}

} // namespace lucy
