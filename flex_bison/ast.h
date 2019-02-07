#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <tuple>
#include <math.h>

#define DEFINE_OP_EXPR(name)                                                           \
  class name##Expression : public OPExpression                                               \
  {                                                                                          \
  public:                                                                                    \
    name##Expression(Expression *e1, Expression *e2) : OPExpression(e1, e2) {}               \
    int eval() override;                                                                     \
  }

using namespace std;

class ASTNode;

class ASTNode
{
public:
  ASTNode() {}
  virtual void exec() = 0;
};

class Statement : public ASTNode
{
public:
  Statement() {}
  void exec() = 0;
};

class Expression : public ASTNode
{
public:
  Expression() {}
  int precedence;
  virtual int eval() = 0;
};

class OPExpression : public Expression
{
public:
  Expression *expr1;
  Expression *expr2;
  OPExpression(Expression *expr1, Expression *expr2) : expr1(expr1), expr2(expr2) {}
};

DEFINE_OP_EXPR(Sum);
DEFINE_OP_EXPR(Res);
DEFINE_OP_EXPR(Mul);
DEFINE_OP_EXPR(Mod);
DEFINE_OP_EXPR(Div);
DEFINE_OP_EXPR(Expo);
DEFINE_OP_EXPR(May);
DEFINE_OP_EXPR(MayIg);
DEFINE_OP_EXPR(Men);
DEFINE_OP_EXPR(MenIg);
DEFINE_OP_EXPR(Igual);
DEFINE_OP_EXPR(Dist);

class Number : public Expression
{
private:
  int num;

public:
    Number(int num) : num(num) { precedence = 0; }
    int getNum() { return num; };
    int eval() {
      return num;
    }
};