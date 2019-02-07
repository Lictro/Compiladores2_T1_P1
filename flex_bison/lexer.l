%option noyywrap
%x blockcomment
%x linecomment
%x exec
%option yylineno

%{
#include <iostream>
#include "parser.tab.h"
using namespace std;

#define YY_DECL int yylex()
%}

digit [0-9]
letter [a-zA-Z]

%%
"/*" BEGIN(blockcomment);
<blockcomment>[^*\n]*        /* eat anything that's not a '*' */
<blockcomment>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
<blockcomment>\n
<blockcomment>"*"+"/" BEGIN(INITIAL);

"//" BEGIN(linecomment);
<linecomment>[^\n]* 
<linecomment>\n BEGIN(INITIAL);

"print" { return KPRINT;} 
"if" { return KIF;} 
"else" { return KELSE;} 
(_|{letter})(_|{letter}|{digit})* { return ID;}
{digit}* { return NUMERO;}
"+" { return SUMA;} 
"-" { return RESTA;} 
"*" { return MULT;} 
"/" { return DIV;}
";" { return SEMICOLON;} 
"(" { return OPENPAR;}
")" { return CLOSEPAR;}
">" { return MAYOR;} 
"<" { return MENOR;} 
">=" { return MAYORIGUAL;} 
"<=" { return MENORIGUAL;}
"==" { return IGUAL;} 
"!=" { return DISTINTO;} 
"{" { return OPENBRA;}
"}" { return CLOSEPAR;}
[\t|\n] { }
. { return ERROR; }
<<EOF>> { return EOFI; }
%%