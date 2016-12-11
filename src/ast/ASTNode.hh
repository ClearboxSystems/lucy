#pragma once
#include <string>
#include "Type.hh"

namespace lucy {

class ASTNode {
public:
    virtual ~ASTNode();
    virtual std::string toString() = 0;
    virtual std::string getNodeType() = 0;
    virtual PrimitiveType getLucyType() { return undefined; }
    virtual bool typeCheck() { return true; }

    std::string lucyTypeToString(PrimitiveType lucyType);
};

}