#include "Operation.h"
Operation::Operation() : Dish()
{
    action = actions::none;
    duration = 0;
}
Operation::Operation(string nameValue, string unitValue, int amountValue, actions actionValue, int durationValue) : Dish(nameValue, unitValue, amountValue)
{
    setAction(actionValue);
    setDuration(durationValue);
}
Operation::Operation(const Operation& other) : Dish(other.getName(), other.getUnit(), other.getAmount())
{
    setAction(other.getAction());
    setDuration(other.getDuration());
}
Operation::~Operation()
{

}
int Operation::getDuration() const
{
    return duration;
}

Operation::actions Operation::getAction() const
{
    return action;
}

void Operation::setAction(actions actionValue)
{
    action = actionValue;
}

void Operation::setDuration(int durationValue)
{
    duration = durationValue;
}

void Operation::print() const
{
    cout << getName() << " " << getAmount() << " " << getUnit() << " " << getAction() << " " << getDuration() << endl;
}

bool Operation::operator!=(const Dish& tempRight)
{
    Operation& right = *(Operation*)&tempRight;
    return (getAmount() != right.getAmount() or
        getName() != right.getName() or
        getUnit() != right.getUnit() or
        getAction() != right.getAction() or
        getDuration() != right.getDuration());
}

Dish::id Operation::identity() const
{
    return id::operation;
}


