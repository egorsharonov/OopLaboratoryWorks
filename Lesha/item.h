#ifndef ITEM_H
#define ITEM_H


#include <iostream>
class Item
{
    std::string name;
    int price;
    int capacity;
public:
    Item();
    Item(const std::string& name, int price = 0, int capacity = 1);
    Item(const Item&);
    virtual ~Item();
    std::string getName() const;
    int getPrice() const;
    int getCapacity() const;
    void setName(const std::string&);
    virtual void setPrice(int);
    virtual void setCapacity(int);
    bool operator==(const Item& right);
    bool operator!=(const Item& right);
    virtual std::string identify() const;
    friend std::ostream& operator<<(std::ostream&, const Item&);
};

#endif // ITEM_H
