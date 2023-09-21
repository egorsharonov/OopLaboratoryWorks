#include "Operation.h"

Operation::Operation() : ComplexNumber()
{
	operandsNum = 2;
}
Operation::Operation(ComplexNumber* other)
{
	(*this) = *(Operation*)other;
}
Operation::Operation(const Operation& other)
{
	setActualPart(other.getActualPart());
	setImaginaryPart(other.getImaginaryPart());
	setArifmeticOperation(other.getArifmeticOperation());
	setNum(other.getNum());
}
bool Operation::checkArifmeticOperation(const string& s) {
	return (s.compare("+") == 0 || s.compare("-") == 0 || s.compare("*") == 0 ||
		s.compare("/") == 0 || s.compare("R") == 0 || s.compare("I") == 0 ||
		s.compare("=") == 0);
}
Operation::Operation(double actualPart, double imaginaryPart,
	const string& arifmeticOperation, int num=2)
{
	setActualPart(actualPart);
	setImaginaryPart(imaginaryPart);
	setArifmeticOperation(arifmeticOperation);
	setNum(num);
}

string Operation::getId() const
{
	return "Operation";
}

int Operation::getNum() const
{
	return operandsNum;
}

void Operation::setNum(int num)
{
	if (num > 0) {
		operandsNum = num;
	}
}

void Operation::setArifmeticOperation(const string& operation)
{
	if (checkArifmeticOperation(operation)) {
		setOper(operation);
	}
}
