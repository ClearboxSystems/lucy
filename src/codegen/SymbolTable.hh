#pragma once

#include "../ast/SymbolNode.hh"
#include "../ast/Type.hh"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Value.h"

#include <map>
#include <string>

namespace lucy {

struct Symbol {
    std::string name;
    struct LucyType *lucyType;
    llvm::Value *value;
};
        
class SymbolTable {
    std::map<std::string, struct Symbol *> symbols;
    std::map<std::string, llvm::AllocaInst *> allocations;
    SymbolTable *parent;
    bool allocaBarrier;
    
    ~SymbolTable();

public:
    SymbolTable(SymbolTable *parent = nullptr, bool allocaBarrier = true) : parent(parent), allocaBarrier(allocaBarrier) {}
    
    SymbolTable *pushScope(bool allocaBarrier);
    SymbolTable *popScope();    

};

} // namespace lucy
