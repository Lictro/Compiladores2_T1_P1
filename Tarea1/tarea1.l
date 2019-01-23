%option noyywrap
%x blockcomment
%x linecomment
%x exec

%{
#include "stdio.h"
#include "Tokens.h"

#define YY_DECL Token yylex()

int flag;
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

"<%" BEGIN(exec);
<exec>(_|{letter})(_|{letter}|{digit})* { printf(yytext); return Token::Iden; }
<exec>{digit}* { printf(yytext); return Token::Numero; }
<exec>"+" { printf(yytext); return Token::OpSum; } 
<exec>"-" { printf(yytext); return Token::OpRes; } 
<exec>"*" { printf(yytext); return Token::OpMul; } 
<exec>"/" { printf(yytext); return Token::OpDiv; }
<exec>";" { printf(yytext); return Token::Semicolon; } 
<exec>"(" { printf(yytext); return Token::OpenPar; }
<exec>")" { printf(yytext); return Token::ClosePar; }
<exec>"%>" BEGIN(INITIAL);
<exec>[\n|\t] { }
<<EOF>> { return Token::Eof;}

.|\n printf(yytext);
%%