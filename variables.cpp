#include<variables.h>
#include<iostream>
#include<unordered_map>
using namespace std;
bool Variables::empty() const
{
    return table.empty();
}
void Variables::clear()
{
    table.clear();
}
bool Variables::isMember(const char c) const
{
    for(const pair<char,unsigned long int> p : table)
    {
        if(p.first == c)
            return true;
    }
    return false;
}

void Variables::add(pair<char, unsigned long int> p)
{
    if(table.find(p.first) == table.end())
    {
        table[p.first] = p.second;
    }
    else
        cerr<<"Trying to add variable in variables table which already exists! ";
}
void Variables::remove(const char c)
{
    table.erase(c);
}

unsigned long int Variables::getValueOf(const char c)
{
    if(isMember(c))
        return table[c];
}

void Variables::print() const
{
    if(empty())
    {
        cout<<"Empty variables table; Nothing to print!";
        return;
    }
    for(const pair<char,unsigned long int> p : table)
    {
        cout<<p.first<<":"<<p.second<<" ";
    }
    cout<<endl;
}
