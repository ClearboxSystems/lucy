#pragma once

namespace lucy {

enum PrimitiveType {
    undefined,
    Integer,
    Float
};

//struct TupleType {
//    int size;
//    struct LucyType args[];
//};
//
//struct FunctionType {
//    LucyType args;
//    LucyType result;
//};
//
//union LucyType {
//    PrimitiveType value;
//    TupleType tuple;
//    FunctionType func;
//    std::string alias;
//};
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