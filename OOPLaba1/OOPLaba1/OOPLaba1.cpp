#include<iostream>
#include<assert.h>
#include "Note.h"
#include "Array.h"
const string FIRST_NAME = "Степан";
const string LAST_NAME = "Дёмин";
const string FATHER_NAME = "Игоревич";
const string POST = "студент";
const string DEGREE = "Нет";
const int HOURS = 22;
const int MINUTES = 47;
const double COFFEE_DIFF = -0.3;
const int NOTE_HOURS = 23;
const int NOTE_MINUTES = 11;
const double CURR_COFFEE = -0.3;
void printArray(MyArray& obj) {
	for (int i = 0; i < obj.size(); i++) {
		Employee tmp = obj.get(i).getEmployee();
		cout << i + 1 << ") " << obj.get(i).getHours() << " " <<
			obj.get(i).getMinutes() << " " << obj.get(i).getCoffeeDiff() << " " <<
			tmp.getLastName() << " " << tmp.getFirstName() << " " << 
			tmp.getFatherName() << " " << tmp.getDegree() << " " << 
			tmp.getPost() << " " << obj.get(i).getCurrCoffee() << " " <<
			obj.get(i).getNoteHours() << " " << obj.get(i).getNoteMinutes() << endl;
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	Employee employee1 = Employee(FIRST_NAME, LAST_NAME, 
		FATHER_NAME, POST, DEGREE);
	JournalItem item1 = JournalItem(HOURS, MINUTES, employee1, COFFEE_DIFF);
	Employee employee2 = employee1;
	JournalItem item2 = item1;
	assert(employee1.getFirstName() == FIRST_NAME);
	assert(employee1.getLastName() == LAST_NAME);
	assert(employee1.getFatherName() == FATHER_NAME);
	assert(employee1.getPost() == POST);
	assert(employee1.getDegree() == DEGREE);
	assert(employee2.getFirstName() == FIRST_NAME);
	assert(employee2.getLastName() == LAST_NAME);
	assert(employee2.getFatherName() == FATHER_NAME);
	assert(employee2.getPost() == POST);
	assert(employee2.getDegree() == DEGREE);
	assert(item1.getHours() == HOURS);
	assert(item1.getMinutes() == MINUTES);
	assert(item1.getCoffeeDiff() == COFFEE_DIFF);
	assert(item2.getHours() == HOURS);
	assert(item2.getMinutes() == MINUTES);
	assert(item2.getCoffeeDiff() == COFFEE_DIFF);
	Employee employeeDefault = Employee();
	assert(employeeDefault.getFirstName().empty());
	assert(employeeDefault.getLastName().empty());
	assert(employeeDefault.getFatherName().empty());
	assert(employeeDefault.getPost().empty());
	assert(employeeDefault.getDegree().empty());
	JournalItem itemDefault = JournalItem();
	assert(itemDefault.getHours() == 0);
	assert(itemDefault.getMinutes() == 0);
	assert(itemDefault.getCoffeeDiff() == 0);

	MyArray array1, array3;
	array1.add(item1);
	assert(array1.checkArray() == false);
	MyArray array2 = array1;
	assert(array1.same(array2) == true);
	array2.remove(0);
	assert(array1.same(array2) == false);
	array1.printInFile("file1.txt");
	array3.getFromFile("file1.txt");
	assert(array1.same(array3) == true);
	assert(array1.size() == 1);
	array1.add(item1);
	printArray(array1);
	assert(array1.size() == 2);
	array1.remove(1);
	assert(array1.size() == 1);
	array2.removeAll();
	assert(array2.size() == 0);

	Note item3 = Note(HOURS, MINUTES, employee1, COFFEE_DIFF,
		CURR_COFFEE, NOTE_HOURS, NOTE_MINUTES);
	Note item4 = item3;
	MyArray array4, array6;
	array4.add(item3);
	assert(array4.checkArray() == false);
	MyArray array5 = array4;
	assert(array4.same(array5) == true);
	array5.remove(0);
	assert(array4.same(array5) == false);
	array4.printInFile("file2.txt");
	array6.add(item3);
	assert(array4.same(array6) == true);
	assert(array4.size() == 1);
	array4.add(item3);
	printArray(array4);
	assert(array4.size() == 2);
	array4.remove(1);
	assert(array4.size() == 1);
	array5.removeAll();
	assert(array5.size() == 0);
	cout << "Tecтирование прошло успешно" << endl;
	system("pause");
}