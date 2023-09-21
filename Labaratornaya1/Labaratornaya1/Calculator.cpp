#include "Calculator.h"
#include <iomanip>
#include<fstream>
Calculator::Calculator() {
	count=0;
	allocated = 0;
	stackPtr = nullptr;
}

Calculator::Calculator(const Calculator& otherStack) {
	removeAll();
	count = otherStack.getStackSize();
	if (allocated < count) {
		allocated = count;
		delete[] stackPtr;
		stackPtr = new ComplexNumber * [count];
	}
	
	for (int i = 0; i < count; i++)
		if (otherStack.stackPtr[i]->getId() == "ComplexNumber") {
			stackPtr[i] = new ComplexNumber(*otherStack.stackPtr[i]);
		}
		else {
			stackPtr[i] = new Operation(*(Operation*)(otherStack.stackPtr[i]));
		}
		
}

Calculator::~Calculator() {
	removeAll();
}

void Calculator::push(const ComplexNumber& value){	
	if (count >= allocated) {
		grow();
	}
	stackPtr[count++] = (value.getId()=="ComplexNumber") ? new ComplexNumber(value) : new Operation(*((Operation*)&value));
}

ComplexNumber Calculator::pop() {
	ComplexNumber num = *(stackPtr[count-1]);
	if (count > 0) {
		delete stackPtr[--count];
	}
	return num;
}

int Calculator::getStackSize() const{
	return count;
}

ComplexNumber** Calculator::getPtr() const{
	return stackPtr;
}

void Calculator::grow() {
	if (!allocated) ++allocated;
	ComplexNumber** tmp = new ComplexNumber*[allocated * 2];
	for (int i = 0; i < allocated*2; ++i) {
		tmp[i] = nullptr;
	}
	for (auto i = 0; i < count; i++) {
		if (stackPtr[i]->getId() == "ComplexNumber") {
			tmp[i] = new ComplexNumber(*stackPtr[i]);
		}
		else {
			tmp[i] = new Operation(*(Operation*)stackPtr[i]);
		}
		delete stackPtr[i];
	}
	delete[] stackPtr;
	stackPtr = tmp;
	allocated *= 2;
}

ComplexNumber Calculator::getLastValue() const {
	return *(stackPtr[count-1]);
}

ComplexNumber Calculator::getFirstValue() const{
	return *(stackPtr[0]);
}

void Calculator::removeAll() {
	if (allocated) {
		int size = count;
		for (int i = 0; i < size; i++) {
			pop();
		}
	}
	count = 0;
}

bool Calculator::equals(const Calculator& obj) const{
	if (obj.count != this->count) {
		return false;
	}
	else {
		for (int i = 0; i < obj.count; i++) {
			ComplexNumber* num1 = obj.stackPtr[i];
			ComplexNumber* num2 = this->stackPtr[i];
			if (!(num1->getId()==num2->getId() && num1->getActualPart() == num2->getActualPart()
				&& num1->getImaginaryPart() == num2->getImaginaryPart()
				&& num1->getArifmeticOperation().compare(num2->getArifmeticOperation()) == 0)) {
				return false;
			}
			if (num1->getId() == "Operation" && ((Operation*)num1)->getNum() != ((Operation*)num2)->getNum())
				return false;
		}
	}
	return true;
}

void Calculator::writeInFile(const string& path) {
	ofstream fout;
	fout.open(path);
	for (int i = 0; i < count; i++) {
		fout << stackPtr[i]->getId() << endl << stackPtr[i]->getActualPart() << endl << stackPtr[i]->getImaginaryPart() << endl <<
			stackPtr[i]->getArifmeticOperation();
		if (stackPtr[i]->getId() == "Operation") {
			fout << endl << ((Operation*)stackPtr[i])->getNum();
		}
		if (i != count - 1) {
			fout << endl;
		}
	}
}

void Calculator::getFromFile(const string& path) {
	ifstream fin;
	fin.open(path);
	while (!fin.eof()) {
		double actPart;
		double imgPart;
		string operation, id;
		int number;
		fin >> id >> actPart >> imgPart >> operation;
		if (id == "Operation")
		{
			fin >> number;
			push(Operation(actPart, imgPart, operation, number));
		}
		else {
			ComplexNumber num = ComplexNumber(actPart, imgPart, operation);
			push(num);
		}
	}
}

