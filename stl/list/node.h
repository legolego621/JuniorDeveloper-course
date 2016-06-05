#ifndef NODE_H
#define NODE_H

class Node
{
public:
    Node(int value);
public:
    void set_next(Node * node);
    void set_pred(Node * node);
    void set_value(int value);
    Node * next() const;
    Node * pred() const;
    int value() const;
private:
    int m_value;
    Node * m_ptrNext;
    Node * m_ptrPred;
};

#endif // NODE_H
