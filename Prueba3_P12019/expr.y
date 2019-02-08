%code requires {
    #include "ast.h"
}

%{
#include <iostream>

int yylex();

extern int yylineno;
extern char *yyfilename;
int errors;

void yyerror(const char *msg) {
    std::cerr << yylineno << ":" << msg << '\n';
    errors ++;
}

#define YYERROR_VERBOSE 1

%}

%expect 4

%union {
    Statement *statement_t;
    Expr *expr_t;
    char *str_t;
    int int_t;
}

%type <statement_t> statement assign_statement print_statement statement_list
%type <statement_t> if_statement statement_block opt_else
%type <expr_t> expr arith_expr term factor

%token OP_ADD OP_SUB OP_MUL OP_DIV OP_ASSIGN
%token OP_EQ "=="
%token OP_NE "!="
%token OP_LE "<="
%token OP_GE ">="
%token KW_PRINT "print"
%token KW_IF	"if"
%token KW_ELSE	"else"
%token<int_t> TK_NUMBER "number"
%token<str_t> TK_IDENT "identifier"
%token TK_EOL
%token TK_EOF "end of input"
%token TK_ERROR

%%

input: opt_eols statement_list opt_eols {
    if (errors == 0)
        $2->exec();
    else
        fprintf(stderr, "There were errors while parsing the file.\n");
    }
;

statement_list: statement_list statement { $$ = $1; ((BlockStatement *)$$)->addStatement($2); }
               | statement { $$ = new BlockStatement; ((BlockStatement *)$$)->addStatement($1); }
;

eols : eols TK_EOL
      | TK_EOL
;

opt_eols: eols
         |
;

statement : assign_statement eols { $$ = $1; }
           | print_statement eols { $$ = $1; }
           | if_statement	 { $$ = $1; }
;

assign_statement: TK_IDENT OP_ASSIGN expr {
                      $$ = new AssignStatement($1, $3);
                        free($1); 
                  }
;

print_statement: "print" expr { $$ = new PrintStatement($2); }
;

if_statement: "if" '(' expr ')' eols statement_block opt_else {
                    $$ = new IfStatement($3, $6, $7);
                }
;

statement_block : statement				 { $$ = $1; }
                | '{' statement_list '}' eols { $$ = $2; }
;

opt_else: "else" eols statement_block { $$ = $3; }
        | 						 { $$ = NULL; }
;

expr:  arith_expr "==" arith_expr { $$ = new EqExpr($1, $3); }
     | arith_expr "!=" arith_expr { $$ = new NeExpr($1, $3); }
     | arith_expr '<' arith_expr  { $$ = new LtExpr($1, $3); }
     | arith_expr "<=" arith_expr { $$ = new LeExpr($1, $3); }
     | arith_expr '>' arith_expr  { $$ = new GtExpr($1, $3); }
     | arith_expr ">=" arith_expr { $$ = new GeExpr($1, $3); }
     | arith_expr { $$ = $1; }
;

arith_expr :  arith_expr OP_ADD term { $$ = new AddExpr($1, $3); }
      | arith_expr OP_SUB term { $$ = new SubExpr($1, $3); }
      | term { $$ = $1; }
;

term :  term OP_MUL factor { $$ = new MulExpr($1, $3);  }
      | term OP_DIV factor { $$ = new DivExpr($1, $3);  }
      | factor { $$ = $1; }
;

factor: TK_NUMBER { $$ = new NumberExpr($1); }
        | TK_IDENT { $$ = new VarExpr($1); free($1); }
        | '(' arith_expr ')' { $$ = $2; }
;