ComplexNumber* Calculator::plus(const ComplexNumber& num1, const ComplexNumber& num2) {
	if (num2.getId() == "ComplexNumber") {
		ComplexNumber* ans = new ComplexNumber(num1.getActualPart() + num2.getActualPart(),
			num1.getImaginaryPart() + num2.getImaginaryPart(),
			num2.getArifmeticOperation());
		return ans;
	}
	else {
		Operation* ans = new Operation(num1.getActualPart() + num2.getActualPart(),
			num1.getImaginaryPart() + num2.getImaginaryPart(),
			num2.getArifmeticOperation(),((Operation*)&num2)->getNum());
		return ans;
	}
	
}

ComplexNumber* Calculator::minus(const ComplexNumber& num1, const ComplexNumber& num2) {
	if (num2.getId() == "ComplexNumber") {
		ComplexNumber* ans = new ComplexNumber(num1.getActualPart() - num2.getActualPart(),
			num1.getImaginaryPart() - num2.getImaginaryPart(),
			num2.getArifmeticOperation());
		return ans;
	}
	else {
		Operation* ans = new Operation(num1.getActualPart() - num2.getActualPart(),
			num1.getImaginaryPart() - num2.getImaginaryPart(),
			num2.getArifmeticOperation(), ((Operation*)&num2)->getNum());
		return ans;
	}
	
}

ComplexNumber* Calculator::multiply(const ComplexNumber& num1, const ComplexNumber& num2) {
	if (num2.getId() == "ComplexNumber") {
		ComplexNumber* ans = new ComplexNumber(num1.getActualPart() * num2.getActualPart()
			- num1.getImaginaryPart() * num2.getImaginaryPart(),
			num1.getActualPart() * num2.getImaginaryPart() + num2.getActualPart() * num1.getImaginaryPart(),
			num2.getArifmeticOperation());
		return ans;
	}
	else {
		Operation* ans = new Operation(num1.getActualPart() * num2.getActualPart()
			- num1.getImaginaryPart() * num2.getImaginaryPart(),
			num1.getActualPart() * num2.getImaginaryPart() + num2.getActualPart() * num1.getImaginaryPart(),
			num2.getArifmeticOperation(), ((Operation*)&num2)->getNum());
		return ans;
	}
	
}

ComplexNumber* Calculator::division(const ComplexNumber& num1, const ComplexNumber& num2) {
	if (num2.getId() == "ComplexNumber") {
		double del = num2.getActualPart() * num2.getActualPart() + num2.getImaginaryPart() * num2.getImaginaryPart();
		ComplexNumber* ans = new ComplexNumber((num1.getActualPart() * num2.getActualPart()
			+ num1.getImaginaryPart() * num2.getImaginaryPart()) / del,
			(num2.getActualPart() * num1.getImaginaryPart() - num1.getActualPart() * num2.getImaginaryPart()) / del,
			num2.getArifmeticOperation());
		return ans;
	}
	else {
		double del = num2.getActualPart() * num2.getActualPart() + num2.getImaginaryPart() * num2.getImaginaryPart();
		Operation* ans = new Operation((num1.getActualPart() * num2.getActualPart()
			+ num1.getImaginaryPart() * num2.getImaginaryPart()) / del,
			(num2.getActualPart() * num1.getImaginaryPart() - num1.getActualPart() * num2.getImaginaryPart()) / del,
			num2.getArifmeticOperation(), ((Operation*)&num2)->getNum());
		return ans;
	}
	
}

