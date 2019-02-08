%{
    #include <cstdio>
    #include <iostream>
    #include <vector>
    #include <unordered_map>
    #include "parser.tab.h"

    using namespace std;
    // Declare stuff from Flex that Bison needs to know about:
    extern int yylex();
    extern char*yytext;
    extern int yyparse();
    extern string curriden;
    extern FILE *yyin;
    
    #define YYERROR_VERBOSE 1
    
    void yyerror(const char *s);
    BlockST* b = new BlockST();
%}

%code requires{
#include "ast.h"
}

%token EOL
%token ERROR
%token MAYOR
%token MENOR
%token MAYORIGUAL
%token MENORIGUAL
%token IGUAL
%token DISTINTO
%token ASIGNAR
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

%nonassoc CLOSEPAR
%nonassoc KELSE
%expect 6

%%
program:
    eolsep block { b->exec(); };
    
block:
    stmtlist { };

stmtlist: 
    stmtlist stmt { ($$) }
    |stmt { vector<ASTNode*> temp; temp.push_back((ASTNode*)$1); $$ = new };

stmt:
    ID ASIGNAR binop eols { $$ = new AsignST(curriden,$3); }
    |KPRINT OPENPAR binop CLOSEPAR eols {$$ = new PrintST($3);}
    |KIF OPENPAR binop CLOSEPAR eols stmtlist {$$ = new IfST($3, nullptr, nullptr);}
    |KIF OPENPAR binop CLOSEPAR eols stmtlist KELSE eols stmtlist {$$ = new IfST($3, nullptr, nullptr);};
    
eols: 
    eols EOL
    |EOL;
    
eolsep: 
    eols EOL
    |EOL 
    |;
    
binop:
    aritexpr MAYOR aritexpr { $$ = new MayExpression($1,$3); }
    |aritexpr MAYORIGUAL aritexpr { $$ = new MayIgExpression($1,$3); }
    |aritexpr MENOR aritexpr { $$ = new MenExpression($1,$3); }
    |aritexpr MENORIGUAL aritexpr { $$ = new MenIgExpression($1,$3); }
    |aritexpr IGUAL aritexpr { $$ = new IgualExpression($1,$3); }
    |aritexpr DISTINTO aritexpr { $$ = new DistExpression($1,$3); }
    |aritexpr { $$ = $1; };

aritexpr:
    term SUMA aritexpr  { $$ = new SumExpression($1,$3); }
    |term RESTA aritexpr  { $$ = new ResExpression($1,$3); }
    |term { $$ = $1; };

term:
    term MULT factor { $$ = new MulExpression($1,$3); }
    |term DIV factor { $$ = new DivExpression($1,$3); }
    |factor { $$ = $1; };

factor:
    NUMERO { $$ = new Number(atoi(yytext)); }
    |ID { $$ = new Iden(string(yytext)); }
    |OPENPAR binop CLOSEPAR { $$ = $2; }
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
