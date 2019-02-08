#include "ast.h"

unordered_map<std::string, int> vars;

void AsignST::exec(){
    vars.insert(make_pair(LValue,((Expression*)RValue)->eval()));
}

void PrintST::exec(){
    cout<<((Expression*)expr)->eval()<<endl;
}

void BlockST::exec(){
    for(int i = 0; i<stmts.size();i++){
        stmts[i]->exec();
    }
}

void IfST::exec(){
    if(((Expression*)cond)->eval()){
        cout<<"TRUE"<<endl;
        tblock->exec();
    }else{
        cout<<"FALSE"<<endl;
        fblock->exec();
    }
}


int MayExpression::eval()
{
    return ((Expression*)expr1)->eval() > ((Expression*)expr2)->eval();
}

int MenExpression::eval()
{
    return ((Expression*)expr1)->eval() < ((Expression*)expr2)->eval();
}

int MayIgExpression::eval()
{
    return ((Expression*)expr1)->eval() >= ((Expression*)expr2)->eval();
}

int MenIgExpression::eval()
{
    return ((Expression*)expr1)->eval() <= ((Expression*)expr2)->eval();
}

int IgualExpression::eval()
{
    return ((Expression*)expr1)->eval() == ((Expression*)expr2)->eval();
}

int DistExpression::eval()
{
    return ((Expression*)expr1)->eval() != ((Expression*)expr2)->eval();
}

int SumExpression::eval()
{
    return ((Expression*)expr1)->eval() + ((Expression*)expr2)->eval();
}

int ResExpression::eval()
{
    return ((Expression*)expr1)->eval() - ((Expression*)expr2)->eval();
}

int MulExpression::eval()
{
    return ((Expression*)expr1)->eval() * ((Expression*)expr2)->eval();
}
int DivExpression::eval()
{
    return ((Expression*)expr1)->eval() / ((Expression*)expr2)->eval();
}

int Iden::eval()
{
    return vars.find(id)->second;
}
