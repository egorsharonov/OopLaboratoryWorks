#ifndef THINGSLIST_H
#define THINGSLIST_H


#include "coins.h"
class List
{
private:
    struct Node {
        Item* data_;
        Node* pPrev_ = nullptr;
        Node* pNext_ = nullptr;
        Node(const Item&, Node*, Node*);
    };
    int size_;
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
public:
    List();
    List(const List&);
    ~List();
    void pushBack(const Item&);
    void push(const Item&);
    int sort();
    void del(int = 0);
    void popAll();
    void insert(int, const Item&);
    void write(const std::string&) const;
    void read(const std::string&);
    int getSize() const;
    bool operator==(const List&) const;
    bool operator!=(const List&) const;
    class Iterator {
        Node* cur_;
    public:
        Iterator(Node* first) : cur_(first)
        {}
        const Iterator operator++ (int) {
            auto temp = cur_;
            cur_ = cur_->pNext_;
            return temp;
        }
        Iterator& operator++ ()   {
            cur_ = cur_->pNext_;
            return (*this);
        }
        const Iterator operator-- (int){
            auto temp = cur_;
            cur_ = cur_->pPrev_;
            return temp;
        }
        Iterator& operator-- (){
            cur_ = cur_->pPrev_;
            return (*this);
        }
        Item& operator*() const{
            return *(cur_->data_);
        }
        bool operator==(const Iterator& right) const{
            return *cur_->data_ == *right.cur_->data_;
        }
        bool operator!=(const Iterator& right) const{
            return cur_ != right.cur_;
        }
    };
    Iterator begin() const { return head_; }
    Iterator end() const { return tail_; }
};

#endif // THINGSLIST_H
