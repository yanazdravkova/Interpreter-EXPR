#include<iostream>
#include<functions.h>
using namespace std;

Functions Functions::copy(Functions const& other)
{
    for(const pair<string,ExprTree*> p : other.table)
    {
        table[p.first] = new ExprTree(*p.second);
    }
}
void Functions::erase()
{
    table.clear();
}

Functions::Functions(Functions const& other):Functions()
{
    copy(other);
}
Functions& Functions::operator=(Functions const& other)
{
    if(this != &other)
    {
        erase();
        copy(other);
    }
    return *this;
}
Functions::~Functions()
{
    erase();
}
bool Functions::empty() const
{
    return table.empty();
}
void Functions::clear()
{
    erase();
}
bool Functions::isMember(const string s)
{
    for(const pair<string, ExprTree*> p:table)
    {
        if(s.compare(p.first))
            return true;
    }
    return false;
}

void Functions::add(pair<string, ExprTree*> p)
{
    if(table.find(p.first) == table.end())
    {
        table[p.first] = p.second;
    }
     else
        cerr<<"Trying to add variable in variables table which already exists! ";
}
void Functions::remove(const string str)
{
    table.erase(str);
}

ExprTree* Functions::getExprTreeOf(const string str)
{
    for(const pair<string, ExprTree*> p:table)
    {
        if(str.compare(p.first))
            return p.second;
    }
        cerr<<"Trying to get ExprTree of non-existing element!";
}

void Functions::print() const
{
    for(const pair<string, ExprTree*> p:table)
    {
        cout<<p.first<<endl;
        p.second->print();
    }
    cout<<endl;
}
