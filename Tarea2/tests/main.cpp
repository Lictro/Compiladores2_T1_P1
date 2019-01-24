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
        std::cerr << "Uso: ./test filename [-Dvar=10]" << std::endl;
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

    if(argc>2){
        for(int i = 2; i < argc; i++)
        {
            if(argv[i][0]=='-' && argv[i][1]=='D'){
                auto asignar = mysplitFn(argv[i],"-D");
                auto par = mysplitFn(asignar[0],"=");
                if(par.size()==2){
                    vars.insert(make_pair(par[0],stoi(par[1])));
                }
            }
        }
    }
    
    parse();

    return 0;
}