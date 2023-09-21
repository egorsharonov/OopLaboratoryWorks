#ifndef DISH_H
#define DISH_H


#include <iostream>
#include <fstream>
using namespace std;
class Dish
{
public:
    enum id {
        dish,
        operation
    };
    Dish();
    Dish(string nameValue, string unitValue, int amountValue);
    Dish(const Dish& other);
    ~Dish();
    string getName() const;
    string getUnit() const;
    int getAmount() const;
    void setName(const string& nameValue);
    void setUnit(const string& unitValue);
    void setAmount(int amountValue);
    virtual void print() const;
    virtual bool operator!=(const Dish&);
    void read(string&);
    void write(string&) const;
    virtual id identity() const;

private:
    string name;
    string unit;
    int amount;
};

#endif // DISH_H
