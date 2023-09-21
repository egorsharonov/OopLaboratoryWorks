#ifndef THINGSLIST_H
#define THINGSLIST_H


#include "coinsstack.h"
class ThingsList
{
private:
    struct Node {
        Object* data_;
        Node* pPrev_ = nullptr;
        Node* pNext_ = nullptr;
        Node(const Object&, Node*, Node*);
    };
    int size_;
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
public:
    ThingsList();
    ThingsList(const ThingsList&);
    ~ThingsList();
    void pushBack(const Object&);
    void push(const Object&);
    int sort();
    void del(int = 0);
    void clear();
    void insert(int, const Object&);
    void write(const std::string&) const;
    void read(const std::string&);
    int getSize() const;
    bool operator==(const ThingsList&) const;
    bool operator!=(const ThingsList&) const;
    class Iterator {
        Node* cur_;
    public:
        Iterator(Node* first) : cur_(first)
        {}
        const Iterator operator++ (int);
        Iterator& operator++ ();
        const Iterator operator-- (int);
        Iterator& operator-- ();
        Object& operator*() const;
        bool operator==(const ThingsList::Iterator&) const;
        bool operator!=(const ThingsList::Iterator&) const;
    };
    Iterator begin() const { return head_; }
    Iterator end() const { return tail_; }
};

#endif // THINGSLIST_H
