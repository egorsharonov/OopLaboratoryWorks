#include "coins.h"

Coins::Coins(std::string name, int price) : Item(name, price)
{
    Item::setCapacity(calculateCapacity(price));
}
Coins::Coins(const Coins& copy) : Item(copy.getName(), copy.getPrice())
{
    Item::setCapacity(calculateCapacity(copy.getPrice()));
}
Coins::~Coins(){}
void Coins::setPrice(int price){
    Item::setCapacity(calculateCapacity(price));
    Item::setPrice(price);
}
void Coins::setCapacity(int capacity){
}
std::string Coins::identify() const{
    return "Coins";
}
int Coins::calculateCapacity(int price)
{
    int Capacity = 0;
    for (auto& i : {100, 50, 10, 5, 1})
    {
        Capacity += price / i;
        price %= i;
    }
    return Capacity;
}
