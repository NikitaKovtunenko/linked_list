//
// Created by Никита Ковтуненко on 19.04.2024.
//

#ifndef MY_LIST_LIST_H
#define MY_LIST_LIST_H
#include <iostream>
#include <initializer_list>
template <typename T>
struct Node{
    T val;
    Node<T> * next;
    Node(const T& v, Node<T> * p = nullptr): val(v), next(p){}
    Node() = default;
    Node(const Node<T>&) = default;
    Node(Node<T>&&) = default;
    Node<T>& operator= (const Node<T>& ) = default;
    Node<T>& operator= (Node<T>&&) = default;
};

template <typename T>
class linked_list {
    Node<T>* head;

    struct list_iterator {

        Node<T>* ptr;

        list_iterator(Node<T>* p) : ptr(p){}

        list_iterator operator++(int) {
            list_iterator l(*this);
            ptr = ptr->next;
            return l;
        }

        list_iterator& operator++()
        {
            ptr = ptr->next;
            return *this;
        }

        T operator*() const
        {
            return ptr->val;
        }

        T* operator->() const {
            return &ptr->val;
        }

        bool operator!=(const list_iterator& right) const
        {
            return ptr != right.ptr;
        }

        bool operator == (const list_iterator&  right) const
        {
            return ptr == right.ptr;
        }
    };

    using const_iterator = const list_iterator;
    using iterator = list_iterator;

public:
    // итераторы

    // конструктор по умолчанию
    linked_list();
    // конструктор по копирующий
    linked_list(const linked_list& list);
    // конструктор перемещающий
    linked_list(linked_list&& list);
    // конструктор со списком инициализации
    linked_list(const std::initializer_list<T> & list);
    // конструктор (количество, значение)
    linked_list(size_t count, const T& );
    // конструктор с итераторами
    linked_list(iterator begin, iterator end);
    // оператор копирования
    linked_list& operator=(const linked_list<T>& list);
    // оператор копирования перемещаюший
    linked_list& operator=(linked_list<T>&& list);
    // деструктор
    ~linked_list();
    // добавить в начало
    void pushFront(const T&);
    void pushFront(T&&);

    // добавить в начало emplace
    // добавить в конец emplace

    // вставить после
    void insert_after(iterator & it,const T&&);
    void insert_after(iterator & it,const T&);
    // получить итератор на начало
    iterator begin() noexcept;
    const_iterator cbegin() const noexcept;
    // получить итератор на конец
    iterator end() noexcept;
    const_iterator cend() const noexcept;

    void clear() noexcept;

    // реализовать функции
    void swap(linked_list<T> & );
    bool empty() const noexcept;
    // assign
    void pop_front();
    iterator erase_after(iterator & item);
    iterator erase_after(iterator & first,iterator& last);
    iterator find(const T & val);
};


#endif //MY_LIST_LIST_H

#include "list.hpp"