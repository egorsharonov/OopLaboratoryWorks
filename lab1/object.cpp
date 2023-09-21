#include "object.h"
Object::Object() {
    name_ = "default";
    price_ = 0;
    volume_ = 1;

}
Object::Object(const std::string& name, int price, int volume) :
    Object() {
    setName(name);
    setPrice(price);
    setVolume(volume);
}
Object::Object(const Object& parent) {
    name_ = parent.name_;
    price_ = parent.price_;
    volume_ = parent.volume_;
}
Object::~Object() {}
std::string Object::getName() const {
    return name_;
}
int Object::getPrice() const {
    return price_;
}
int Object::getVolume() const {
    return volume_;
}
void Object::setName(const std::string& name) {
    if (name != "")
    {
        this->name_ = name;
    }
}
void Object::setPrice(int price) {
    if (price >= 0)
    {
        this->price_ = price;
    }
}
void Object::setVolume(int volume) {
    if (volume > 0)
    {
        this->volume_ = volume;
    }
}
std::ostream& operator<<(std::ostream& out,const Object& obj) {
    std::string type = (obj.identify()==Object::id::object)?
        "Object":"CoinsStack";


    return out << "class: " << type << " name: "
        << obj.getName() << " price: " << obj.getPrice()
        << " volume: " << obj.getVolume() << "\n";
}
bool Object::operator!=(const Object& right) {
    return (getName() != right.getName() or
        getPrice() != right.getPrice() or
        getVolume() != right.getVolume());
}
bool Object::operator==(const Object& right) {
    return !(*this != right);
}

Object::id Object::identify() const
{

    return Object::id::object;
}

