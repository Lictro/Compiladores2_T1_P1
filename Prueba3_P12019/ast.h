#ifndef _AST_H
#define _AST_H

#include <string>
#include <list>

using namespace std;

#define DEFINE_BINARY_EXPR(name) \
	class name##Expr: public BinaryExpr { \
	public:								  \
		name##Expr(Expr *expr1, Expr *expr2): BinaryExpr(expr1, expr2) {} \
		int eval() override; \
	}

class Expr {
public:
	virtual int eval() = 0;
};

class BinaryExpr: public Expr {
protected:
	BinaryExpr(Expr *expr1, Expr *expr2) {
		this->expr1 = expr1;
		this->expr2 = expr2;
	}
public:
	Expr *expr1, *expr2;
};

DEFINE_BINARY_EXPR(Add);
DEFINE_BINARY_EXPR(Sub);
DEFINE_BINARY_EXPR(Mul);
DEFINE_BINARY_EXPR(Div);
DEFINE_BINARY_EXPR(Eq);
DEFINE_BINARY_EXPR(Ne);
DEFINE_BINARY_EXPR(Lt);
DEFINE_BINARY_EXPR(Le);
DEFINE_BINARY_EXPR(Gt);
DEFINE_BINARY_EXPR(Ge);

class NumberExpr: public Expr {
public:
	NumberExpr(int value) {
		this->value = value;
	}

	int eval() {
		return value;
	}
	
	int getValue() { return value; }

private:
	int value;
};

class VarExpr: public Expr {
public:
	VarExpr(const std::string& name): name(name) {}

	int eval();

	std::string name;
};

class Statement {
public:
	virtual void exec() = 0;
};

class AssignStatement: public Statement {
public:
	AssignStatement(const std::string& lhs, Expr *rhs):
		lhs(lhs),
		rhs(rhs) {}

	void exec() override;

	std::string lhs;
	Expr *rhs;
};

class PrintStatement: public Statement {
public:
	PrintStatement(Expr *expr) {
		this->expr = expr;
	}

	void exec();

	Expr *expr;
};

class IfStatement: public Statement {
public:
	IfStatement(Expr *expr, Statement *st_true, Statement *st_false) {
		this->expr = expr;
		this->st_true = st_true;
		this->st_false = st_false;
	}

	void exec();

	Expr *expr;
	Statement *st_true;
	Statement *st_false;
};

class BlockStatement: public Statement {
public:
	BlockStatement() {}

	void addStatement(Statement *statement) {
		statementList.push_back(statement);
	}

	void exec();

	list<Statement*> statementList;
};

#endif
