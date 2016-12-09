#include "IRRenderer.hh"

#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Value.h"
#include "llvm/Transforms/Utils/Cloning.h"

#include <iostream>
#include <vector>

using ::llvm::Value;
using ::llvm::Type;

namespace lucy {

    
IRRenderer::IRRenderer() 
    : context{},
      module(llvm::make_unique<Module>("Lucy JIT", context)),
      builder(llvm::make_unique<IRBuilder<> >(module->getContext())) {}
//    IRRenderer(unique_ptr<Module> ())) {}

IRRenderer::IRRenderer(const IRRenderer& orig)
    : IRRenderer(llvm::CloneModule(orig.module.get())) {}


IRRenderer::IRRenderer(unique_ptr<Module> module)
    : module(std::move(module)),
        builder(unique_ptr<IRBuilder<> >(new IRBuilder<>(this->module->getContext()))) {
    
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

AllocaInst *IRRenderer::getNamedValue(const string& name) {
    return namedValues[name];
}

void IRRenderer::setNamedValue(const string& name, AllocaInst* value) {
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
    
    
    std::cerr << "IR Generator not defined for node type: " << nodeType << std::endl;            
    return nullptr;            
}

Value *IRRenderer::generateIR(BinaryNode* node) {
    Value *left = generateIR(node->lhs);
    Value *right = generateIR(node->rhs);
    
    if (!left || !right)
        return 0;
    
//    Type *llvmIntType = Type::getIntegerType(getLLVMContext());
    
    switch (node->opcode) {
        case '+': return builder->CreateAdd(left, right, "addtmp");
        case '-': return builder->CreateSub(left, right, "subtmp");
        case '*': return builder->CreateMul(left, right, "multmp");
        default : 
            std::cerr << "Unknown Binary Operator: " << node->opcode << std::endl;
            return 0;
    }   
}

Value *IRRenderer::generateIR(NumberNode *node) {
//    Type *llvmIntType = Type::getIntegerType(getLLVMContext());

    return llvm::ConstantInt::get(getLLVMContext(), llvm::APInt(64, node->val));
}


} // namespace lucy