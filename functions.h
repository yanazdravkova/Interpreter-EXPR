#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include<iostream>
#include<unordered_map>
#include<string>
#include<expressionTree.h>
using namespace std;

class Functions
{
    unordered_map<string,ExprTree*> table;


    Functions copy(Functions const& other);
    void erase();
public:
    Functions():table(){}
    Functions(const Functions& other);
    Functions& operator=(const Functions & other);
    ~Functions();
    bool empty() const;
    void clear();
    bool isMember(const string s);

    void add(pair<string, ExprTree*> p);
    void remove(const string str);

    ExprTree* getExprTreeOf(const string str);

    void print() const;

};

#endif // _FUNCTIONS_H_
