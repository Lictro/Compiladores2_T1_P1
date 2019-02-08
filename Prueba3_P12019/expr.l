%option noyywrap
%option yylineno
%x comment

%{
#include <cstdio>
#include <iostream>
#include <fstream>
#include "expr_tokens.h"

std::ifstream in;

#define YY_INPUT(buf, result, max_size) \
    do { \
        in.read(reinterpret_cast<char *>(buf), max_size); \
        result = in.gcount(); \
    } while (0)
    
#define YY_DECL int yylex()

void yyerror(const char *msg);
%}

%%
[ \t]   { /* Nada */ }
"/*"    { BEGIN(comment); }
"//".*\n { return TK_EOL; }
"\n"	 { return TK_EOL; }
"+"		{ return OP_ADD; }
"-"		{ return OP_SUB; }
"*"		{ return OP_MUL; }
"/"		{ return OP_DIV; }
"("		{ return '('; }
")"		{ return ')'; }
"="		{ return OP_ASSIGN; }
"=="	{ return OP_EQ; }
"!="	{ return OP_NE; }
"<"		{ return '<'; }
">"		{ return '>'; }
"<="	{ return OP_LE; }
">="	{ return OP_GE; }
"if"	{ return KW_IF; }
"{"		{ return '{'; }
"}"		{ return '}'; }
"else"  { return KW_ELSE; }
"print" { return KW_PRINT; }
[a-zA-Z_][a-zA-Z_0-9]* { yylval.str_t = strdup(yytext); return TK_IDENT; }
[0-9]+	{ yylval.int_t = atoi(yytext); return TK_NUMBER; }
.		{ printf("0x%02x '%c' invalid character\n", (int)yytext[0], yytext[0]); return TK_ERROR; }

<comment>"*/" { BEGIN(INITIAL); }
<comment>.|\n { /* Nothing */ }
<comment><<EOF>> { yyerror("Block comment without end."); return 0; }

%%
