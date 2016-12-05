#include "tree.hpp"

#include "bison_parser.hpp"

#include <memory>



STree::STree() : root(nullptr) {}

STree::STree(STree &&other) {
    root = std::move(other.root);
    other.root = nullptr;
}

STree &
STree::operator =(STree other) {
    std::swap(root, other.root);
    return *this;
}

STree::~STree() {
    root.reset();
}

void
STree::parse(std::istream &input) {
    root.release();

    bison::Parser *parser = new bison::Parser(*this);
    parser->parse();
}


void
STree::set_root(ASTNode *node) {
    root = std::unique_ptr<ASTNode>(node);
}

//void
//STree::set_root(FunctionNode *node) {
//    root = std::unique_ptr<ASTNode>(node);
//}
//
//void
//STree::set_root(PrototypeNode *node) {
//    root = std::unique_ptr<ASTNode>(node);
//}
