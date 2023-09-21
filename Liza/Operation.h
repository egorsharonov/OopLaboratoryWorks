#ifndef OPERATION_H
#define OPERATION_H

#include "Dish.h"
class Operation : public Dish
{
public:
    enum actions {
        cut,
        pack,
        fry,
        put,
        none
    };
    Operation();
    Operation(string, string = "", int = 0, actions = actions::none, int = 0);
    Operation(const Operation&);
    ~Operation();
    int getDuration() const;
    actions getAction() const;
    void setAction(actions);
    void setDuration(int);
    void print() const override;
    bool operator!=(const Dish&) override;
    id identity() const override;
private:
    actions action;
    int duration;
};

#endif // OPERATION_H
