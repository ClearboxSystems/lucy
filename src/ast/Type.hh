#pragma once

#include <vector>
#include <string>
#include "../ast.hh"

namespace lucy {

class SymbolTable;
struct LucyType {
    LucyType() {}
    enum {Primitive, Tuple, Function, Alias} type;
    union {
        PrimitiveType primitive;
        std::vector<struct LucyType *> tuple;
        std::pair<struct LucyType *, struct LucyType *> function;
        std::string alias;
    };
    
    static struct LucyType *getPrimitive(PrimitiveType prim) {
        if (prim == undefined) return nullptr;
        
        struct LucyType *lt = new (struct LucyType);
        lt->type = Primitive;
        lt->primitive = prim;
        return lt;
    }

    bool equals(LucyType *that) {
        if (type != that->type)
            return false;

        if (type == Primitive && primitive == that->primitive)
            return true;

        // FIXME: This needs to be implemented for other types
        return false;
    }
};

class TypeChecker {
    bool typeCheckAST(AssignmentNode* node, SymbolTable *symbolTable);
    bool typeCheckAST(BinaryNode* node, SymbolTable *symbolTable);
    bool typeCheckAST(CastNode* node, SymbolTable *symbolTable);
    bool typeCheckAST(SymbolNode* node, SymbolTable *symbolTable);
    
public:
    TypeChecker() {}

    bool typeCheckAST(ASTNode *node, SymbolTable *symbolTable);
};

//
//std::map<std::string, LucyType *> typeTable;
//


/*

let a : int64 = 12;
let b : float64 = 12;

type real := float64;

let c : real = a;

type money := { dollars: int, cents: int };

 * fun 

*/


} // namespace lucy