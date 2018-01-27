#include <iostream>
#include<variables.h>
#include<functions.h>
#include<expressionTree.h>
#include<rpnConverter.h>
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
                 ExprTree((unsigned long)1,ExprTree(), ExprTree()),
                 ExprTree('%',
                          ExprTree('*',
                                   ExprTree((unsigned long)2,ExprTree(), ExprTree()),
                                   ExprTree((unsigned long)2,ExprTree(), ExprTree())),
                          ExprTree((unsigned long)3,ExprTree(),ExprTree())));
    ExprTree fy('*',
                ExprTree((unsigned long)5,ExprTree(), ExprTree()),
                ExprTree('y',ExprTree(), ExprTree()));
    ExprTree fz("a + 2*2%3");
    fz.print();
    cout<<fz.calculate();

}
void testRPN()
{
    string s("(12+58%13)*(3+2)");
    RPNConverter rc(s);
    cout<<rc.toPostfix();
}
int main()
{
    testFunctions();
    return 0;
}
