#include <iostream>
#include <interpreter.h>
#include <stdlib.h>//strtoul char array to unsigned long
#include <cstring>//convert string to unsigned long
#include<expressionTree.h>
using namespace std;

//проверката се случва спрямо елементите до срещането на =
//имената на функциите са съставени от една главна латинска буква
bool Interpreter::hasAssignOpFun(const string line) const
{
    return isValidFunName(line[0]) && line[1] == '[' && isVar(line[2]) && line[3] == ']' && line[4] == '=';
}
bool Interpreter::hasAssignOpVar(const string line) const
{
    return isVar(line[0]) && line[1] == '=';
}
bool Interpreter::hasRead(const string line) const
{
    return line.substr(0,5) == "read " && isVar(line[5]);
}
bool Interpreter::hasPrint(const string line) const
{
    return line.substr(0,5) == "print";
}

void Interpreter::proceed(const string line)
{
    if(hasAssignOpVar(line))
    {
        assignVar(line[0], line.substr(2));
    }
    else if(hasAssignOpFun(line))
    {
        assignFun(line.substr(0,4), line.substr(5));
    }
    else if(hasRead(line))
    {
        read(line.substr(5));
    }
    else if(hasPrint(line))
    {
        print(line.substr(6));
    }
    else
        cerr<<"Syntax error \n";
}
void Interpreter::assignVar(const char varName, string expr)
{
    if(isDigitsOnly(expr))
        vars.add(make_pair(varName, strtoul(expr.c_str(),nullptr,10)));
    else
    {
        ExprTree t(expr);
        if(t.noVarsAtAll())
            vars.add(make_pair(varName,t.calculate()));
        else
        {
            //ако не е прост аритметичен израз
            cerr<<"Syntax error \n";
            exit(0);
        }
    }
}
void Interpreter::assignFun(const string fx,const string expr)
{
    fs.add(make_pair(fx,new ExprTree(expr)));
}

void Interpreter::read(const string expr)
{
    unsigned long v;
    cout<<"read "<<expr[0]<<" = ";
    cin>>v;
    vars.add(make_pair(expr[0], v));
}

void Interpreter::print(string expr)
{
    //принт на променлива
    if(expr.length() == 1 && isVar(expr[0]))
    {

        const char c = expr[0];
        if(vars.isMember(c))
            cout<<vars.getValueOf(c)<<endl;
        else
            cerr<<"No variable "<<c<<"\n";
    }
    //принт на функция с аргумент променлива
    else if(isValidFunName(expr[0]) && expr[1] == '[' && isVar(expr[2]) && expr[3] == ']' && expr.substr(4)=="")
    {
        //ако няма записана стойност на съответната променлива, то стойността на функцията за нея не може да се изчисли
        if(!vars.isMember(expr[2]))
            cerr<<"No variable "<<expr[2]<<"\n";
        //ако имаме записана стойност за подадения аргумент -> заместваме го в дървото на израза, но! трябва да заместим и всички други променливи в него, за да може да се пресметне
        else
        {
            unsigned long arg = vars.getValueOf(expr[2]);
            int idx = expr.find('[',0);//индексът на отварящата скоба
            string searchBy = expr.substr(0,idx);
            ExprTree* copyTree = new ExprTree (*(fs.getExprTreeByFname(searchBy)));
            copyTree->replaceVar(fs.getFArgByFname(searchBy), arg);
            if(copyTree->noVarsAtAll())
                cout<<copyTree->calculate()<<endl;
           else
           {
               copyTree->replaceAll(vars);
               //copyTree->print();
               cout<<copyTree->calculate()<<endl;

           }
           delete copyTree;
        }
    }
    else if(isValidFunName(expr[0]) && expr[1] == '[' && expr.find(']',2) != -1 && expr.substr(expr.find(']',2)+1) == "")
    {
        string expression;
        int i=2;
        while(expr[i] != ']')
        {
            expression += expr[i];
            i++;
        }
        unsigned long arg = calculateExpression(expression);
        int idx = expr.find('[',0);//индексът на отварящата скоба
            string searchBy = expr.substr(0,idx);
            ExprTree* copyTree = new ExprTree (*(fs.getExprTreeByFname(searchBy)));
            copyTree->replaceVar(fs.getFArgByFname(searchBy), arg);
            if(copyTree->noVarsAtAll())
                cout<<copyTree->calculate();
           else
           {
               copyTree->replaceAll(vars);
               //copyTree->print();
               cout<<copyTree->calculate()<<endl;

           }
           delete copyTree;
    }
    else
        cout<<calculateExpression(expr)<<endl;

}
void Interpreter::printVariablesTable() const
{
    vars.print();
}
void Interpreter::printFunctionsTable() const
{
    fs.print();
}
unsigned long Interpreter::calculateExpression(string expr)
{
    ExprTree t(expr);
    if(t.noVarsAtAll())
        {
            return t.calculate();
        }
    t.replaceAll(vars);
    if(t.noVarsAtAll())
        return t.calculate();
}
