#pragma once

#include "../ast.hh"

#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"

#include <map>
#include <string>
#include <memory>

using ::std::map;
using ::std::string;
using ::std::unique_ptr;

using ::llvm::AllocaInst;
using ::llvm::Function;
using ::llvm::IRBuilder;
using ::llvm::LLVMContext;
using ::llvm::Module;

namespace lucy {
    
class IRRenderer {
private:
    map<string, AllocaInst *> namedValues;

    IRRenderer(const IRRenderer& orig);
    IRRenderer(unique_ptr<Module> module);
    IRRenderer(IRRenderer &&other);
    
    IRRenderer &operator =(IRRenderer other);

    llvm::Value *generateIR(NumberNode *node);
    llvm::Value *generateIR(BinaryNode *node);

public:
    IRRenderer();
    ~IRRenderer();

    unique_ptr<Module> module;
    unique_ptr<IRBuilder<> > builder;

    LLVMContext &getLLVMContext();
    
    AllocaInst *getNamedValue(const string &name);
    void setNamedValue(const string &name, AllocaInst *value);
    void clearNamedValue(const string &name);
    void clearAllNamedValues();
    
    AllocaInst *createEntryBlockAlloca(Function *func, const string &name);
    
    llvm::Value *generateIR(ASTNode *node);
};

} // namespace lucy