#include<iostream>
#include<expressionTree.h>
#include<iomanip>
using namespace std;

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
    out<<setw(5*currentHeight)<<root->data<<endl;
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
    if(root->data == c)
        return true;
    return left().isMember(c) || right().isMember(c);
}
void ExprTree::replaceVar(char x, char val)
{
    //когато аргументъг се съдържа в корена, заместваме я с фактическата стойност
    if(root->data == x)
    {
        root->data = val;
        return;
    }
    //ако аргументът се съдържа в лявото поддърво - заместваме го там
    if(left().isMember(x))
    {
        left().replaceVar(x,val);
        return;
    }
    //аналогично за дясното
    if(right().isMember(x))
    {
        right().replaceVar(x,val);
        return;
    }

}
unsigned long int ExprTree::calculate() const
{

}
