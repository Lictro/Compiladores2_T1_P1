%option noyywrap
%x blockcomment
%x linecomment
%option yylineno

%{
#include <iostream>
#include "tokens.h"

#define ERROR -1

using namespace std;

string curriden;
%}

digit [0-9]
letter [a-zA-Z]

%%
"print" { return KPRINT;} 
"if" { return KIF;} 
"else" { return KELSE;} 
"while" { return KWHILE; }
(_|{letter})(_|{letter}|{digit})* { curriden = string(yytext); return ID;}
{digit}+ { curriden = string(yytext); return NUMBER;}
"+" { return OP_SUM;} 
"-" { return OP_RES;} 
"*" { return OP_MUL;} 
"/" { return OP_DIV;}
";" { return SEMICOLON;} 
"(" { return OPEN_PAR;}
")" { return CLOSE_PAR;}
">" { return OP_MAYOR;} 
"<" { return OP_MENOR;} 
">=" { return OP_MAYOR_IGUAL;} 
"<=" { return OP_MENOR_IGUAL;}
"==" { return OP_IGUAL;}
"=" { return OP_ASIGNAR;}
"!=" { return OP_DISTINTO;} 
"{" { return OPEN_CUR;}
"}" { return CLOSE_CUR;}
[" "|\t|\r|\f|\n] { return yylex(); }
. { return ERROR; }
%%