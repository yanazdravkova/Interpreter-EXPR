#include <iostream>
#include<variables.h>
#include<functions.h>
#include<expressionTree.h>
using namespace std;
void testVariables()
{
    Variables v;
    v.add(make_pair('a',123));
    v.add(make_pair('b',12));
    v.print();
    cout<<v.isMember('a');
    cout<<v.isMember('c');
    v.add(make_pair('a',5));
    v.print();
    v.clear();
    cout<<endl<<v.empty();
    v.print();
}
void testFunctions()
{

    ExprTree* fx = new ExprTree('+',
                 ExprTree('2',ExprTree(), ExprTree()),
                 ExprTree('*',
                          ExprTree('3',ExprTree(),ExprTree()),
                          ExprTree('x',ExprTree(),ExprTree())));
    ExprTree fy('*',
                ExprTree('5',ExprTree(), ExprTree()),
                ExprTree('y',ExprTree(), ExprTree()));
    fx->print();
    cout<<endl;
    fy.print();
    Functions fs;
    fs.add(make_pair("f[x]",fx));
    fs.print();
}
int main()
{
    testFunctions();
    return 0;
}
