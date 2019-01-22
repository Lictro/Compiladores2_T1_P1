#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <sstream>
#include "doctest.h"
#include "tokens.h"

extern char *yytext;
extern std::istream *in;

const char *test = "0xdeadbeef 12345678 0 0b1010 07654 a";

Token yylex();

doctest::String toString(Token tk) {
    switch (tk) {
        case Token::Decimal: return "Decimal";
        case Token::Hex: return "Hex";
        case Token::Binary: return "Binary";
        case Token::Octal: return "Octal";
        case Token::Error: return "Error";
        case Token::Eof: return "Eof";
        default:
            return "Unknown";
    }
}

TEST_CASE("Lexer") {
    std::istringstream ins;

    ins.str(test);

    in = &ins;
    Token tk = yylex();
    std::string text = yytext;
    
    CHECK(tk == Token::Hex);
    CHECK(text == "0xdeadbeef");
    
    tk = yylex();
    text = yytext;
    CHECK(tk == Token::Decimal);
    CHECK(text == "12345678");
    
    tk = yylex();
    text = yytext;
    CHECK(tk == Token::Decimal);
    CHECK(text == "0");
    
    tk = yylex();
    text = yytext;
    CHECK(tk == Token::Binary);
    CHECK(text == "0b1010");
    
    tk = yylex();
    text = yytext;
    CHECK(tk == Token::Octal);
    CHECK(text == "07654");
    
    tk = yylex();
    text = yytext;
    CHECK(tk == Token::Error);
    CHECK(text == "a");
    
    tk = yylex();
    CHECK(tk == Token::Eof);
}
