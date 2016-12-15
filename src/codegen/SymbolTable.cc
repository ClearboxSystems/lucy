#include "SymbolTable.hh"

#include <iostream>

namespace lucy {

SymbolTable::~SymbolTable() {
    
}
    
SymbolTable *SymbolTable::pushScope(bool allocaBoundry) {
    SymbolTable *symbolTable = new SymbolTable(this, allocaBoundry);
    return symbolTable;    
}

SymbolTable *SymbolTable::popScope() {
    if (!parent) {
        std::cout << "Error: Cannot poop the top level scope!" << std::endl;
        return this;
    }
    
    SymbolTable *ret = parent;
    delete this;
    return ret;
}

Symbol *SymbolTable::getSymbol(const std::string &name, bool traverseParents) {    
    Symbol *symbol = symbols[name];
    if (symbol) return symbol;
    
    if (traverseParents && parent) return parent->getSymbol(name, traverseParents);
    
    return nullptr;
}

bool SymbolTable::addSymbol(Symbol *symbol) {
    if (symbols[symbol->name]) {
        std::cerr << "Error: symbol already defined in current scope: " << symbol->name << std::endl; 
        return false;
    }

    symbols[symbol->name] = symbol;
    return true;
}


bool SymbolTable::storeValue(const std::string &name, llvm::Value *value) {
    Symbol *sym = getSymbol(name, true);
    if (!sym) {
        std::cerr << "Unknown symbol: " << name << std::endl; 
        return false;
    }

    if (sym->value) {
        std::cerr << "Error, symbol: " << name << " has already been assigned to!" << std::endl; 
        return false;        
    }
    
    sym->value = value;
    
    return true;
}    
} // namespace lucy
