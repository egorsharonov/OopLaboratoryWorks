#include "DishQueue.h"
#include <fstream>
DishQueue::Iterator DishQueue::Iterator::operator++(int)
{
    auto temp = cur;
    cur = cur->pNext;
    return temp;
}
DishQueue::Iterator DishQueue::Iterator::operator++()
{
    cur = cur->pNext;
    return cur;
}
DishQueue::Iterator DishQueue::Iterator::operator--(int)
{
    auto temp = cur;
    cur = cur->pPrev;
    return temp;
}
DishQueue::Iterator DishQueue::Iterator::operator--()
{
    cur = cur->pPrev;
    return cur;
}
Dish& DishQueue::Iterator::operator*()
{
    return *(cur->data);
}
bool DishQueue::Iterator::operator==(const DishQueue::Iterator& right)
{
    return cur == right.cur;
}
bool DishQueue::Iterator::operator!=(const DishQueue::Iterator& right)
{
    return cur != right.cur;
}
bool DishQueue::operator==(const DishQueue& right) const
{
    auto leftCur = head;
    auto rightCur = right.head;
    while (leftCur != nullptr and rightCur != nullptr)
    {
        if (*(leftCur->data) != *(rightCur->data))
            return false;
        leftCur = leftCur->pNext;
        rightCur = rightCur->pNext;
    }
    return true;
}
bool DishQueue::operator!=(const DishQueue& right) const
{
    return not ((*this) == right);
}
DishQueue::Node::Node(Dish* data = new Dish(),
    Node* pPrev = nullptr, Node* pNext = nullptr)
{
    this->data = data;
    this->pNext = pNext;
    this->pPrev = pPrev;
}
DishQueue::DishQueue()
{
    size = 0;
    head = tail = nullptr;
}
DishQueue::DishQueue(const DishQueue& copy)
{
    size = 0;
    auto copyHead = copy.head;
    while (copyHead != nullptr)
    {
        if (copyHead->data->identity() == Dish::id::dish) {
            pushBack(new Dish(*(copyHead->data)));
        }
        else {
            pushBack(new Operation(*((Operation*)copyHead->data)));
        }
        copyHead = copyHead->pNext;
    }
}
DishQueue::~DishQueue()
{
    clear();
}
void DishQueue::pushBack(Dish* data)
{
    if (head == nullptr)
    {
        head = tail = new Node(data);
    }
    else
    {
        tail->pNext = new Node(data, tail);
        tail = tail->pNext;
    }
    ++size;
}
void DishQueue::popFront()
{
    if (head != nullptr)
    {
        auto temp = head;
        auto value = head->data;
        if (tail == head) tail = nullptr;
        head = head->pNext;
        if(value) delete value;
        delete temp;
        size--;
    }

}
void DishQueue::clear()
{
    while (size > 0)
        popFront();
}
void DishQueue::write(std::string path) const
{
    std::ofstream fout(path);
    for (auto cur = head; cur != nullptr; cur = cur->pNext)
    {
        Dish::id id_ = cur->data->identity();
        fout << int(id_) << " ";
        if (id_ == Dish::id::dish) {
            Dish& tmp = *(cur->data);
            fout << tmp.getName() << " " << tmp.getUnit() << " "
                 << tmp.getAmount() << " "<<endl;
        }
        else
        {
            Operation& tmp = *((Operation*)cur->data);
            fout << tmp.getName() << " " << tmp.getUnit() << " "
                << tmp.getAmount() << " " << tmp.getAction() << " "
                << tmp.getDuration() << " "<<endl;
        }


    }
    fout.close();
}
void DishQueue::read(std::string path)
{
    clear();
    std::ifstream fin(path);
    Dish::id id_;
    int i;
    while (fin >> i)
    {
        string name, unit;
        int amount, duration, action;
        id_ = Dish::id(i);
        if (id_ == Dish::id::dish) {
            fin >> name >> unit >> amount;
            pushBack(new Dish(name, unit, amount));
        }
        else
        {
            fin >> name >> unit >> amount
                >> action >> duration;
            pushBack(new Operation(name, unit, amount, Operation::actions(action), duration));
        }
    }
    fin.close();
}
int DishQueue::getSize() const
{
    return size;
}
/*void DishQueue::emplace(Node &&value)
{
    if (lst.end() == nullptr)
    {
        lst.end() = front_ = std::make_shared<QueueElement>(std::move(lst), nullptr);
    } else {
        lst.end()->next() = std::make_shared<QueueElement>(std::move(lst), nullptr);
        lst.end() = lst.end().next();
    }
    ++size_;
}*/
