#include <iostream>
#include <unordered_map>
#include "Tokens.h"

extern Token yylex();
extern char* yytext;
extern int yylineno;
extern FILE* yyin;

Token currTkn;
std::unordered_map<std::string, int> vars;

void parse();
int input();
int expr();
int term();
int factor();

/**
 * INPUT -> (Expr ;)*
 * Expr -> Term (+ / - Term)
 * Term -> Factor (* / / Factor)
 * Factor -> (Expr) | Num | Ident
**/ 

void parse() {
    int result;

    do {
        currTkn = yylex();
        result = input();
        std::cout << result << std::endl;
    } while (currTkn != Token::Eof);

    std::cout << "File parsed successfully" << std::endl;
}

int input() {
    int val = expr();

    if (currTkn == Token::Semicolon) {
        return val;
    } else {
        std::cout << "Error expected ; Line" << yylineno <<std::endl;
        exit(1);
    }
}

int expr() {
    int val = term();

    while (currTkn == Token::OpSum || currTkn == Token::OpRes) {
        if (currTkn == Token::OpSum) {
            currTkn = yylex();
            val = val + term();
        } else {
            currTkn = yylex();
            val = val - term();
        }
    }

    return val;
}

int term() {
    int val = factor();

    while (currTkn == Token::OpMul || currTkn == Token::OpDiv) {
        if (currTkn == Token::OpMul) {
            currTkn = yylex();
            val = val * factor();
        } else {
            currTkn = yylex();
            val = val / factor();
        }
    }

    return val;
}

int factor() {
    int val;

    if (currTkn == Token::Iden || currTkn == Token::Numero) {
        val = std::stoi(yytext);
        currTkn = yylex();
        return val;
    } else if (currTkn == Token::OpenPar) {
        currTkn = yylex();
        val = expr();

        if (currTkn == Token::ClosePar) {
            currTkn = yylex();
            return val;
        } else {
            std::cout << "Error expected ')', Line" << yylineno <<std::endl;
        exit(1);
        }
    } else {
        std::cout << "Error expected Expression but found, Line" << yylineno <<std::endl;
        exit(1);
    }
    return -1;
}

int main(int argc, char** argv) {
    FILE *in;
    std::string var;

    if (argc > 0 && (in = fopen(argv[1], "r"))) {
        yyin = in;
    } else {
        std::cerr << "Unable to open file" << std::endl;
        exit(1);
    }

    // for (int i = 2; i < argc; i++) {
    //     var = argv[i];

    //     if (var[0] == '-' && var[1] == 'D') {

    //     }
    // }

    
    try
    {
         parse();
    }
    catch(const char* msg)
    {
        std::cerr << msg << '\n';
    }
    
    return 0;
}