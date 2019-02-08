#include <iostream>
#include <unordered_map>
#include <string>
#include "ast.h"

std::unordered_map<std::string, int> vars;

#define IMPLEMENT_BINARY_EXPR_EVAL(name, op) \
	int name##Expr::eval() {	\
		int v1 = expr1->eval();	\
		int v2 = expr2->eval();	\
								\
		return v1 op v2;		\
	}

IMPLEMENT_BINARY_EXPR_EVAL(Add, +);
IMPLEMENT_BINARY_EXPR_EVAL(Sub, -);
IMPLEMENT_BINARY_EXPR_EVAL(Mul, *);
IMPLEMENT_BINARY_EXPR_EVAL(Div, /);
IMPLEMENT_BINARY_EXPR_EVAL(Eq, ==);
IMPLEMENT_BINARY_EXPR_EVAL(Ne, !=);
IMPLEMENT_BINARY_EXPR_EVAL(Lt, <);
IMPLEMENT_BINARY_EXPR_EVAL(Le, <=);
IMPLEMENT_BINARY_EXPR_EVAL(Gt, >);
IMPLEMENT_BINARY_EXPR_EVAL(Ge, >=)

int VarExpr::eval() {
	return vars[name];
}

// Statement exec methods

void AssignStatement::exec() {
	int rvalue = rhs->eval();

	vars[lhs] = rvalue;
}

void PrintStatement::exec() {
	int value = expr->eval();
	std::cout << value << '\n';
}

void IfStatement::exec() {
	if (expr->eval()) {
		st_true->exec();
	} else {
		if (st_false != nullptr) {
			st_false->exec();
		}
	}
}

void BlockStatement::exec() {
	for (auto st : statementList) {
		st->exec();
	}
}
