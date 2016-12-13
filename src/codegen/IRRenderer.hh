#pragma once

#include "../ast.hh"

#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/LegacyPassManager.h"

#include "../../include/KaleidoscopeJIT.h"

#include <map>
#include <string>
#include <memory>

using ::std::map;
using ::std::string;
using ::std::unique_ptr;

using ::llvm::AllocaInst;
using ::llvm::Value;
using ::llvm::Function;
using ::llvm::IRBuilder;
using ::llvm::LLVMContext;
using ::llvm::Module;
using ::llvm::legacy::FunctionPassManager;

namespace lucy {
    
class IRRenderer {
private:
    map<string, Value *> namedValues;
    map<string, FunctionPrototype *> functionPrototypes;
    map<string, Value *> globalVariables;

    IRRenderer(const IRRenderer& orig);
    IRRenderer(unique_ptr<Module> module);
    IRRenderer(IRRenderer &&other);
    
    IRRenderer &operator =(IRRenderer other);

    llvm::Value *generateIR(IntegerNode *node);
    llvm::Value *generateIR(FloatNode *node);
    llvm::Value *generateIR(SymbolNode *node);
    llvm::Value *generateIR(BinaryNode *node);
    llvm::Value *generateIR(CallNode *node);
    llvm::Value *generateIR(CastNode *node);
    llvm::Function *generateIR(FunctionPrototype *proto);

    unique_ptr<llvm::orc::KaleidoscopeJIT> jit;
    unique_ptr<FunctionPassManager> fpm;

    void initializeModuleAndPassManager();

    llvm::Function *getFunction(std::string name);

public:
    IRRenderer();
    ~IRRenderer();

    LLVMContext context;
    unique_ptr<Module> module;
    unique_ptr<IRBuilder<> > builder;

    LLVMContext &getLLVMContext();
    
    Value *getNamedValue(const string &name);
    void setNamedValue(const string &name, Value *value);
    void clearNamedValue(const string &name);
    void clearAllNamedValues();
    
    AllocaInst *createEntryBlockAlloca(Function *func, const string &name);
    
    llvm::Value *generateIR(ASTNode *node);
    llvm::Function *generateIR(FunctionDef *definition);
    void handleTopLevel(ASTNode *node);
    void handleExtern(FunctionPrototype *node);
};

} // namespace lucy
