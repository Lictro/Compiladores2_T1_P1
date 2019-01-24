#include <iostream>
#include <unordered_map>
#include <string>
#include "lexer.h"

using namespace std;

Token currTkn;
unordered_map<std::string, int> vars;

void parse();
void Input();
void Body();
void Statement();
void PrintST();
void IfElseST(){}
int Expr();
int SingleExpr();
int Term();
int Factor();

void nextToken(){
    currTkn = yylex();
}

void parse()
{
    nextToken();
    Body();
    if (currTkn == Token::Eof)
    {
        cout << "EL PARSER HA SIDO COMPLETADO!!" << endl;
    }
    else
    {
        cout << "ESPERADO [ EOF ] - RECIBIDO [ " << yytext << " ]" << endl;
        exit(1);
    }
}

void Body()
{
    while (currTkn == Token::KPrint || currTkn == Token::KIf)
    {
        Statement();
    }
}

void Statement()
{
    if (currTkn == Token::KPrint)
        PrintST();
    if (currTkn == Token::KIf)
        IfElseST();
}

void PrintST()
{
    int val;
    nextToken();
    val = Expr();
    if (currTkn != Token::Semicolon) {
        cout << "ESPERADO [ ; ] - RECIBIDO [ " << yytext << " ]" << endl;
        exit(1);
    }
    nextToken();
}

int Expr()
{
    int val = SingleExpr();
    if (currTkn == Token::OpMayor)
    {
        nextToken();
        val = val > SingleExpr();
    }
    if (currTkn == Token::OpMayorIgual)
    {
        nextToken();
        val = val >= SingleExpr();
    }
    if (currTkn == Token::OpMenor)
    {
        nextToken();
        val = val < SingleExpr();
    }
    if (currTkn == Token::OpMenorIgual)
    {
        nextToken();
        val = val <= SingleExpr();
    }
    if (currTkn == Token::OpIgual)
    {
        nextToken();
        val = val == SingleExpr();
    }
    if (currTkn == Token::OpDistinto)
    {
        nextToken();
        val = val != SingleExpr();
    }
    return val;
}

int SingleExpr()
{
    int val = Term();
    if (currTkn == Token::OpSum)
    {
        
        nextToken();
        val += SingleExpr();
    }
    if (currTkn == Token::OpRes)
    {
        
        nextToken();
        val -= SingleExpr();
    }
    return val;
}

int Term()
{
    int val =  Factor();
    if (currTkn == Token::OpMul)
    {
        
        nextToken();
        val *= Term();
    }
    if (currTkn == Token::OpDiv)
    {
        
        nextToken();
        val /= Term();
    }
    return val;
}

int Factor()
{
    int val = 0;
    if (Token::Iden == currTkn)
    {
        
        nextToken();
    }
    else if (currTkn == Token::Numero)
    {
        
        val = stoi(yytext);
        nextToken();
    }
    else if (currTkn == Token::OpenPar)
    {
        nextToken();
        val = Expr();
        if (currTkn != Token::ClosePar)
        {
            cout << "ESPERADO [ ) ] - RECIBIDO [ " << yytext << " ]" << endl;
            exit(1);
        }
        nextToken();
    }
    else
    {
        cout << "ESPERADO [ Numero, Id o ( ] - RECIBIDO [ " << yytext << " ]" << endl;
        exit(1);
    }
    return val;
}