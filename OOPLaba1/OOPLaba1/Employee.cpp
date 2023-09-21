#include "Employee.h"
Employee::Employee() {
	string firstName;
	string lastName;
	string fatherName;
	string post;
	string degree;
}
Employee::Employee(const string& firstName, const string& lastName, 
	const string& fatherName, const string& post, const string& degree) {
	if (!(checkValue(firstName) || checkValue(lastName) || checkValue(post) 
		|| checkValue(fatherName) || checkValue(degree))) {
		setFirstName(firstName);
		setLastName(lastName);
		setFatherName(fatherName);
		setPost(post);
		setDegree(degree);
	}
}
Employee::Employee(const Employee& copied) {
	setFirstName(copied.firstName);
	setLastName(copied.lastName);
	setFatherName(copied.fatherName);
	setPost(copied.post);
	setDegree(copied.degree);
};
bool Employee::checkValue(const string& value) {
	if (value.empty()) {
		return true;
	}
	else {
		return false;
	}
}
void Employee::setFirstName(const string& firstName) {

	this->firstName = firstName;
}
void Employee::setLastName(const string& lastName) {
	this->lastName = lastName;
}
void Employee::setFatherName(const string& fatherName) {
	this->fatherName = fatherName;
}
void Employee::setPost(const string& post) {
	this->post = post;
}
void Employee::setDegree(const string& degree) {
	this->degree = degree;
}
string Employee::getFirstName() const {
	return firstName;
}
string Employee::getLastName() const {
	return lastName;
}
string Employee::getFatherName() const {
	return fatherName;
}
string Employee::getPost() const {
	return post;
}
string Employee::getDegree() const {
	return degree;
}