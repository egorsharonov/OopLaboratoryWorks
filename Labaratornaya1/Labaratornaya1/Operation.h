#pragma once
#include "ComplexNumber.h"
class Operation :
    public ComplexNumber
{
private:
    int operandsNum;

protected:
    bool checkArifmeticOperation(const string&) override;
public:
    Operation();
    Operation(ComplexNumber*);
    Operation(const Operation&);
    Operation(double, double, const string&, int);
    string getId() const override;
    int getNum() const;
    void setNum(int);
    void setArifmeticOperation(const string&) override;
};

