#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "expr_ast.h"

TEST_CASE("Simple expression") {
    ASTNode *e = new AddExpr(new NumExpr(10), new NumExpr(20));
    
    CHECK(e->toString() == "(10)+(20)");
}

TEST_CASE("Add expression") {
    ASTNode *e = new AddExpr(new NumExpr(10), new NumExpr(20));
    
    CHECK(e->toString() == "(10)+(20)");
}

TEST_CASE("Sub expression") {
    ASTNode *e = new SubExpr(new NumExpr(10), new NumExpr(20));
    
    CHECK(e->toString() == "(10)-(20)");
}

TEST_CASE("Mult expression") {
    ASTNode *e = new MulExpr(new NumExpr(10), new NumExpr(20));
    
    CHECK(e->toString() == "(10)*(20)");
}

TEST_CASE("Div expression") {
    ASTNode *e = new DivExpr(new NumExpr(10), new NumExpr(20));
    
    CHECK(e->toString() == "(10)/(20)");
}

TEST_CASE("Mod expression") {
    ASTNode *e = new ModExpr(new NumExpr(10), new NumExpr(20));
    
    CHECK(e->toString() == "(10)%(20)");
}

TEST_CASE("Combined expression (Add/Sub)") {
    ASTNode *e = new MulExpr(
                             new AddExpr(new NumExpr(10), new NumExpr(20)),
                             new SubExpr(new NumExpr(567), new NumExpr(560))
                            );
    
    CHECK(e->toString() == "((10)+(20))*((567)-(560))");
}

TEST_CASE("Combined expression (Div/Mod)") {
    ASTNode *e = new ModExpr(
                             new DivExpr(
                                          new AddExpr(new NumExpr(10), new NumExpr(20)),
                                          new NumExpr(5)
                                        ),
                             new NumExpr(13)
                            );
    
    CHECK(e->toString() == "(((10)+(20))/(5))%(13)");
}