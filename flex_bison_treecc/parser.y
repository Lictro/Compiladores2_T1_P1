%include {
    #include <assert.h>
    #include <iostream>
    #include "ast.h"

    extern int yylineno;
}

%token_type {ASTNode*}
%default_type {ASTNode*}

%syntax_error {
    std::cout << "Syntax error at line " << yylineno << std::endl;
}

input ::= statement_list(B). {std::cout<< "PARSEO COMPLETADO" << std::endl; ((BlockST*)B)->execute();}

statement_list(A) ::= statement_list(B) statement(C). {A = B; ((BlockST*)A)->list_st.push_back(C);}
statement_list(A) ::= statement(B). {A = new BlockST; ((BlockST *)A)->list_st.push_back(B);}

statement(A) ::= assign(B) SEMICOLON. {A=B;}
statement(A) ::= print(B) SEMICOLON. {A=B;}
statement(A) ::= while(B). {A=B;}
statement(A) ::= if(B). {A=B;}

assign(A) ::= ID(B) OP_ASIGNAR condicion(C). { A = new AssignST(((Iden*)B)->id,(expression*)C);}

print(A) ::= KPRINT OPEN_PAR condicion(B) CLOSE_PAR. { A = new PrintST((expression*)B);}
while(A) ::= KWHILE OPEN_PAR condicion(B) CLOSE_PAR OPEN_CUR statement_list(C) CLOSE_CUR. {A = new WhileST((expression*)B,C);}

if(A) ::= KIF OPEN_PAR condicion(B) CLOSE_PAR OPEN_CUR statement_list(C) CLOSE_CUR opt_else(D). {A = new IfST((expression*)B,C,D);}

opt_else(A) ::= KELSE OPEN_CUR statement_list(B) CLOSE_CUR. {A = B;}
opt_else(A) ::= . {A = nullptr;}

condicion(A) ::= expr(B) OP_MAYOR expr(C). {A = new GreaterExpr((expression*)B,(expression*)C);}
condicion(A) ::= expr(B) OP_MAYOR_IGUAL expr(C). {A = new GreaterEqExpr((expression*)B,(expression*)C);}
condicion(A) ::= expr(B) OP_MENOR expr(C). {A = new LessExpr((expression*)B,(expression*)C);}
condicion(A) ::= expr(B) OP_MENOR_IGUAL expr(C). {A = new LessEqExpr((expression*)B,(expression*)C);}
condicion(A) ::= expr(B) OP_IGUAL expr(C). {A = new EqualExpr((expression*)B,(expression*)C);}
condicion(A) ::= expr(B) OP_DISTINTO expr(C). {A = new DistExpr((expression*)B,(expression*)C);}
condicion(A) ::= expr(B). {A = B;}

expr(A) ::= expr(B) OP_SUM term(C). {A = new AddExpr((expression*)B,(expression*)C);}
expr(A) ::= expr(B) OP_RES term(C). {A = new SubExpr((expression*)B,(expression*)C);}
expr(A) ::= term(B). {A = B;}

term(A) ::= term(B) OP_MUL factor(C). {A = new MulExpr((expression*)B,(expression*)C);}
term(A) ::= term(B) OP_DIV factor(C). {A = new DivExpr((expression*)B,(expression*)C);}
term(A) ::= term(B) OP_MOD factor(C). {A = new ModExpr((expression*)B,(expression*)C);}
term(A) ::= factor(B). {A = B;}

factor(A) ::= NUMBER(B). {A = B; }
factor(A) ::= ID(B). {A = B;}
factor(A) ::= CLOSE_PAR condicion(B) OPEN_PAR. {A = B;}