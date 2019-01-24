%option noyywrap
%x blockcomment
%x linecomment
%x exec

%{
#include "stdio.h"
#include "Tokens.h"

std::istream *input;

#define YY_DECL Token yylex()

#define YY_INPUT(buf,result,max_size) \
    do { \
        input->read(reinterpret_cast<char *>(buf), max_size); \
        result = input->gcount(); \
    } while (0)

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
<exec>"print" { return Token::KPrint; } 
<exec>"if" { return Token::KIf; } 
<exec>"else" { return Token::KElse; } 
<exec>(_|{letter})(_|{letter}|{digit})* { return Token::Iden; }
<exec>{digit}* { return Token::Numero; }
<exec>"+" { return Token::OpSum; } 
<exec>"-" { return Token::OpRes; } 
<exec>"*" { return Token::OpMul; } 
<exec>"/" { return Token::OpDiv; }
<exec>";" { return Token::Semicolon; } 
<exec>"(" { return Token::OpenPar; }
<exec>")" { return Token::ClosePar; }
<exec>">" { return Token::OpMayor; } 
<exec>"<" { return Token::OpMenor; } 
<exec>">=" { return Token::OpMayorIgual; } 
<exec>"<=" { return Token::OpMenorIgual; }
<exec>"=" { return Token::OpIgual; } 
<exec>"!=" { return Token::OpDistinto; } 
<exec>"{" { return Token::OpenBra; }
<exec>"}" { return Token::CloseBra; }
<exec>"%>" BEGIN(INITIAL);
<exec>[\n|\t] { }
<<EOF>> { return Token::Eof; }

. std::cout << yytext;
%%