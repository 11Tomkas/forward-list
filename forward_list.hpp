#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include <initializer_list>

template <typename Type>
class Forward_list
{
    private:
        struct Node;
    public:
        using value_type = Type;
        using size_type = unsigned long long;
        using difference_type = long long;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
    public:
        Forward_list();
        Forward_list(size_type count);
        Forward_list(size_type count, const_reference value);
        template <typename Iter>
            Forward_list(Iter first, Iter last);
        Forward_list(const Forward_list& other);
        Forward_list(Forward_list&& other);
        Forward_list(std::initializer_list<value_type> init);
        ~Forward_list();
    private:
        Node* m_pHead;
        Node* m_pTail;
};

template <typename Type>
struct Forward_list<Type>::Node
{
    value_type value;
    Node* pNext;
};

#include "forward_list.cpp"

#endif