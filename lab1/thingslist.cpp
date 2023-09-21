#include "thingslist.h"
#include <fstream>

const ThingsList::Iterator ThingsList::Iterator::operator++ (int) {
    auto temp = cur_;
    cur_ = cur_->pNext_;
    return temp;
}

ThingsList::Iterator& ThingsList::Iterator::operator++ () {
    cur_ = cur_->pNext_;
    return (*this);
}

const ThingsList::Iterator ThingsList::Iterator::operator-- (int) {
    auto temp = cur_;
    cur_ = cur_->pPrev_;
    return temp;
}

ThingsList::Iterator& ThingsList::Iterator::operator-- () {
    cur_ = cur_->pPrev_;
    return *this;
}

Object& ThingsList::Iterator::operator*() const{
    return *(cur_->data_);
}
bool ThingsList::Iterator::operator==(
    const ThingsList::Iterator& right) const{
    return *cur_->data_ == *right.cur_->data_;
}

bool ThingsList::Iterator::operator!=(
    const ThingsList::Iterator& right) const{
    return cur_ != right.cur_;
}

bool ThingsList::operator==(const ThingsList& right) const {
    auto leftCur = begin();
    auto rightCur = right.begin();
    if (size_ != right.size_) return false;
    while (leftCur != nullptr and rightCur != nullptr) {
        if (*leftCur++ != *rightCur++) return false;
    }
    return true;
}

bool ThingsList::operator!=(const ThingsList& right) const {
    return not (*this == right);
}

ThingsList::Node::Node(const Object& data,
    Node* pPrev = nullptr, Node* pNext = nullptr) {
    data_ =  (data.identify() == Object::id::object) ?
                new Object(data) : new CoinsStack(*((CoinsStack*)&data));
    pNext_ = pNext;
    pPrev_ = pPrev;
}

void ThingsList::pushBack(const Object& rowData) {

    bool sortNeeded = head_!=nullptr;
    push(rowData);
    if (sortNeeded) sort();

}
void ThingsList::push(const Object& data){
    if (!head_) {
        head_ = tail_ = new Node(data);
    }
    else {
        tail_->pNext_ = new Node(data, tail_);
        tail_ = tail_->pNext_;
    }
    ++size_;
}
int ThingsList::sort(){
    int position = size_-1;
    auto prev = tail_->pPrev_, cur = tail_;
    auto unitCost=[](Object data)->double{
        return data.getPrice()/data.getVolume();};
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
void ThingsList::insert(int pos,const Object& data) {
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

ThingsList::ThingsList() {
    size_ = 0;
    head_ = tail_ = nullptr;
}

ThingsList::ThingsList(const ThingsList& copy) {
    size_ = 0;
    for (auto copyHead = copy.begin(); copyHead != nullptr; ++copyHead) {
        pushBack(*copyHead);
    }
}

ThingsList::~ThingsList() {
    clear();
}

void ThingsList::del(int pos) {
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

void ThingsList::clear() {
    while (size_) del();
}

void ThingsList::write(const std::string& path) const{

    std::ofstream fout(path);
    for (auto cur = begin(); cur != nullptr; ++cur) {
        fout <<  (*cur).identify() << " " << (*cur).getName() << " ";
        fout << (*cur).getVolume() << " " << (*cur).getPrice() << "\n";
    }
    fout.close();
}

void ThingsList::read(const std::string& path) {
    clear();
    std::ifstream fin(path);
    int id;
    while (fin >> id) {
        std::string temp, name;
        double price, volume;
        fin >> name >> volume >> price;
        Object* tempObj = (Object::id(id) == Object::id::object) ?
            new Object(name, price, volume) : new CoinsStack(name, price);
        pushBack(*tempObj);
    }
    fin.close();
}

int ThingsList::getSize() const {
    return size_;
}
