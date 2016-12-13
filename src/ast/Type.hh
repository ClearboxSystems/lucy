#pragma once

#include <vector>

namespace lucy {

enum PrimitiveType {
    undefined,
    Integer,
    Float
};

struct LucyType {
    enum {Primitive, Tuple, Function, Alias} type;
    union {
        PrimitiveType primitive;
        std::vector<struct LucyType *> tuple;
        std::pair<struct LucyType *, struct LucyType *> funcion;
        std::string alias;
    };
};

class TypeChecker {
public:
    TypeChecker()  {}


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