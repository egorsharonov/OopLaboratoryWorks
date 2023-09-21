#include "Array.h"
#include "Journal.h"
#include "Employee.h"
#include<fstream>
using namespace std;
MyArray::MyArray() {
	count = 0;
	allocated = 0;
	flask = 0;
	items = NULL;
}
MyArray::MyArray(const MyArray& copied) {
	count = copied.count;
	flask = copied.flask;
	items = new Note[count];
	allocated = count;
	for (int i = 0; i < count; i++) {
		items[i] = copied.items[i];
	}
}
MyArray::~MyArray() {
	removeAll();
}
void MyArray::grow() {
	Note* tmp = new Note[count + 1];
	for (int i = 0; i < count; i++) {
		tmp[i] = items[i];
	}
	delete[] items;
	items = tmp;
	allocated += 1;
}
void MyArray::add(const JournalItem& obj) {
	if (count >= allocated) {
		grow();
	}
	Note temp = Note(obj);
	items[count++] = temp;
	flask = flaskDiff(flask, obj.getCoffeeDiff());
}
void MyArray::add(const Note& obj) {
	if (count >= allocated) {
		grow();
	}
	items[count++] = obj;
	flask = flaskDiff(flask, obj.getCoffeeDiff());
}
void MyArray::remove(const int& i) {
	for (int j = i; j < count - 1; j++) {
		items[j] = items[j + 1];
	}
	count--;
}
void MyArray::removeAll() {
	if (allocated) {
		delete[] items;
	}
	count = 0;
}
Note MyArray::get(const int& i) {
	if ((i >= 0) && (i <= count)) {
		return items[i];
	}
}
int MyArray::size() const {
	return count;
}
double MyArray::flaskDiff(double flask, double coffeeDiff) {
	flask += coffeeDiff;
	return flask;
}
bool MyArray::checkArray() const {
	for (int i = 0; i < count; i++) {
		if (flask < 0 || flask > MAX_FLASK) return false;
	}
	return true;
}
void MyArray::printInFile(const string& file) const {
	ofstream fout;
	fout.open(file);
	for (int i = 0; i < count; i++) {
		Employee tmp = items[i].getEmployee();
		fout << items[i].getHours() << endl << items[i].getMinutes() << endl <<
			items[i].getCoffeeDiff() << endl << tmp.getLastName() << endl <<
			tmp.getFirstName() << endl << tmp.getFatherName() << endl <<
			tmp.getDegree() << endl << tmp.getPost() << endl << items[i].getCurrCoffee()
			<< endl << items[i].getNoteHours() << endl << items[i].getNoteMinutes();
		if (i != count - 1) {
			fout << endl;
		}
	}
}
void MyArray::getFromFile(const string& file) {
	ifstream fin;
	fin.open(file);
	while(!fin.eof()) {
		int tmpHours, tmpMinutes, tmpNoteHours, tmpNoteMinutes;
		double tmpCofeeDiff, tmpCurrCoffee;
		string tmpLastName, tmpFirstName, tmpFatherName, tmpDegree, tmpPost;
		fin >> tmpHours >> tmpMinutes >> tmpCofeeDiff >> tmpLastName >> 
			tmpFirstName >> tmpFatherName >> tmpDegree >> tmpPost >> tmpNoteHours
			>> tmpNoteMinutes >> tmpCurrCoffee;
		Note item = Note(tmpHours, tmpMinutes, Employee(tmpFirstName,
			tmpLastName, tmpFatherName, tmpPost, tmpDegree), tmpCofeeDiff, 
			tmpCurrCoffee, tmpNoteHours, tmpNoteMinutes);
		add(item);
	}
}
bool MyArray::same(const MyArray& obj) {
	if (obj.count != this->count) {
		return false;
	}
	else {
		for (int i = 0; i < obj.count; i++) {
			Note tmp1 = obj.items[i], tmp2 = this->items[i];
			Employee temp1 = tmp1.getEmployee(), temp2 = tmp2.getEmployee();
			if (!(tmp1.getHours() == tmp2.getHours() &&
				tmp1.getMinutes() == tmp2.getMinutes() &&
				tmp1.getCoffeeDiff() == tmp2.getCoffeeDiff() &&
				temp1.getFirstName() == temp2.getFirstName() &&
				temp1.getLastName() == temp2.getLastName() &&
				temp1.getFatherName() == temp2.getFatherName() &&
				temp1.getDegree() == temp2.getDegree() &&
				temp1.getPost() == temp2.getPost() && 
				tmp1.getCurrCoffee() == tmp2.getCurrCoffee() &&
				tmp1.getNoteMinutes() == tmp2.getNoteMinutes() &&
				tmp1.getNoteHours() == tmp2.getNoteHours())) return false;
		}
	}
	return true;
}