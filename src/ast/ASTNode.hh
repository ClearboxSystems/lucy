#pragma once
#include <string>

namespace lucy {

class ASTNode {
public:
    virtual ~ASTNode();
    virtual std::string toString() = 0;
    virtual std::string getType() = 0;
};

}