#ifndef _RPN_CNVERTER_H_
#define _RPN_CNVERTER_H_

#include<string>
#include<sstream>
#include<iostream>
#include<stack>
using namespace std;

class RPNConverter
{
    stack<char> opStack;
    string str;

    int priority(char op) const
    {
        switch (op)
        {
        case '+':
        case '-':
            return 1;
        case '*':
        case '%':
        case '/':
            return 2;
        }
        return 0;
    }
public:
    RPNConverter(string _str):str(_str){}
    string toPostfix();

};

#endif // _RPN_CNVERTER_H_
