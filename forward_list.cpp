#include "forward_list.hpp"

template <typename Type>
Forward_list<Type>::Forward_list()
    : m_pHead{ nullptr }
    , m_pTail{ nullptr }
{
}

template <typename Type>
Forward_list<Type>::Forward_list(size_type count)
    : m_pHead{ nullptr }
    , m_pTail{ nullptr }
{
    if (count == 0)
        return;

    m_pHead = new Node{ value_type{}, nullptr };

    Node* pNode{ m_pHead };

    for (size_type c{ 1 }; c < count; ++c)
    {
        pNode->pNext = new Node{ value_type{}, nullptr };
        pNode = pNode->pNext;
    }
    m_pTail = pNode;
}

template <typename Type>
Forward_list<Type>::Forward_list(size_type count, const_reference value)
    : m_pHead{ nullptr }
    , m_pTail{ nullptr }
{
    if (count == 0)
        return;

    m_pHead = new Node{ value, nullptr };

    Node* pNode{ m_pHead };

    for (size_type c{ 1 }; c < count; ++c)
    {
        pNode->pNext = new Node{ value, nullptr };
        pNode = pNode->pNext;
    }
    m_pTail = pNode;
}

template <typename Type>
template <typename Iter>
Forward_list<Type>::Forward_list(Iter first, Iter last)
    : m_pHead{ nullptr }
    , m_pTail{ nullptr }
{
    if ((last - first) == 0)
        return;

    m_pHead = new Node{ *first, nullptr };
    ++first;

    Node* pNode{ m_pHead };

    for (; first != last; ++first)
    {
        pNode->pNext = new Node{ *first, nullptr };
        pNode = pNode->pNext;
    }
    m_pTail = pNode;
}

template <typename Type>
Forward_list<Type>::Forward_list(const Forward_list& other)
    : m_pHead{ nullptr }
    , m_pTail{ nullptr }
{
    if (other.m_pHead == nullptr)
        return;

    Node* pOtherNode{ other.m_pHead };

    m_pHead = new Node{ pOtherNode->value, nullptr };
    pOtherNode = pOtherNode->pNext;

    Node* pNode{ m_pHead };

    for (; pOtherNode != nullptr; pOtherNode = pOtherNode->pNext)
    {
        pNode->pNext = new Node{ pOtherNode->value, nullptr };
        pNode = pNode->pNext;
    }
    m_pTail = pNode;
}

template <typename Type>
Forward_list<Type>::Forward_list(Forward_list&& other)
    : m_pHead{ nullptr }
    , m_pTail{ nullptr }
{
    if (other.m_pHead == nullptr)
        return;

    m_pHead = other.m_pHead;
    m_pTail = other.m_pTail;
    other.m_pHead = nullptr;
    other.m_pTail = nullptr;
}

template <typename Type>
Forward_list<Type>::Forward_list(std::initializer_list<value_type> init)
    : m_pHead{ nullptr }
    , m_pTail{ nullptr }
{
    if (init.size() == 0)
        return;

    typename std::initializer_list<value_type>::iterator iter{ init.begin() };

    m_pHead = new Node{ *iter, nullptr };
    ++iter;

    Node* pNode{ m_pHead };

    for (; iter != init.end(); ++iter)
    {
        pNode->pNext = new Node{ *iter, nullptr };
        pNode = pNode->pNext;
    }
    m_pTail = pNode;
}

template <typename Type>
Forward_list<Type>::~Forward_list()
{
    Node* pNode;

    while (m_pHead != nullptr)
    {
        pNode = m_pHead;
        m_pHead = m_pHead->pNext;
        delete pNode;
    }
}