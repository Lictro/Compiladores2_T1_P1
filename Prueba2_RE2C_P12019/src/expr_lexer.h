#ifndef _EXPR_LEXER_H
#define _EXPR_LEXER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

static const size_t SIZE = 1024;
static const size_t YYMAXFILL = 100;

enum class Token {
    Num         = 100,
    Id          = 101,
    OpAdd       = 102,
    OpSub       = 103,
    OpMul       = 104,
    OpenPar     = 105,
    ClosePar    = 106,
    OpDiv       = 107,
    Semicolon   = 108,
    Error       = 998,
    Eof         = 999,
};

/*
<--- discarded -->                              <----- n ----->
oxxxxxxxxxxxxxxxxxo----------o-----------------o--------o.....o..........o... (more input)
buffer          lexeme    YYMARKER          YYCURSOR YYLIMIT *          *
|             *          *                 *            | *          *
|          *          *                 *              *|         *
|       *          *                 *              *   |      *
|    *          *                 *              *      |   *
| *          *                 *              *         |*
o-----------o-----------------o--------------o----------o
buffer,  YYMARKER          YYCURSOR                  YYLIMIT
*/

class ExprLexer {
public:
    ExprLexer(std::istream &in): ctx(in) {}
    ~ExprLexer();

    Token getNextToken();
    int getLineNo() { return lineNo; }
    std::string getText() { return text; }

private:
    struct Context {
        char *buf;
        char *lim;
        char *cur;
        char *tok;
        bool eof;

        Context(std::istream &in)
            : buf()
            , lim(buf + SIZE)
            , cur(lim)
            , tok(lim)
            , eof(false)
        {
            std::ostringstream oss;
            oss << in.rdbuf();
            std::string strConst = oss.str();
            buf = (char *)strConst.c_str();
        }

        bool fill(size_t need)
        {
            if (eof) {
                return false;
            }
            const size_t free = tok - buf;
            if (free < need) {
                return false;
            }
            memmove(buf, tok, lim - tok);
            lim -= free;
            cur -= free;
            tok -= free;
            lim += fread(lim, 1, free, stdin);
            if (lim < buf + SIZE) {
                eof = true;
                memset(lim, 0, YYMAXFILL);
                lim += YYMAXFILL;
            }
            return true;
        }
    };

    Token makeToken(const char *txt, int len, Token tk) {
        std::string tt(txt, len);
        text = std::move(tt);

        return tk;
    }

private:
    int lineNo;
    Context ctx;
    std::string text;
};
#endif
