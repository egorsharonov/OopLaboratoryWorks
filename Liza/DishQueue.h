#ifndef DISHQUEUE_H
#define DISHQUEUE_H


#include "Operation.h"
class DishQueue
{
private:
    struct Node
    {
        Dish* data;
        Node* pNext = nullptr;
        Node* pPrev = nullptr;
        Node(Dish*, Node*, Node*);
    };
    int size;
    Node* head = nullptr;
    Node* tail = nullptr;

public:
    DishQueue();
    DishQueue(const DishQueue&);
    ~DishQueue();
    void pushBack(Dish*);
    void popFront();
    void clear();
    void write(string) const;
    void read(string);
    //void emplace(Node &&value);
    int getSize() const;
    bool operator==(const DishQueue&) const;
    bool operator!=(const DishQueue&) const;
    class Iterator
    {
        Node* cur;

    public:
        Iterator(Node* first) : cur(first)
        {}
        Iterator operator++(int);
        Iterator operator++();
        Iterator operator--(int);
        Iterator operator--();
        Dish& operator*();
        bool operator==(const DishQueue::Iterator&);
        bool operator!=(const DishQueue::Iterator&);
    };
    Iterator begin() const { return head; }
    Iterator end() const { return tail; }
};

#endif // DISHQUEUE_H
