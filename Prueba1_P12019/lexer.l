%option noyywrap
%option yylineno

%{
#include <iostream>
#include "tokens.h"

std::istream *in;

#define YY_DECL Token yylex()

#define YY_INPUT(buf,result,max_size) \
    do { \
        in->read(reinterpret_cast<char *>(buf), max_size); \
        result = in->gcount(); \
    } while (0)

%}

digit [0-9]
hex [a-fA-F]
bin [0-1]
octal [0-7]
start [1-9]
letter [a-zA-Z]

%%
0|{start}{digit}* { return Token::Decimal; }
0{octal}* { return Token::Octal; }
0x({digit}|{hex})* { return Token::Hex; }
0b({bin})* { return Token::Binary; }
<<EOF>> return Token::Eof;
{letter}* { return Token::Error; }
%%