ComplexNumber Calculator::getAnswer() {
	bool flag = false;
	for (int i = 0; i < count; i++) {
		if (stackPtr[i]->getArifmeticOperation().compare("=") == 0) {
			flag = true;
		}
	}
	ComplexNumber** newstackPtr = new ComplexNumber*[count];
	if (flag) {
		int j = 0;
		for (int i = 0; i < count; i++) {
			if (priority(stackPtr[i]->getArifmeticOperation()) == 2) {
				newstackPtr[j++] = stackPtr[i];
			}
		}
		for (int i = 0; i < count; i++) {
			if (priority(stackPtr[i]->getArifmeticOperation()) == 1) {
				newstackPtr[j++] = stackPtr[i];
			}
		}
		for (int i = 0; i < count; i++) {
			if (priority(stackPtr[i]->getArifmeticOperation()) == 3) {
				newstackPtr[j++] = stackPtr[i];
			}
		}
		for (int i = 0; i < count; i++) {
			if (priority(stackPtr[i]->getArifmeticOperation()) == 4) {
				newstackPtr[j++] = stackPtr[i];
			}
		}
		for (int i = j - 1; i >= 0; i--)
			cout << i + 1 << " | " << newstackPtr[i]->getActualPart() << " " << newstackPtr[i]->getImaginaryPart() << " " << newstackPtr[i]->getArifmeticOperation() << endl;


		for (int i = 0; i < count ; i++) {
			if (newstackPtr[i]->getArifmeticOperation().compare("*") == 0) {
				if (newstackPtr[i + 1]->getId() == "ComplexNumber") {
					newstackPtr[i + 1] = new ComplexNumber(multiply(*(newstackPtr[i]), *(newstackPtr[i + 1])));
				}
				else {
					newstackPtr[i + 1] = new Operation(multiply(*(newstackPtr[i]), *(newstackPtr[i + 1])));
				}
			} 
			else if (newstackPtr[i]->getArifmeticOperation().compare("/") == 0 ) {
				if (newstackPtr[i + 1]->getId() == "ComplexNumber") {
					newstackPtr[i + 1] = new ComplexNumber(division(*(newstackPtr[i]), *(newstackPtr[i + 1])));
				}
				else {
					newstackPtr[i + 1] = new Operation(division(*(newstackPtr[i]), *(newstackPtr[i + 1])));
				}
			} 
			else if (newstackPtr[i]->getArifmeticOperation().compare("+") == 0 ) {
				if (newstackPtr[i + 1]->getId() == "ComplexNumber") {
					newstackPtr[i + 1] = new ComplexNumber(plus(*(newstackPtr[i]), (*newstackPtr[i + 1])));
				}
				else {
					newstackPtr[i + 1] = new Operation(plus(*(newstackPtr[i]), (*newstackPtr[i + 1])));
				}
			}
			else if (newstackPtr[i]->getArifmeticOperation().compare("-") == 0) {
				if (newstackPtr[i + 1]->getId() == "ComplexNumber") {
					newstackPtr[i + 1] = new ComplexNumber(minus(*(newstackPtr[i]), *(newstackPtr[i + 1])));
				}
				else {
					newstackPtr[i + 1] = new Operation(minus(*(newstackPtr[i]), *(newstackPtr[i + 1])));
				}
			}
			else if (newstackPtr[i]->getArifmeticOperation().compare("R") == 0) {
				if (newstackPtr[i + 1]->getId() == "ComplexNumber") {
					newstackPtr[i + 1] = new ComplexNumber(newstackPtr[i]->getActualPart(), 0, newstackPtr[i + 1]->getArifmeticOperation());
				}
				else {
					newstackPtr[i + 1] = new Operation(newstackPtr[i]->getActualPart(), 0, newstackPtr[i + 1]->getArifmeticOperation(), ((Operation*)newstackPtr[i + 1])->getNum());
				}
			}
			else if (newstackPtr[i]->getArifmeticOperation().compare("I") == 0) {
				if (newstackPtr[i + 1]->getId() == "ComplexNumber") {
					newstackPtr[i + 1] = new ComplexNumber(0, newstackPtr[i]->getImaginaryPart(), newstackPtr[i + 1]->getArifmeticOperation());
				}
				else {
					newstackPtr[i + 1] = new Operation(0, newstackPtr[i]->getImaginaryPart(), newstackPtr[i + 1]->getArifmeticOperation(), ((Operation*)newstackPtr[i + 1])->getNum());
				}
			}
		}
	}
	return  *(newstackPtr[count - 1]);
}

int Calculator::priority(const string& s) {
	if (s.compare("+") == 0 || s.compare("-") == 0) {
		return 1;
	}
	if (s.compare("*") == 0 || s.compare("/") == 0) {
		return 2;
	}
	if (s.compare("R") == 0 || s.compare("I") == 0) {
		return 3;
	}
	if (s.compare("=") == 0) {
		return 4;
	}
	else {
		return 0;
	}
}