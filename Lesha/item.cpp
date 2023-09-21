#include "item.h"
Item::Item() :
    name("default"),
    price(0),
    capacity(1)
{}

Item::Item(const std::string& name, int price, int capacity) : Item() {
    setName(name);
    setPrice(price);
    setCapacity(capacity);
}
Item::Item(const Item& parent) {
    name = parent.name;
    price = parent.price;
    capacity = parent.capacity;
}
Item::~Item() {}
std::string Item::getName() const {
    return name;
}
int Item::getPrice() const {
    return price;
}
int Item::getCapacity() const {
    return this->capacity;
}
void Item::setName(const std::string& name) {
    if (name != "")
    {
        this->name = name;
    }
}
void Item::setPrice(int price) {
    if (price >= 0)
    {
        this->price = price;
    }
}
void Item::setCapacity(int capacity) {
    if (capacity > 0)
    {
        this->capacity = capacity;
    }
}
std::ostream& operator<<(std::ostream& out,const Item& obj) {
    std::string type = obj.identify();
    return out << "class: " << type << " name: "
        << obj.getName() << " price: " << obj.getPrice()
        << " capacity: " << obj.getCapacity() << "\n";
}
bool Item::operator!=(const Item& right) {
    return (getName() != right.getName() or
        getPrice() != right.getPrice() or
        getCapacity() != right.getCapacity());
}
bool Item::operator==(const Item& right) {
    return !(*this != right);
}

std::string Item::identify() const
{

    return "Item";
}

