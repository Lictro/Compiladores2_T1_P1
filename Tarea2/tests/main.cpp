#include "stdio.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "parser.cpp"

int main(int argc, char** argv) {
    std::string var;
    std::ifstream infile(argv[1]);
    std::istringstream ins;

    if(argc<2){
        std::cerr << "Uso: ./test filename" << std::endl;
        exit(1);
    }

    if (infile.is_open()) {
        std::string str((std::istreambuf_iterator<char>(infile)),
            std::istreambuf_iterator<char>());
        ins.str(str.c_str());
    } else {
        std::cerr << "Unable to open file" << std::endl;
        exit(1);
    }

    input = &ins;

    parse();

    return 0;
}