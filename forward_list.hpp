#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include <initializer_list>

template <typename T>
class ForwardList
{
    private:
        struct Node;
    public:
        using value_type = T;
        using size_type = unsigned long long;
        using difference_type = long long;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        ForwardList();
        ForwardList(size_type count);
        ForwardList(size_type count, const_reference value);
        template <typename InputIt>
            ForwardList(InputIt first, InputIt last);
        ForwardList(const ForwardList& other);
        ForwardList(ForwardList&& other);
        ForwardList(std::initializer_list<value_type> init);
        ~ForwardList();

        ForwardList& operator=(const ForwardList& other);
        ForwardList& operator=(ForwardList&& other);
        ForwardList& operator=(std::initializer_list<value_type> ilist);

        bool empty() const;

        void print() const;
    private:
        Node* m_pHead;
};

#include "forward_list.cpp"

#endif