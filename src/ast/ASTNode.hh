#pragma once
#include <string>

namespace lucy {

enum PrimitiveType {
    undefined,
    Integer,
    Float
};    
    
struct LucyType;
class ASTNode {
public:
    ASTNode(LucyType *lucyType = nullptr) : lucyType(lucyType) {}
    virtual ~ASTNode();
    virtual std::string toString() = 0;
    virtual std::string getNodeType() = 0;
    virtual struct LucyType *getLucyType() { return lucyType; }

    std::string lucyTypeToString(struct LucyType *lucyType);
    
    struct LucyType *lucyType = nullptr;
};

}