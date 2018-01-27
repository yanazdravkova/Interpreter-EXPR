#include<iostream>
#include<expressionTree.h>
#include<iomanip>
#include<stack>
#include<rpnConverter.h>
#include <stdlib.h>//strtoul char array to unsigned long
#include <cstring>//convert string to unsigned long
using namespace std;

bool validOperator(const char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' );
}
bool isVar(const char c)
{
	if(c >= 'a' && c <= 'z') return true;
	return false;
}

Node* ExprTree::copy(Node* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    return new Node(node->data, copy(node->left), copy(node->right));
}

void ExprTree::erase(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    erase(node->left);
    erase(node->right);
    delete node;
}
ExprTree::ExprTree(const char data, ExprTree left, ExprTree right)
{
    root = new Node(data);
    std::swap(root->left, left.root);
    std::swap(root->right, right.root);
}
ExprTree::ExprTree(unsigned long data, ExprTree left, ExprTree right)
{
    root = new Node(data);
    std::swap(root->left, left.root);
    std::swap(root->right, right.root);
}
ExprTree& ExprTree::operator=(ExprTree other)
{
    std::swap(root, other.root);
    return *this;
}
ExprTree::~ExprTree()
{
    erase(root);
}
bool ExprTree::empty()const
{
    return root == nullptr;
}
ExprTree ExprTree::left() const
{
    return ExprTree(root->left);
}

ExprTree ExprTree::right() const
{
    return ExprTree(root->right);
}

void ExprTree::prettyPrint(ostream& out, int currentHeight) const
{
    if(empty())
        return;
    right().prettyPrint(out, currentHeight + 1);
    out<<setw(5*currentHeight);
    if((root->data).isOperation())
    {
        cout<<(root->data).operation<<endl;
    }
    else
    {
        cout<<(root->data).value<<endl;
    }

    left().prettyPrint(out, currentHeight + 1);
}
void ExprTree::print() const
{
    prettyPrint(cout,0);
}
bool ExprTree::isMember(const char c) const
{
    if(empty())
        return false;
    if((root->data).isOperation() && (root->data).operation == c)
        return true;
    return left().isMember(c) || right().isMember(c);
}
void Node::replaceVarN(char x,unsigned long val)
{
    //������ ���������� �� ������� � ������, ���������� � � ������������ ��������
    if(data.isOperation() && data.operation == x)
    {
        data.operation = 0;
        data.value = val;
        return;
    }
    //��� ���������� �� ������� � ������ �������� - ���������� �� ���
    if(ExprTree(left).isMember(x))
    {
        left->replaceVarN(x, val);
        return;
    }
    //���������� �� �������
    if(ExprTree(right).isMember(x))
    {
        right->replaceVarN(x,val);
        return;
    }

}
void ExprTree::replaceVar(char x,unsigned long val)
{
    root->replaceVarN(x,val);
}
unsigned long ExprTree::calculate() const
{
    if(empty())
        return 0;
    if(! (root->data).isOperation())
        return (root->data).value;
    unsigned long l = left().calculate();
    unsigned long r = right().calculate();
    switch ((root->data).operation)
    {
    case '*':
        return l * r;
    case '+':
        return l + r;
    case '-':
        return l - r;
    case '%':
        return l % r;
    case '/':
        return r == 0 ? 0 : l / r;
    default:
        return 0;
    }
}
bool ExprTree::noVarsExceptX(const char x) const
{
    if(empty())
        return true;
    //� ������ ����� ���������� ��� ����������� ��������
    if((root->data).isOperation())
    {
        //��� � ������ ����� ������������, ����� � �������� ��������� �� ��������� -> ����������� ����� ����������
        if((root->data).operation == x)
        {
            return left().noVarsExceptX(x) && right().noVarsExceptX(x);
        }
        //��� � ������ ����� ����������� ��������, ������ ����������� 2�� ����������
        if(validOperator((root->data).operation))
           {
               return left().noVarsExceptX(x) && right().noVarsExceptX(x);
           }

        //����� ����� ����� ����������
        return false;
    }
    //� ������ ����� ����� -> ������ �� �������� ������������
    return left().noVarsExceptX(x) && right().noVarsExceptX(x);
}
bool ExprTree::noVarsAtAll() const
{
    if(empty())
        return true;
    if((root->data).isOperation() && ! validOperator((root->data).operation))
        return false;
    else
        return left().noVarsAtAll() && right().noVarsAtAll();
}
//used: https://www.geeksforgeeks.org/expression-tree/
ExprTree::ExprTree(string str):ExprTree()
{
    RPNConverter rc(str);
    string postfix = rc.toPostfix();
    cout<<postfix<<endl;
    //return;
    stack<Node*> nodes;
    Node*  t;
    Node* t1;
    Node* t2;
    string num;
    for (int i=0; i<postfix.length(); i++)
    {
        cout<<"i: "<<i<<endl;
        cout<<"nodes size: "<<nodes.size()<<endl;
        // ��� � �����
        if (isdigit(postfix[i]))
        {
            num += postfix[i];
            if(postfix[i+1] == ',')//�� ���� �� ������� ����� ���������, ������ ���� ����� ����� ��� �������, ���������� ���� ��������� ������, ����� � �������� - ����
            {
                 Node* tprev = new Node(strtoul (num.c_str(), nullptr, 10));
            cout<<num<<endl;
            nodes.push(tprev);
            num = "";
            }
        }
        else if(postfix[i] == ',')
        {

        }
        else if(isVar(postfix[i]))
        {
            t = new Node(postfix[i]);
            nodes.push(t);
        }
        else // operator
        {

            if(!num.empty())
            {
                //cout<<"num"<<num<<endl;
                //��������� �������� �� ������� �� ���������� ����� ��������� � ����� � ����� � ���������� ����
            Node* tprev = new Node(strtoul (num.c_str(), nullptr, 10));
            nodes.push(tprev);
            num = "";
            }

            //������ ����� � ��������� �� ����� �� �����
            t = new Node(postfix[i]);

            //��������� 2 �������� �� �����
            t1 = nodes.top(); // Store top
            nodes.pop();      // Remove top
            t2 = nodes.top();
            nodes.pop();

            //��������� �� ���� ���������� �� ����������, ���� �������� ���� �� ����������
            t->right = t1;
            t->left = t2;

            //��������� �������������� ����� ���� ������ �� � �����
            nodes.push(t);
        }
    }

    //������� � ���������� ������ �� ������ ����� � �����
    //�������������� ����� ����� � ����
    root = nodes.top();
    //���������� �����
    nodes.pop();
}


