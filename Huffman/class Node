#ifndef NODE_H
#define NODE_H
using namespace std;

//Класс ячеек дерева
class Node
{
public:
    Node()
        : left(nullptr), right(nullptr)
    {}
    Node(Node * LeftNode, Node * RightNode)
        : left(LeftNode), right(RightNode), number(LeftNode->number + RightNode->number)
    {}
public:
    int number;
    char value;
    Node * left, * right;
};

#endif // NODE_H
