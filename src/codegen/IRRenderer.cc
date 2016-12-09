#include "IRRenderer.hh"

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Transforms/Utils/Cloning.h"

#include "llvm/Target/TargetMachine.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Support/TargetSelect.h"

#include <iostream>
#include <vector>

using ::llvm::Value;
using ::llvm::Type;
using ::llvm::BasicBlock;
using ::llvm::Function;
using ::llvm::FunctionType;

namespace lucy {

    
IRRenderer::IRRenderer() 
    : context{},
      module(llvm::make_unique<Module>("Lucy JIT", context)),
      builder(llvm::make_unique<IRBuilder<> >(context)) {
    
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
    jit = llvm::make_unique<llvm::orc::KaleidoscopeJIT>();
    initializeModuleAndPassManager();
}

IRRenderer::IRRenderer(const IRRenderer& orig)
    : IRRenderer(llvm::CloneModule(orig.module.get())) {}


IRRenderer::IRRenderer(unique_ptr<Module> module)
    : module(std::move(module)),
        builder(unique_ptr<IRBuilder<> >(new IRBuilder<>(this->module->getContext()))) {

    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
    jit = llvm::make_unique<llvm::orc::KaleidoscopeJIT>();
    initializeModuleAndPassManager();
    
}

IRRenderer::IRRenderer(IRRenderer&& other) {
    module = std::move(other.module);
    builder = std::move(other.builder);
    
    other.module = nullptr;
    other.builder = nullptr;
}

IRRenderer & IRRenderer::operator =(IRRenderer other) {
    std::swap(module, other.module);
    std::swap(builder, other.builder);
    return *this;
}

IRRenderer::~IRRenderer() {
    builder.reset();
    module.reset();
}

LLVMContext &IRRenderer::getLLVMContext() {
    return module->getContext();
}

Value *IRRenderer::getNamedValue(const string& name) {
    return namedValues[name];
}

void IRRenderer::setNamedValue(const string& name, Value* value) {
    namedValues[name] = value;
}

void IRRenderer::clearNamedValue(const string& name) {
    namedValues.erase(name);
}

void IRRenderer::clearAllNamedValues() {
    namedValues.clear();
}

Value *IRRenderer::generateIR(ASTNode *node) {

    std::string nodeType = node->getType();
    
    if (nodeType == "BinaryNode")
        return generateIR((BinaryNode *)node);
    else if (nodeType == "NumberNode")
        return generateIR((NumberNode *)node);
    else if (nodeType == "SymbolNode")
        return generateIR((SymbolNode *)node);
    else if (nodeType == "CallNode")
        return generateIR((CallNode *)node);
    
    
    std::cerr << "IR Generator not defined for node type: " << nodeType << std::endl;            
    return nullptr;            
}

Value *IRRenderer::generateIR(BinaryNode* node) {
    Value *left = generateIR(node->lhs);
    Value *right = generateIR(node->rhs);
    
    if (!left || !right)
        return 0;
        
    switch (node->opcode) {
        case '+': return builder->CreateAdd(left, right, "addtmp");
        case '-': return builder->CreateSub(left, right, "subtmp");
        case '*': return builder->CreateMul(left, right, "multmp");
        default : 
            std::cerr << "Unknown Binary Operator: " << node->opcode << std::endl;
            return 0;
    }   
}

Value *IRRenderer::generateIR(SymbolNode *node) {
    Value *v = getNamedValue(node->name);
    if (!v)
        std::cerr << "Unknown Variable: " << node->name << std::endl;

    return v;
}

Value *IRRenderer::generateIR(CallNode *node) {
    // Looking up function by name is a mistake!
    Function *callF = getFunction(node->name);
    if (!callF) {
        std::cerr << "Unknown function: " << node->name << std::endl;
        return nullptr;
    }

    if (callF->arg_size() != node->args.size()) {
        std::cerr << "Incorrect # args in " << node->name;
        std::cerr << ", expecting " << callF->arg_size(); 
        std::cerr << " but got " << node->args.size() << std::endl;
        return nullptr;        
    }

    std::vector<Value *> argsV;
    for (unsigned i = 0, e = node->args.size(); i != e; ++i) {
        argsV.push_back(generateIR(node->args[i]));
        if (!argsV.back()) {
            std::cerr << "Failed to generate argument: " << i << std::endl;
            return nullptr;            
        }
    }

    return builder->CreateCall(callF, argsV, "calltmp");
}

Value *IRRenderer::generateIR(NumberNode *node) {
    return llvm::ConstantInt::get(getLLVMContext(), llvm::APInt(64, node->val));
}

Function *IRRenderer::generateIR(FunctionPrototype *proto) {
    std::vector<Type *> ints(proto->args.size(), Type::getInt64Ty(context));
    FunctionType *FT = FunctionType::get(Type::getInt64Ty(context), ints, false);

    Function *F = Function::Create(FT, Function::ExternalLinkage, proto->name, &(*module));

    // Set names for all arguments.
    unsigned idx = 0;
    for (auto &arg : F->args())
        arg.setName(proto->args[idx++]);

    return F;
}

Function *IRRenderer::generateIR(FunctionDef *def) {
    FunctionPrototype *proto = def->proto;
    functionPrototypes[proto->name] = proto;
    Function *func = getFunction(proto->name);

    if (!func)
        return nullptr;

    BasicBlock *BB = BasicBlock::Create(context, "entry", func);
    builder->SetInsertPoint(BB);

    clearAllNamedValues();
    for (auto &arg : func->args())
        setNamedValue(arg.getName(), &arg);

    if (Value *retVal = generateIR(def->body)) {
        builder->CreateRet(retVal);

        verifyFunction(*func);

        func->dump();

        jit->addModule(std::move(module));
        initializeModuleAndPassManager();

        return func;
    }

    func->eraseFromParent();
    return nullptr;
}

void IRRenderer::handleTopLevel(ASTNode *node) {
    std::vector<std::string> args;
    auto proto = new FunctionPrototype("__anon_expr", args);
    auto func = new FunctionDef(proto, node);
    Function *ir = generateIR(func);

    if (ir) {
        auto H = jit->addModule(std::move(module));
        initializeModuleAndPassManager();

        auto topLevelSymbol = jit->findSymbol("__anon_expr");
        assert(topLevelSymbol && "Function not found");

        long (*fp)() = (long (*)())(intptr_t)topLevelSymbol.getAddress();
        std::cout << "Evaluated to " << fp() << std::endl;

        jit->removeModule(H);
    }
}

void IRRenderer::handleExtern(FunctionPrototype *proto) {
    Function *func = generateIR(proto);
    if (func) {
        functionPrototypes[proto->name] = proto;
        func->dump();
    }
}

void IRRenderer::initializeModuleAndPassManager() {
    module = llvm::make_unique<Module>("Lucy JIT", context);
    module->setDataLayout(jit->getTargetMachine().createDataLayout());

    fpm = llvm::make_unique<llvm::legacy::FunctionPassManager>(module.get());

    fpm->add(llvm::createInstructionCombiningPass());
    fpm->add(llvm::createReassociatePass());
    fpm->add(llvm::createGVNPass());
    fpm->add(llvm::createCFGSimplificationPass());
    fpm->doInitialization();

}

llvm::Function *IRRenderer::getFunction(std::string name) {
    if (llvm::Function *func = module->getFunction(name))
        return func;

    auto fi = functionPrototypes.find(name);
    if (fi != functionPrototypes.end())
        return generateIR(fi->second);

    return nullptr;
}



} // namespace lucy