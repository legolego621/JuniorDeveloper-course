/* realisation list v1 */

#include "list.h"

List::List()
    : m_ptrBack(nullptr), m_ptrRoot(nullptr), m_size(0)
{ }

List::List(std::size_t size, int value)
    : m_ptrBack(nullptr), m_ptrRoot(nullptr), m_size(0)
{
    List::initialization(size, value);
}

List::List(const List & list)
    : m_ptrBack(nullptr), m_ptrRoot(nullptr), m_size(0)
{
    Node * ptr = list.m_ptrRoot;
    for(std::size_t i = 0; i < list.size(); ++i){
        List::push_back(ptr->value());
        ptr = ptr->next();
    }
}

List::~List()
{
    for(std::size_t i = 0; i < m_size; ++i)
        List::pop_back();
}

void List::initialization(std::size_t size, int value)
{
    for(std::size_t i = 0; i < size; ++i)
        List::push_back(value);
}

void List::clear()
{
    if(m_size == 0){
        std::cout << "List null. Return (0)" << std::endl;
        return;
    }
    std::size_t size = m_size;
    for(std::size_t i = 0; i < size; ++i)
        List::pop_back();
}

void List::erase(std::size_t pos)
{
    if(m_size == 0 || pos >= m_size){
        std::cout << "Fail" << std::endl;
        return;
    }
    if(m_size - 1 == 0){
        delete m_ptrRoot;
        m_ptrRoot = m_ptrBack = nullptr;
    }
    if(pos == m_size - 1){
        m_ptrBack = m_ptrBack->pred();
        delete m_ptrBack->next();
        m_ptrBack->set_next(nullptr);
    }
    else if(pos == 0){
        m_ptrRoot = m_ptrRoot->next();
        delete m_ptrRoot->pred();
        m_ptrRoot->set_pred(nullptr);
    }
    else{
        Node * ptr = m_ptrRoot;
        for(std::size_t i = 0; i <= pos; ++i)
        {
            if(i == pos){
                ptr->pred()->set_next(ptr->next());
                ptr->next()->set_pred(ptr->pred());
                delete ptr;
                break;
            }
            ptr = ptr->next();
        }
    }
}

void List::insert(std::size_t pos, int value)
{
    if((m_size == 0 && pos != 0) || pos > m_size){
        std::cout << "List null. Return (0)" << std::endl;
        return;
    }
    Node * node = new Node(value);
    if(pos == 0){
        node->set_next(m_ptrRoot);
        m_ptrRoot->set_pred(node);
        m_ptrRoot = node;
    }
    else if(pos == m_size){
        node->set_pred(m_ptrBack);
        m_ptrBack->set_next(node);
        m_ptrBack = node;
    }
    else{
        Node * ptr = m_ptrRoot;
        for(std::size_t i = 0; i <= pos; ++i){
            if(i == pos){
                ptr->pred()->set_next(node);
                node->set_pred(ptr->pred());
                ptr->set_pred(node);
                node->set_next(ptr);
            }
            ptr = ptr->next();
        }
    }
    ++m_size;
}

void List::push_back(int value)
{
    Node * node = new Node(value);
    if(m_size == 0)
        m_ptrRoot = node;
    else{
        m_ptrBack->set_next(node);
        node->set_pred(m_ptrBack);
    }
    m_ptrBack = node;
    ++m_size;
}

void List::pop_back()
{
    if(m_size == 0){
        std::cout << "List null. Return (void)" << std::endl;
        return;
    }
    if(m_size - 1 == 0){
        delete m_ptrBack;
        m_ptrRoot = m_ptrBack = nullptr;
    }
    else{
        m_ptrBack = m_ptrBack->pred();
        delete m_ptrBack->next();
        m_ptrBack->set_next(nullptr);
    }
    --m_size;
}

int List::back() const
{
    if(m_size == 0){
        std::cout << "List null. Return (0)" << std::endl;
        return 0;
    }
    return m_ptrBack->value();
}

int List::front() const
{
    if(m_size == 0){
        std::cout << "List null. Return (0)" << std::endl;
        return 0;
    }
    return m_ptrRoot->value();
}

std::size_t List::size() const
{
    return m_size;
}

int List::max_size() const
{
    if(m_size == 0){
        std::cout << "List null. Return (0)" << std::endl;
        return 0;
    }
    int max = m_ptrRoot->value();
    Node * ptr;
    for(ptr = m_ptrRoot; ptr != nullptr; ptr = ptr->next()){
        if(ptr->value() > max)
            max = ptr->value();
    }
    return max;
}

std::ostream & operator << (std::ostream & os, const List & list)
{
    if(list.size() == 0){
        os << "List null!";
        return os;
    }
    Node * ptr;
    for(ptr = list.m_ptrRoot; ptr != nullptr; ptr = ptr->next())
        os << ptr->value() << " ";
    return os;
}

List & List::operator = (const List & list)
{
    if(this == &list)
        return *this;
    List::clear();
    Node * ptr = list.m_ptrRoot;
    for(std::size_t i = 0; i < list.size(); ++i){
        List::push_back(ptr->value());
        ptr = ptr->next();
    }
    return *this;
}

bool List::operator == (const List & list) const
{
    if(m_size != list.size())
        return false;
    Node * ptr_list, * ptr_this;
    for(ptr_this = m_ptrRoot, ptr_list = list.m_ptrRoot; ptr_this != nullptr && ptr_list != nullptr; ptr_this = ptr_this->next(), ptr_list = ptr_list->next()){
        if(ptr_this->value() != ptr_list->value())
            return false;
    }
    return true;
}

void List::swap(List & list)
{
    List temp = *this;
    *this = list;
    list = temp;
}

