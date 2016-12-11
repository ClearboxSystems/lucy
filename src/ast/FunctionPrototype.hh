#pragma once

#include <vector>
#include <string>

namespace lucy {

class FunctionPrototype {

public:
    FunctionPrototype(const std::string &name, std::vector<std::string> &args);
    std::string toString();
    std::string getNodeType() { return "FunctionPrototype"; }

    std::string name;
    std::vector<std::string> args;
};

} // namespace lucy
