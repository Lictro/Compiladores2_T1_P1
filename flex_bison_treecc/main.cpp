#include <iostream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "build/tokens.h"

#define EOFI 0

extern int yylex();
extern char* yytext;
extern FILE *yyin;
extern std::string curriden;

void *ParseAlloc(void *(*mallocProc)(size_t));
void Parse(void *yyp,int yymajor,ASTNode* yyminor);
void ParseFree( void *p, void (*freeProc)(void *));

void parse() {
    void *parser = ParseAlloc(malloc);
    int tk = yylex();
    while (tk != EOFI) {
        if (tk == NUMBER) {
            Parse(parser, tk, new Number(std::stoi(curriden)));
        }else if(tk == ID){
            Parse(parser, tk, new Iden(curriden));
        }else{
            Parse(parser, tk, NULL);
        } 
        tk = yylex();
    }
    Parse(parser, 0, nullptr);
    ParseFree(parser, free);
}

int main(int argc, char** argv)
{
    FILE *myfile = fopen(argv[1], "r");
    // make sure it is valid:
    if (!myfile) {
        std::cout << "I can't open a.snazzle.file!" << std::endl;
        return -1;
    }
    // Set flex to read from it instead of defaulting to STDIN:
    yyin = myfile;

    parse();

    return 0;
}