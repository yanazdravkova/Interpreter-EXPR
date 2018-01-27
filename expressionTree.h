#ifndef _EXPRESSION_TREE_H_
#define _EXPRESSION_TREE_H_

#include<iostream>
#include<string>

using namespace std;

struct OpNode
{
    ///забележка* operation-a в случаите, когато дървото е всъщност тяло на функция и съдържа променливи, може да бъде име на променлива
  char operation;
   unsigned long value;

  OpNode():operation(0),value(0) {}

  OpNode(char _operation):operation(_operation),value(0) {}

  OpNode(unsigned long _value):operation(0),value(_value) {}

  bool isOperation() {
    return operation != 0;
  }

};
class Node
{
    public:
    OpNode data;
    Node* left;
    Node* right;
        Node():data(), left(nullptr), right(nullptr) {}
    Node(OpNode data, Node* left = nullptr, Node* right = nullptr)
        : data(data), left(left), right(right) {}
    void replaceVarN(char x,unsigned long val);//замества 1 срещане на x със val в дървото
};
class ExprTree
{
    friend class Node;
    Node* root;

    Node* copy(Node* node);
    void erase(Node* node);
    ExprTree(Node* root): root(copy(root)) {}
    void prettyPrint(ostream& out, int currentHeight) const;
    bool isValidOperation(const char c) const;
    bool isNumber(const char c) const;

public:
    ExprTree(): root(nullptr) {}
    void f(string str);
    ExprTree(const char data, ExprTree left, ExprTree right);
    ExprTree(unsigned long data, ExprTree left, ExprTree right);

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
    void print() const;

    unsigned long calculate() const;//функцията calculate се вика, единствено когато сме сигурни, че в дървото няма променливи, а само операции и числа

    bool isMember(const char c) const;
    void replaceVar(char x, unsigned long val);

    bool noVarsExceptX(const char x) const;//няма други променливи в дървото, освен тази, с която функцията е била дефинирана т.е x от дефиницята на D[x] от примера в описанието
    bool noVarsAtAll() const;//в дървото имаме само операции са смятане и числа <=> дървото е готово да бъде пресметнато


};

#endif // _EXPRESSION_TREE_H_
