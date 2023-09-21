#ifndef COINSSTACK_H
#define COINSSTACK_H

#include "item.h"

class Coins : public Item
{
public:
    Coins(const Coins&);
    Coins(std::string = "Coins", int = 0);
    ~Coins() override;
    void setPrice(int) override;
    void setCapacity(int) override;
    std::string identify() const override;
private:
    int calculateCapacity(int price);
};

#endif // COINSSTACK_H
