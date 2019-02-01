#include <cstdio>
#include <iostream>
#include "expr_lexer.h"

/*!max:re2c*/
using namespace std;

int state = 1;

Token ExprLexer::getNextToken() {
    while(1){
        ctx.tok = ctx.cur;
        /*!re2c

        re2c:define:YYCTYPE = char;
        re2c:define:YYCURSOR = ctx.cur;
        re2c:define:YYLIMIT = ctx.lim;
        re2c:define:YYFILL = "if (!ctx.fill(@@)) return Token::Eof;";
        re2c:define:YYFILL:naked = 1;

        lcom = "#";
        o_bcom = "#!";
        c_bcom = "!#"; 
        end = "\x00";
        wsp = [' ']+;
        num = [1-9]*[0-9]+;
        num_real = [1-9]*[0-9]+ ['.'] [0-9]+;
        numero = [num|num_real];
        iden =[_|a-zA-Z][_|a-zA-Z|0-9]*;
        */

        if(state == 1){
            goto exprs;
        }else if(state == 2){
            goto line;
        }else if(state == 3){
            goto block;
        }

        line:
        /*!re2c
        * { continue; }
        end { return makeToken("Eof",3,Token::Eof); }
        "\n" {lineNo++; state = 1; continue; }
        */

        block:
        /*!re2c
        * { continue; }
        wsp { continue; }
        "\n" {lineNo++; continue; }
        end { return makeToken("Eof reached",3,Token::Error); }
        c_bcom {lineNo++; state = 1; continue; }
        */

        exprs:
        /*!re2c
        * { return makeToken("Error",3,Token::Error); }
        wsp { continue; }
        "\n" { lineNo++; continue; }
        lcom { state = 2; continue; }
        o_bcom { state = 3; continue; }
        end { return makeToken("Eof",3,Token::Eof); }
        iden { string t(ctx.tok,ctx.cur-ctx.tok); return makeToken(t.c_str(),t.size(),Token::Id); }
        numero { string t(ctx.tok,ctx.cur-ctx.tok); return makeToken(t.c_str(),t.size(),Token::Num); }
        "+" { return makeToken("+",1,Token::OpAdd); }
        "-" { return makeToken("-",1,Token::OpSub); }
        "*" { return makeToken("*",1,Token::OpMul); }
        "/" { return makeToken("/",1,Token::OpDiv); }
        "(" { return makeToken("(",1,Token::OpenPar); }
        ")" { return makeToken(")",1,Token::ClosePar); }
        ";" { return makeToken(";",1,Token::Semicolon); }
        */
    }
}