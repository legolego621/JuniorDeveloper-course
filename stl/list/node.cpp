#include "node.h"

Node::Node(int value)
    : m_ptrPred(nullptr), m_ptrNext(nullptr), m_value(value)
{ }

void Node::set_next(Node * node)
{
    m_ptrNext = node;
}

void Node::set_pred(Node *node)
{
    m_ptrPred = node;
}

void Node::set_value(int value)
{
    m_value = value;
}

Node * Node::next() const
{
    return m_ptrNext;
}

Node * Node::pred() const
{
    return m_ptrPred;
}

int Node::value() const
{
    return m_value;
}
