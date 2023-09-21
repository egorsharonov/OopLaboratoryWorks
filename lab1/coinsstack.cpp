#include "coinsstack.h"

CoinsStack::CoinsStack(std::string name, int price) :
    Object(name, price)
{
    Object::setVolume(calculateVolume(price));
}
CoinsStack::CoinsStack(const CoinsStack& copy) :
    Object(copy.getName(), copy.getPrice())
{
    Object::setVolume(calculateVolume(copy.getPrice()));
}
void CoinsStack::setPrice(int price){
    Object::setVolume(calculateVolume(price));
    Object::setPrice(price);
}
void CoinsStack::setVolume(int volume){
}
Object::id CoinsStack::identify() const{
    return Object::id::coinsStack;
}
int CoinsStack::calculateVolume(int price)
{
    int Volume = 0;
    for (auto& i : {100, 50, 10, 5, 1})
    {
        Volume += price / i;
        price %= i;
    }
    return Volume;
}

CoinsStack::~CoinsStack(){

}
