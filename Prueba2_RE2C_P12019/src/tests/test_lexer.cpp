#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <sstream>
#include <memory>
#include <cstring>
#include "doctest.h"
#include "expr_lexer.h"

const char *test1 = "45 + 10";
const char *test2 = "_var_1 + _var_2";
const char *test4 = "(0.56 + 1.54) - (10.34 + 333.789);";
const char *test5 = "#Line comment\n"
                    "45 # Line Comment\n"
                    "+ # Line Comment\n"
                    "10 # Line Comment\n"
                    "#";

const char *test6 = "#! Block comment !#\n"
                    "#! Block comment !# 45 #! Block comment !# + #! Block comment !# 10\n";

const char *test7 = "#! Block comment ### \n"
                    " Block comment !!! ### !#45#! Block comment ### \n"
                    " Block comment !!! ### !# + 10#! Block comment ### \n"
                    " Block comment !!! ### !#";

TEST_CASE("Add expr with numbers") {
    std::istringstream in;

    in.str(test1);
    ExprLexer l(in);
    Token tk = l.getNextToken();
    
    CHECK( tk == Token::Num );
    tk = l.getNextToken();
    CHECK( tk == Token::OpAdd );
    tk = l.getNextToken();
    CHECK( tk == Token::Num );
    tk = l.getNextToken();
    CHECK( tk == Token::Eof );
}

TEST_CASE("Add expr with variables") {
    std::istringstream in;

    in.str(test2);
    ExprLexer l(in);
    Token tk = l.getNextToken();

    CHECK( tk == Token::Id );
    tk = l.getNextToken();
    CHECK( tk == Token::OpAdd );
    tk = l.getNextToken();
    CHECK( tk == Token::Id );
    tk = l.getNextToken();
    CHECK( tk == Token::Eof );
}

TEST_CASE("Big buffer") {
    std::istringstream in;
    const int sizeKb = 64;
    int lastPos = sizeKb * 1024 - 1;
    std::unique_ptr<char[]> buff(new char[sizeKb * 1024]);
    char *p = buff.get();

    memset(p, ' ', sizeKb * 1024);
    int pos = lastPos - strlen(test1);
    strcpy(&p[pos], test1);
    p[lastPos] = '\0';

    in.str(p);
    ExprLexer l(in);
    Token tk = l.getNextToken();

    CHECK( tk == Token::Num );
    tk = l.getNextToken();
    CHECK( tk == Token::OpAdd );
    tk = l.getNextToken();
    CHECK( tk == Token::Num );
    tk = l.getNextToken();
    CHECK( tk == Token::Eof );
}

TEST_CASE("Complex expression with real numbers") {
    std::istringstream in;

    in.str(test4);
    ExprLexer l(in);
    Token tk = l.getNextToken();

    CHECK( tk == Token::OpenPar );
    CHECK( l.getText() == "(" );
    tk = l.getNextToken();
    CHECK( tk == Token::Num );
    CHECK( l.getText() == "0.56" );
    tk = l.getNextToken();
    CHECK( tk == Token::OpAdd );
    CHECK( l.getText() == "+" );
    tk = l.getNextToken();
    CHECK( tk == Token::Num );
    CHECK( l.getText() == "1.54" );
    tk = l.getNextToken();
    CHECK( tk == Token::ClosePar );
    CHECK( l.getText() == ")" );
    tk = l.getNextToken();
    CHECK( tk == Token::OpSub );
    CHECK( l.getText() == "-" );

    tk = l.getNextToken();
    CHECK( tk == Token::OpenPar );
    CHECK( l.getText() == "(" );
    tk = l.getNextToken();
    CHECK( tk == Token::Num );
    CHECK( l.getText() == "10.34" );
    tk = l.getNextToken();
    CHECK( tk == Token::OpAdd );
    CHECK( l.getText() == "+" );
    tk = l.getNextToken();
    CHECK( tk == Token::Num );
    CHECK( l.getText() == "333.789" );
    tk = l.getNextToken();
    CHECK( tk == Token::ClosePar );
    CHECK( l.getText() == ")" );
    tk = l.getNextToken();
    CHECK( tk == Token::Semicolon );
    CHECK( l.getText() == ";" );
    tk = l.getNextToken();
    CHECK( tk == Token::Eof );
}

TEST_CASE("Line comments") {
    std::istringstream in;

    in.str(test5);
    ExprLexer l(in);
    Token tk = l.getNextToken();

    CHECK( tk == Token::Num );
    CHECK( l.getText() == "45" );
    tk = l.getNextToken();
    CHECK( tk == Token::OpAdd );
    CHECK( l.getText() == "+" );
    tk = l.getNextToken();
    CHECK( tk == Token::Num );
    CHECK( l.getText() == "10" );
    tk = l.getNextToken();
    CHECK( tk == Token::Eof );
}

TEST_CASE("Block comments 1") {
    std::istringstream in;

    in.str(test6);
    ExprLexer l(in);
    Token tk = l.getNextToken();

    CHECK( tk == Token::Num );
    CHECK( l.getText() == "45" );
    tk = l.getNextToken();
    CHECK( tk == Token::OpAdd );
    CHECK( l.getText() == "+" );
    tk = l.getNextToken();
    CHECK( tk == Token::Num );
    CHECK( l.getText() == "10" );
    tk = l.getNextToken();
    CHECK( tk == Token::Eof );
}

TEST_CASE("Block comments 2") {
    std::istringstream in;

    in.str(test7);
    ExprLexer l(in);
    Token tk = l.getNextToken();

    CHECK( tk == Token::Num );
    CHECK( l.getText() == "45" );
    tk = l.getNextToken();
    CHECK( tk == Token::OpAdd );
    CHECK( l.getText() == "+" );
    tk = l.getNextToken();
    CHECK( tk == Token::Num );
    CHECK( l.getText() == "10" );
    tk = l.getNextToken();
    CHECK( tk == Token::Eof );
}
