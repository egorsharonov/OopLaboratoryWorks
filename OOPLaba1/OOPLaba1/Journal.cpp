#include "Journal.h"
JournalItem::JournalItem() {
	hours = 0;
	minutes = 0;
	employee = Employee();
	coffeeDiff = 0;
}S
JournalItem::JournalItem(int hours, int minutes, const Employee& employee,
	const double& coffeeDiff) {
	if (hours < 0 || hours > 23) hours = 0;
	else this->hours = hours;
	if (minutes < 0 || minutes > 59) minutes = 0;
	else this->minutes = minutes;
	this->employee = employee;
	this->coffeeDiff = coffeeDiff;
}
JournalItem::JournalItem(const JournalItem& copied) {
	hours = copied.hours;
	minutes = copied.minutes;
	employee = copied.employee;
	coffeeDiff = copied.coffeeDiff;
}
void JournalItem::setHours(int hours) {
	this->hours = hours;
}
void JournalItem::setMinutes(int minutes) {
	this->minutes = minutes;
}
void JournalItem::setEmployee(Employee employee) {
	this->employee = employee;
}
void JournalItem::setCoffeeDiff(double coffeeDiff) {
	this->coffeeDiff = coffeeDiff;
}
int JournalItem::getHours() const {
	return hours;
}
int JournalItem::getMinutes() const {
	return minutes;
}
Employee JournalItem::getEmployee() const {
	return employee;
}
double JournalItem::getCoffeeDiff() const {
	return coffeeDiff;
}
JournalItem::id JournalItem::identify() const {
	return id::journalItem;
}