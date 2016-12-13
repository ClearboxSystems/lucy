#pragma once

#include <vector>
#include <string>
#include "../ast.hh"

namespace lucy {

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
    bool typeCheckAST(AssignmentNode* node);
    bool typeCheckAST(BinaryNode* node);
    bool typeCheckAST(CastNode* node);

public:
    TypeChecker()  {}

    bool typeCheckAST(ASTNode *node);
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