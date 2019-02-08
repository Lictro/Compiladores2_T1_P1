#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <math.h>
#include <unordered_map>

#define DEFINE_OP_EXPR(name)                                                           \
  class name##Expression : public OPExpression                                              \
  {                                                                                         \
  public:                                                                                   \
    name##Expression(ASTNode *e1, ASTNode *e2) : OPExpression(e1, e2) {}              \
    int eval() override;                                                                    \
}

using namespace std;

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

class AsignST : public Statement
{
public:
  string LValue;
  ASTNode* RValue;
  AsignST(string LValue, ASTNode *RValue) : RValue(RValue), LValue(LValue) {}
  void exec();
};

class PrintST : public Statement
{
public:
  ASTNode* expr;
  PrintST(ASTNode* expr) : expr(expr) {}
  void exec();
};

class BlockST : public Statement
{
public:
  vector<ASTNode*> stmts;
  BlockST(vector<ASTNode*> stmts) : stmts(stmts) {}
  void exec();
};

class IfST : public Statement
{
public:
  ASTNode* cond; ASTNode* tblock; ASTNode* fblock;
  IfST(ASTNode* cond, ASTNode* tblock, ASTNode* fblock) : cond(cond), tblock(tblock), fblock(fblock)  {}
  void exec();
};


class Expression : public ASTNode
{
public:
  Expression() {}
  virtual int eval() = 0;
  void exec(){}
};

class OPExpression : public Expression
{
public:
  ASTNode*expr1;
  ASTNode*expr2;
  OPExpression(ASTNode*expr1, ASTNode*expr2) : expr1(expr1), expr2(expr2) {}
};

DEFINE_OP_EXPR(Sum);
DEFINE_OP_EXPR(Res);
DEFINE_OP_EXPR(Mul);
DEFINE_OP_EXPR(Div);
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
    Number(int num) : num(num) { }
    int eval() {
      return num;
    }
};

class Iden : public Expression
{
private:
  string id;

public:
    Iden(string id) : id(id) { }
    int eval();
};

typedef ASTNode* YYSTYPE;
#define YYSTYPE_IS_DECLARED 1
