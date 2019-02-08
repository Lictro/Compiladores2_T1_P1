%option noyywrap
%x blockcomment
%x linecomment
%option yylineno

%{
#include <iostream>
#include "parser.tab.h"

using namespace std;

string curriden;
%}

digit [0-9]
letter [a-zA-Z]

%%
"\n" { return EOL;}
"print" { return KPRINT;} 
"if" { return KIF;} 
"else" { return KELSE;} 
(_|{letter})(_|{letter}|{digit})* { curriden = string(yytext); return ID;}
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
"=" { return ASIGNAR;}
"!=" { return DISTINTO;} 
"{" { return OPENBRA;}
"}" { return CLOSEPAR;}
[" "|\t|\r|\f] { return yylex(); }
. { return ERROR; }
%%
