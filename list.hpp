//
// Created by Никита Ковтуненко on 19.04.2024.
//

#ifndef MY_LIST_LIST_HPP
#define MY_LIST_LIST_HPP
#include "list.h"

template <typename T>
linked_list<T>::linked_list(): head(nullptr){}

// потестить
template <typename T>
linked_list<T>::linked_list(const linked_list<T>& list)
{
    if(list.head)
    {
        auto itB = list.cbegin();
        head = new Node<T>(*itB, nullptr);
        auto curr = head;
        ++itB;

        while(itB != list.cend())
        {
            curr->next = new Node<T>(*itB, nullptr);
            curr = curr->next;
            itB++;
        }
    }
}

template <typename T>
linked_list<T>::linked_list(linked_list<T>&& list)
{
    if(list.head)
    {
        head = list.head;
        list.head = nullptr;
    }
}

template <typename T>
linked_list<T>::linked_list(const std::initializer_list<T> & list) {
    if (list.size() != 0) {
        auto itB = list.begin();
        head = new Node<T>(*itB, nullptr);
        auto curr = head;
        ++itB;

        while (itB != list.end()) {
            curr->next = new Node<T>(*itB, nullptr);
            curr = curr->next;
            ++itB;
        }

        curr->next = nullptr;
    }
}

template <typename T>
linked_list<T>:: linked_list(size_t count, const T& item)
{
    if(!count)
        return;

    head = new Node<T>(item);
    auto curr = head;
    count--;
    while (count--)
    {
        curr->next = new Node<T>(item);
        curr = curr->next;
    }

    curr->next = nullptr;

}
// конструктор с итераторами
template <typename T>
linked_list<T>::linked_list(iterator first, iterator last)
{
    if(first == last)
        return;

    head = new Node<T>(*first);
    auto curr = head;
    ++first;

    while(first != last)
    {
        curr->next = new Node<T>(*first);
        curr = curr->next;
        ++first;
    }
}

template <typename T>
linked_list<T>& linked_list<T>:: operator=(const linked_list<T>& list)
{
    if(this == &list)
        return *this;


    auto curr = head;
    auto otherCurr = list.head;

    if(!list.head)
    {
        auto prev = curr;
        while(curr)
        {
            curr = prev->next;
            delete prev;
            prev = curr;
        }
        head = nullptr;
        return *this;
    }

    if(!head)
    {
        head = new Node<T>(T(), nullptr);
        curr = head;
    }

    while(true)
    {
        if(!otherCurr->next)
        {
            if(curr->next) {
                auto prev = curr->next;
                auto next = prev;
                curr->next = nullptr;
                while(next)
                {
                    next = prev->next;
                    delete prev;
                    prev = next;
                }
            }

        }

        if(!curr->next)
        {
            if(otherCurr->next) {
                curr->next = new Node<T>();
            }
        }
        curr->val = otherCurr->val;
        curr = curr->next;
        otherCurr = otherCurr->next;

        if(!otherCurr){
            return *this;
        }
    }
}

template <typename T>
linked_list<T>& linked_list<T>::operator=(linked_list<T>&& list){
    if(this == &list)
        return *this;

    clear();
    head = list.head;
    list.head = nullptr;
    return *this;
}

template <typename T>
linked_list<T>::~linked_list()
{
    auto curr = head;

    while(curr != nullptr)
    {
        auto prev = curr;
        curr = curr->next;
        delete prev;
    }
}
template <typename T>
void linked_list<T>::clear() noexcept{

    auto curr = head;

    while(curr != nullptr)
    {
        auto prev = curr;
        curr = curr->next;
        delete prev;
    }
    head = nullptr;
}

template <typename T>
void linked_list<T>:: pushFront(const T& item){
    auto newHead = new Node<T>(item);
    newHead->next = head;
    head = newHead;
}

template <typename T>
void linked_list<T>:: pushFront(T&& item )
{
    auto newHead = new Node<T>(item);
    newHead->next = head;
    head = newHead;
}

template <typename T>
void linked_list<T>::insert_after(iterator& it,const T&& val)
{
    auto next = it.ptr->next;
    it.ptr->next = new Node<T>(std::move(val));
    it.ptr->next->next = next;
}

template <typename T>
void linked_list<T>::insert_after(iterator& it,const T& val)
{
    auto next = it;
    it->next = new Node<T>(val);
    it->next->next = next;
}

template <typename T>
typename linked_list<T>::iterator linked_list<T>::begin() noexcept{
    return iterator(head);
}

template <typename T>
typename linked_list<T>::const_iterator linked_list<T>::cbegin() const noexcept{
    return const_iterator(head);
}

template <typename T>
typename linked_list<T>::iterator linked_list<T>::end() noexcept{
    return iterator(nullptr);
}

template <typename T>
typename linked_list<T>::const_iterator linked_list<T>::cend() const noexcept{
    return const_iterator(nullptr);
}

template <typename T>
bool linked_list<T>::empty() const noexcept {
    return head == nullptr;
}

template <typename T>
void linked_list<T>::swap(linked_list<T> & list) {
    auto ptr = list.head;
    list.head = head;
    head = ptr;
}
template <typename T>
void linked_list<T>::pop_front() {
    if(!head)
        throw std::runtime_error("List empty");

    auto prev = head;
    head = head->next;
    delete prev;
}
template <typename T>
typename linked_list<T>::iterator linked_list<T>::erase_after(iterator& item)
{
    if(!item->next)
        throw std::runtime_error("Next element == nullptr");

    auto next = item->next;
    item->next = next->next;
    delete next;

    return iterator(item->next);
}

template <typename T>
typename linked_list<T>::iterator linked_list<T>::erase_after(iterator& first,iterator & last)
{
    if(!first.ptr->next)
        throw std::runtime_error("Next element == nullptr");

    if(first == last)
        return iterator(last);


    auto curr = iterator(first.ptr->next);

    while(curr != last)
    {
        auto prev = curr;
        ++curr;
        delete prev.ptr;
    }

    first.ptr->next = last.ptr;
    return last;
}

template <typename T>
typename linked_list<T>::iterator linked_list<T>::find(const T &val) {

    auto it = begin();

    while(it != end())
    {
        if(*it == val)
            return it;
        ++it;
    }
    return end();
}

#endif //MY_LIST_LIST_HPP
