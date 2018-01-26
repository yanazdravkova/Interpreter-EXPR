#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include<iostream>
#include<unordered_map>
using namespace std;
class Variables
{
    unordered_map<char, unsigned long int> table;
public:
    bool empty() const;
    void clear();
    bool isMember(const char c) const;

    void add(pair<char, unsigned long int> p);
    void remove(const char c);

    unsigned long int getValueOf(const char c);

    void print() const;
};

#endif // _VARIABLES_H_
