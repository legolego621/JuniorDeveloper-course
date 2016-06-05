/* realization list v1 */

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "node.h"

class List
{
public:
    List();
    List(std::size_t size, int value = 0);
    List(const List & list);
    ~List();
public:
    void insert(std::size_t pos, int value);
    void erase(std::size_t pos);
    void push_back(int value);
    void pop_back();
    int front() const;
    int back() const;
    void swap(List & list);
    void clear();
public:
    std::size_t size() const;
    int max_size() const;
public:
    List & operator = (const List & list);
    bool operator == (const List & list) const;
    friend std::ostream & operator << (std::ostream & os, const List & list);
private:
    void initialization(std::size_t size, int value);
private:
    std::size_t m_size;
    Node * m_ptrRoot;
    Node * m_ptrBack;
};

#endif // LIST_H
