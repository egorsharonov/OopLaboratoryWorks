#include "Note.h"
Note::Note() : JournalItem() {
	currCoffee = 0;
	noteHours = 0;
	noteMinutes = 0;
}
Note::Note(int hours, int minutes, const Employee& employee,
	const double& coffeeDiff, const double& currCoffee,
	const int& noteHours, const int& noteMinutes) :
	JournalItem(hours, minutes, employee, coffeeDiff) {
	setCurrCoffee(currCoffee);
	setNoteHours(noteHours);
	setNoteMinutes(noteMinutes);
}
Note::Note(const JournalItem& obj) :
	JournalItem(obj.getHours(), obj.getMinutes(), 
		obj.getEmployee(), obj.getCoffeeDiff()) {
	currCoffee = 0;
	noteHours = 0;
	noteMinutes = 0;
}
Note::Note(const Note& copied) : JournalItem(copied.getHours(), 
	copied.getMinutes(), copied.getEmployee(), copied.getCoffeeDiff()) {
	this->currCoffee = copied.getCurrCoffee();
	this->noteHours = copied.getNoteHours();
	this->noteMinutes = copied.getNoteMinutes();
}
void Note::setNoteHours(int noteHours) {
	this->noteHours = noteHours;
}
void Note::setNoteMinutes(int noteMinutes) {
	this->noteMinutes = noteMinutes;
}
void Note::setCurrCoffee(double currCoffee) {
	this->currCoffee = currCoffee;
}
int Note::getNoteHours() const {
	return noteHours;
}
int Note::getNoteMinutes() const {
	return noteMinutes;
}
double Note::getCurrCoffee() const {
	return currCoffee;
}
JournalItem::id Note::identify() const {
	return id::note;
}