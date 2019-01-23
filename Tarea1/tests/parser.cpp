#include <iostream>
#include <unordered_map>
#include <string>
#include "lexer.h"

using namespace std;

Token currTkn;
unordered_map<std::string, int> vars;

void parse();
void S();
int E();
int T();
int F();

void nextToken(){
    currTkn = yylex();
}

void parse()
{
    nextToken();
    S();
    if (currTkn == Token::Eof)
    {
        printf("EL PARSER HA SIDO COMPLETADO!!\n");
    }
    else
    {
        cout << "ESPERADO [ EOF ] - RECIBIDO [ " << yytext << " ]" << endl;
        exit(1);
    }
}

void S()
{
    int val = E();
    if (currTkn == Token::Semicolon)
    {
        nextToken();
        cout << " = " << val << endl;
    }
    else
    {
        cout << "ESPERADO [ ; ] - RECIBIDO [ " << yytext << " ]" << endl;
        exit(1);
    }
    if (currTkn != Token::Eof)
        S();
}

int E()
{
    int val = T();
    if (currTkn == Token::OpSum)
    {
        cout << yytext;
        nextToken();
        val += T();
    }
    if (currTkn == Token::OpRes)
    {
        cout << yytext;
        nextToken();
        val -= T();
    }
    return val;
}

int T()
{
    int val =  F();
    if (currTkn == Token::OpMul)
    {
        cout << yytext;
        nextToken();
        val *= T();
    }
    if (currTkn == Token::OpDiv)
    {
        cout << yytext;
        nextToken();
        val /= T();
    }
    return val;
}

int F()
{
    int val = 0;
    if (Token::Iden == currTkn)
    {
        cout << yytext;
        nextToken();
    }
    else if (currTkn == Token::Numero)
    {
        cout << yytext;
        val = stoi(yytext);
        nextToken();
    }
    else if (currTkn == Token::OpenPar)
    {
        cout << yytext;
        nextToken();
        val = E();
        if (currTkn != Token::ClosePar)
        {
            cout << "ESPERADO [ ) ] - RECIBIDO [ " << yytext << " ]" << endl;
            exit(1);
        }
        cout << yytext;
        nextToken();
    }
    else
    {
        cout << "ESPERADO [ Numero, Id o ( ] - RECIBIDO [ " << yytext << " ]" << endl;
        exit(1);
    }
    return val;
}