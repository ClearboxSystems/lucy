#pragma once

#include <memory>
#include "../ast.hpp"
#include "bison_parser.hpp"


class STree {
    STree(STree &&other);
    STree &operator =(STree other);

public:
    STree();
    ~STree();

    std::unique_ptr<ASTNode> root;

    void parse(std::istream &input);

    void set_root(ASTNode *node);
//    void set_root(FunctionNode *node);
//    void set_root(PrototypeNode *node);
};


