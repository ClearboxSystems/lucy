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


} // namespace lucy
