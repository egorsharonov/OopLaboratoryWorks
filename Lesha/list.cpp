#include "list.h"
#include <fstream>

bool List::operator==(const List& right) const {
    auto leftCur = begin();
    auto rightCur = right.begin();
    if (size_ != right.size_) return false;
    while (leftCur != nullptr and rightCur != nullptr) {
        if (*leftCur++ != *rightCur++) return false;
    }
    return true;
}

bool List::operator!=(const List& right) const {
    return not (*this == right);
}

List::Node::Node(const Item& data,
    Node* pPrev = nullptr, Node* pNext = nullptr) {
    data_ =  (data.identify() == "Item") ?
                new Item(data) : new Coins(*((Coins*)&data));
    pNext_ = pNext;
    pPrev_ = pPrev;
}

void List::pushBack(const Item& data) {

    bool sortNeeded = head_!=nullptr;
    push(data);
    if (sortNeeded) sort();

}
void List::push(const Item& data){
    if (!head_) {
        head_ = tail_ = new Node(data);
    }
    else {
        tail_->pNext_ = new Node(data, tail_);
        tail_ = tail_->pNext_;
    }
    ++size_;
}
int List::sort(){
    int position = size_-1;
    auto prev = tail_->pPrev_, cur = tail_;
    auto unitCost=[](Item data)->double{
        return data.getPrice()/data.getCapacity();};
    double curUnitCost = unitCost(*tail_->data_);
    double prevUnitCost = unitCost(*prev->data_);
    while ( curUnitCost > prevUnitCost) {
        --position;
        prev->pNext_ = cur->pNext_;
        if (cur->pNext_) cur->pNext_->pPrev_ = prev;
        cur->pPrev_ = prev->pPrev_;
        if (prev->pPrev_) prev->pPrev_->pNext_ = cur;
        prev->pPrev_ = cur;
        cur->pNext_ = prev;
        if (!prev->pNext_) tail_ = prev;
        if (!cur->pPrev_) {
            head_ = cur;
            break;
        }
        prev = cur->pPrev_;
        curUnitCost = unitCost(*(cur->data_));
        prevUnitCost = unitCost(*(prev->data_));
    }
    return position;
}
void List::insert(int pos,const Item& data) {
    if (pos > size_)
        exit(1);
    if (size_ == pos)
        this->pushBack(data);
    else {
        auto cur = head_;
        for (auto i = 0; i < pos && cur; i++, cur = cur->pNext_);
        auto newNode = new Node(data, cur->pPrev_, cur);
        if (cur->pPrev_) cur->pPrev_->pNext_ = newNode;
        cur->pPrev_ = newNode;
    }
}

List::List() {
    size_ = 0;
    head_ = tail_ = nullptr;
}

List::List(const List& copy) {
    size_ = 0;
    for (auto copyHead = copy.begin(); copyHead != nullptr; ++copyHead) {
        pushBack(*copyHead);
    }
}

List::~List() {
    popAll();
}

void List::del(int pos) {
    if (pos >= size_ or pos < 0)
        exit(1);
    auto cur = head_;
    for (int i = 0; i < pos; i++, cur = cur->pNext_);
    if (cur == head_) {
        head_ = head_->pNext_;
    }
    if (cur == tail_) {
        tail_ = tail_->pPrev_;
    }
    if (cur->pPrev_) cur->pPrev_->pNext_ = cur->pNext_;
    if (cur->pNext_) cur->pNext_->pPrev_ = cur->pPrev_;
    delete cur->data_;
    delete cur;
    size_--;

}

void List::popAll() {
    while (size_) del();
}

void List::write(const std::string& path) const{

    std::ofstream fout(path);
    for (auto cur = begin(); cur != nullptr; ++cur) {
        fout <<  (*cur).identify() << " " << (*cur).getName() << " ";
        fout << (*cur).getCapacity() << " " << (*cur).getPrice() << "\n";
    }
    fout.close();
}

void List::read(const std::string& path) {
    popAll();
    std::ifstream fin(path);
    std::string id;
    while (fin >> id) {
        std::string temp, name;
        double price, capacity;
        fin >> name >> capacity >> price;
        Item* tempObj = (id == "Item") ?
            new Item(name, price, capacity) : new Coins(name, price);
        pushBack(*tempObj);
    }
    fin.close();
}

int List::getSize() const {
    return size_;
}
