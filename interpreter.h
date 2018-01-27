#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include<iostream>
#include<variables.h>
#include<functions.h>
#include<expressionTree.h>
#include<rpnConverter.h>
#include<string>
class Interpreter
{
    Variables vars;
    Functions fs;
    bool isValidFunName(const char c) const
{
	if(c >= 'A' && c <= 'Z') return true;
	return false;
}
bool isVar(const char c) const
{
	if(c >= 'a' && c <= 'z') return true;
	return false;
}
bool isDigitsOnly(const string &str)
{
    return str.find_first_not_of("0123456789") == -1; //StackOverflow
}
    bool hasAssignOpFun(const string line) const;
    bool hasAssignOpVar(const string line) const;
    bool hasRead(const string line) const;
    bool hasPrint(const string line) const;

    void assignVar(const char varName, string expr);
    void assignFun(const string fx,const string expr);
    void read( string expr);
    void print(string expr);


public:
unsigned long calculateExpression(string expr);
    void proceed(string line);
    void printVariablesTable() const;
    void printFunctionsTable() const;
};

#endif // _INTERPRETER_H_
