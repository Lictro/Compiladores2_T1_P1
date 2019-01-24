#include <iostream>
#include <unordered_map>
#include <string>
#include <stack>
#include <vector>
#include "lexer.h"

using namespace std;

Token currTkn;
unordered_map<std::string, int> vars;

vector<string> mysplitFn(string str, string delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos)
            pos = str.length();
        string token = str.substr(prev, pos - prev);
        if (!token.empty())
            tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

void parse();
void Input();
void Body();
void Statement();
void PrintST();
void IfElseST();
int Expr();
int SingleExpr();
int Term();
int Factor();

void nextToken(){
    currTkn = yylex();
}

void parse()
{
    execution.push(1);
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
    if(execution.top() == 1)
        cout << val << endl;
    nextToken();
}

void IfElseST(){
    int val;
    int able = 0;
    if(execution.top() == 1){
        able = 1;    
    }
    nextToken();
    if (currTkn != Token::OpenPar){
        cout << "ESPERADO [ ( ] - RECIBIDO [ " << yytext << " ]" << endl;
        exit(1);
    }
    nextToken();
    val = Expr();
    if (currTkn != Token::ClosePar){
        cout << "ESPERADO [ ) ] - RECIBIDO [ " << yytext << " ]" << endl;
        exit(1);
    }
    nextToken();
    if (currTkn == Token::OpenBra)
    {
        nextToken();
        if(able){
        if(execution.top() == 1){
            if(val == 1){
                execution.push(1);
            }else{
                execution.push(2);
            }
        }}
    }
    else
    {
        cout << "ESPERADO [ { ] - RECIBIDO [ " << yytext << " ]" << endl;
        exit(1);
    }
    Body();
    if (currTkn != Token::CloseBra)
    {
        cout << "ESPERADO [ } ] - RECIBIDO [ " << yytext << " ]" << endl;
        exit(1);
    }
    nextToken();
    if(currTkn == Token::KElse){
        nextToken();
        if (currTkn != Token::OpenBra)
        {
            cout << "ESPERADO [ { ] - RECIBIDO [ " << yytext << " ]" << endl;
            exit(1);
        }
        nextToken();
        //////////////////////////////
        if(able){
        if(execution.top() == 2){
            execution.pop();
            execution.push(1);
        }
        else if(execution.top() == 1){
            execution.pop();
            execution.push(2);
        }}
        Body();
        if (currTkn != Token::CloseBra)
        {
            cout << "ESPERADO [ } ] - RECIBIDO [ " << yytext << " ]" << endl;
            exit(1);
        }
        nextToken();
    }
    if(able){
    execution.pop();
    }
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
        if(vars.find(yytext)==vars.end()){
            cout << "Variable " << yytext << " no existe" << endl;
            exit(1);
        }
        val=vars.find(yytext)->second;
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