#pragma once

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

    Symbol *getSymbol(const std::string &name, bool traverseParents = true);
    bool addSymbol(Symbol *symbol);
    bool storeValue(const std::string &name, llvm::Value *value);
};

} // namespace lucy
