#include "parser/tree.hpp"
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char **argv) {
    void *l_val;
    
    STree *tree = new STree();
    
    std::string input;
    fprintf(stderr, "ready> ");
    while (std::getline(std::cin, input, ';')) {
        std::istringstream iss(input);

        tree->parse(iss);
        fprintf(stderr, "ready> ");
    }
    
    return 0;
}