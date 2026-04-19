#include "forward_list.hpp"

#include <iostream>

template <typename T>
struct ForwardList<T>::Node
{
    Node(value_type _value, Node* _pNext)
        : value{ _value }
        , pNext{ _pNext }
    {
        std::cout << "Node(value_type, Node*)\n";
    }
    ~Node()
    {
        std::cout << "~Node()\n";
    }
    value_type value;
    Node* pNext;
};

template <typename T>
ForwardList<T>::ForwardList()
    : m_pHead{ nullptr }
{
}

template <typename T>
ForwardList<T>::ForwardList(size_type count)
    : ForwardList(count, value_type{})
{
}

template <typename T>
ForwardList<T>::ForwardList(size_type count, const_reference value)
    : m_pHead{ nullptr }
{
    if (count == 0)
        return;

    m_pHead = new Node{ value, nullptr };
    --count;

    Node* pHead{ m_pHead };

    for (size_type c{ 0 }; c < count; ++c)
    {
        pHead->pNext = new Node{ value, nullptr };
        pHead = pHead->pNext;
    }
}

template <typename T>
template <typename InputIt>
ForwardList<T>::ForwardList(InputIt first, InputIt last)
    : m_pHead{ nullptr }
{
    size_type count{ 0 };

    for (InputIt it{ first }; it != last; ++it)
        ++count;

    if (count == 0)
        return;

    m_pHead = new Node{ *first, nullptr };
    ++first;

    Node* pHead{ m_pHead };

    for (; first != last; ++first)
    {
        pHead->pNext = new Node{ *first, nullptr };
        pHead = pHead->pNext;
    }
}

template <typename T>
ForwardList<T>::ForwardList(const ForwardList& other)
    : m_pHead{ nullptr }
{
    if (other.empty())
        return;

    Node* pOtherHead{ other.m_pHead };

    m_pHead = new Node{ pOtherHead->value, nullptr };
    pOtherHead = pOtherHead->pNext;

    Node* pHead{ m_pHead };

    for (; pOtherHead != nullptr; pOtherHead = pOtherHead->pNext)
    {
        pHead->pNext = new Node{ pOtherHead->value, nullptr };
        pHead = pHead->pNext;
    }
}

template <typename T>
ForwardList<T>::ForwardList(ForwardList&& other)
    : m_pHead{ nullptr }
{
    if (other.empty())
        return;

    m_pHead = other.m_pHead;
    other.m_pHead = nullptr;
}

template <typename T>
ForwardList<T>::ForwardList(std::initializer_list<value_type> init)
    : m_pHead{ nullptr }
{
    if (init.size() == 0)
        return;

    typename std::initializer_list<value_type>::iterator iter{ init.begin() };

    m_pHead = new Node{ *iter, nullptr };
    ++iter;

    Node* pHead{ m_pHead };

    for (; iter != init.end(); ++iter)
    {
        pHead->pNext = new Node{ *iter, nullptr };
        pHead = pHead->pNext;
    }
}

template <typename T>
ForwardList<T>::~ForwardList()
{
    while (!empty())
    {
        Node* pNode{ m_pHead };

        m_pHead = m_pHead->pNext;
        delete pNode;
    }
    std::cout.put('\n');
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList& other)
{
    if (this == &other)
        return *this;

    if (other.empty())
        return *this;

    if (m_pHead == nullptr)
        m_pHead = new Node{ other.m_pHead->value, nullptr };
    else
    if (m_pHead != nullptr)
        m_pHead->value = other.m_pHead->value;

    Node* pHead{ m_pHead };
    Node* pOtherHead{ other.m_pHead };

    pOtherHead = pOtherHead->pNext;

    for (; pOtherHead != nullptr; pOtherHead = pOtherHead->pNext)
    {
        if (pHead->pNext == nullptr)
        {
            pHead->pNext = new Node{ pOtherHead->value, nullptr };
            pHead = pHead->pNext;
        }
        else
        if (pHead->pNext != nullptr)
        {
            pHead = pHead->pNext;
            pHead->value = pOtherHead->value;
        }
    }

    Node* pTail{ pHead };

    pHead = pHead->pNext;

    while (pHead != nullptr)
    {
        Node* pNode{ pHead };

        pHead = pHead->pNext;
        delete pNode;
    }

    pTail->pNext = nullptr;

    return *this;
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(ForwardList&& other)
{
    if (this == &other)
        return *this;

    if (other.empty())
        return *this;

    Node* pTmpNode{ m_pHead };

    m_pHead = other.m_pHead;
    other.m_pHead = pTmpNode;

    return *this;
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(std::initializer_list<value_type> ilist)
{
    if (ilist.size() == 0)
        return *this;

    typename std::initializer_list<value_type>::const_iterator iter{ ilist.begin() };

    if (m_pHead == nullptr)
        m_pHead = new Node{ *iter, nullptr };
    else
    if (m_pHead != nullptr)
        m_pHead->value = *iter;

    Node* pHead{ m_pHead };

    ++iter;

    for (; iter != ilist.end(); ++iter)
    {
        if (pHead->pNext == nullptr)
        {
            pHead->pNext = new Node{ *iter, nullptr };
            pHead = pHead->pNext;
        }
        else
        if (pHead->pNext != nullptr)
        {
            pHead = pHead->pNext;
            pHead->value = *iter;
        }
    }

    Node* pTail{ pHead };

    pHead = pHead->pNext;

    while (pHead != nullptr)
    {
        Node* pNode{ pHead };

        pHead = pHead->pNext;
        delete pNode;
    }

    pTail->pNext = nullptr;

    return *this;
}

template <typename T>
bool ForwardList<T>::empty() const
{
    return m_pHead == nullptr;
}

template <typename T>
void ForwardList<T>::print() const
{
    if (empty())
    {
        std::cout << "empty\n";

        return;
    }

    Node* pHead{ m_pHead };

    while (pHead != nullptr)
    {
        std::cout << pHead->value << ' ';
        pHead = pHead->pNext;
    }
    std::cout.put('\n');
}