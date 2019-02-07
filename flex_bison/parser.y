%{
requieres
    #include <cstdio>
    #include <iostream>
    #include "parse.tab.h";

    using namespace std;
    // Declare stuff from Flex that Bison needs to know about:
    extern int yylex();
    extern int yyparse();
    extern FILE *yyin;
    
    void yyerror(const char *s);

    typedef ASTNode* YYSTYPE;
    typedef uint16_t char16_t;
%}

%code requiere

%token EOFI
%token EOLI
%token ERROR
%token MAYOR
%token MENOR
%token MAYORIGUAL
%token MENORIGUAL
%token IGUAL
%token DISTINTO
%token SUMA
%token RESTA
%token MULT
%token DIV
%token SEMICOLON
%token OPENPAR
%token CLOSEPAR
%token OPENBRA
%token CLOSEBRA
%token NUMERO
%token KPRINT
%token KIF
%token KELSE
%token ID

%%
binexpr:
    singlexpr MAYOR singlexpr {}
    | singlexpr MENOR singlexpr {}
    | singlexpr MAYORIGUAL singlexpr {}
    | singlexpr MENORIGUAL singlexpr {}
    | singlexpr IGUAL singlexpr {}
    | singlexpr DISTINTO singlexpr {}
    | singlexpr {}
    ;

singlexpr:
    term SUMA singlexpr {}
    | term RESTA singlexpr {}
    | term {}
    ;

term:
    factor MULT term {}
    | factor DIV term {}
    | factor {}
    ;

factor:
    NUMERO {}
    | ID {}
    | OPENPAR binexpr CLOSEPAR {}
    ;
%%

int main(int argc, char** argv) {
  // open a file handle to a particular file:
  FILE *myfile = fopen(argv[1], "r");
  // make sure it is valid:
  if (!myfile) {
    cout << "I can't open a.snazzle.file!" << endl;
    return -1;
  }
  // Set flex to read from it instead of defaulting to STDIN:
  yyin = myfile;
  // Parse through the input:
  yyparse();
}

void yyerror(const char *s) {
  cout << "EEK, parse error!  Message: " << s << endl;
  // might as well halt now:
  exit(-1);
}