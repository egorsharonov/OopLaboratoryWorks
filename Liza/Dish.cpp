#include "Dish.h"
Dish::Dish()
{
    amount = 0;
    name = unit = "default";
}
Dish::Dish(string nameValue, string unitValue, int amountValue)
{
    setName(nameValue);
    setUnit(unitValue);
    setAmount(amountValue);
}
Dish::Dish(const Dish& other)
{
    this->name = other.getName();
    this->unit = other.getUnit();
    this->amount = other.getAmount();
}
Dish::~Dish() {

}
string Dish::getName() const
{
    return name;
}
string Dish::getUnit() const
{
    return unit;
}
int Dish::getAmount() const
{
    return amount;
}
void Dish::setName(const string& nameValue)
{
    name = nameValue;
}
void Dish::setUnit(const string& unitValue)
{
    unit = unitValue;
}
void Dish::setAmount(int amountValue)
{
    if (amountValue > 0)
        amount = amountValue;
    if (amountValue < 0)
        amount = 0;
}
void Dish::print() const
{
    cout << name << " " << unit << " " << amount << endl;
}
bool Dish::operator!=(const Dish& right)
{
    return (getAmount() != right.getAmount() or
        getName() != right.getName() or
        getUnit() != right.getUnit());
}

Dish::id Dish::identity() const
{
    return id::dish;
}
