#ifndef _EXPRESSION_TREE_H_
#define _EXPRESSION_TREE_H_

#include<iostream>
#include<string>

using namespace std;

struct Node
{
    char data;
    Node* left;
    Node* right;
        Node():data(), left(nullptr), right(nullptr) {}
    Node(char data, Node* left = nullptr, Node* right = nullptr)
        : data(data), left(left), right(right) {}
};
class ExprTree
{
    Node* root;
    Node* copy(Node* node);
    void erase(Node* node);
    ExprTree(Node* root): root(copy(root)) {}
    void prettyPrint(ostream& out, int currentHeight) const;
public:
    ExprTree(): root(nullptr) {}

    ExprTree(const char data, ExprTree left, ExprTree right);

    ExprTree(ExprTree&& other) noexcept: ExprTree()
    {
        std::swap(root, other.root);
    }

    ExprTree(ExprTree const& other): root(copy(other.root)) {}

    ExprTree& operator=(ExprTree other);

    ~ExprTree();
    bool empty()const;

    ExprTree left() const;

    ExprTree right() const;
    bool isMember(const char c) const;
    //not made
    bool noVarsExceptX(const char x);//���� ����� ���������� � �������, ����� ����, � ����� ��������� � ���� ���������� �.� x �� ���������� �� D[x] �� ������� � ����������
    bool noVarsAtAll();//� ������� ����� ���� �������� �� ������� � ����� <=> ������� � ������ �� ���� �����������
    void replaceVar(char x, char val);//�������� 1 ������� �� x ��� val � �������

    unsigned long int calculate() const;

    void print() const;
};

#endif // _EXPRESSION_TREE_H_
