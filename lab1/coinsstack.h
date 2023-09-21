#ifndef COINSSTACK_H
#define COINSSTACK_H

#include "object.h"

class CoinsStack : public Object
{
public:
    CoinsStack(const CoinsStack&);
    CoinsStack(std::string = "CoinsStack", int = 0);
    ~CoinsStack() override;
    void setPrice(int) override;
    void setVolume(int) override;
    Object::id identify() const override;
private:
    int calculateVolume(int price);
};

#endif // COINSSTACK_H
