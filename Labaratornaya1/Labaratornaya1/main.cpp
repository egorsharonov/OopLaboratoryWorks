#include "Calculator.h"

int main2() {
	std::string path = "text.txt";
	ComplexNumber n1;
	Operation o1;
	Calculator calc;
	calc.push(n1);
	calc.push(o1);
	calc.writeInFile(path);

	Calculator calc2;
	calc.getFromFile(path);
	std::cout << calc.equals(calc2);
	return 0;
}