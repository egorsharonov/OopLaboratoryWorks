#pragma once
#include<iostream>
#include"Journal.h"
class Note : public JournalItem {
private:
	double currCoffee;
	int noteHours;
	int noteMinutes;
public:
	Note();
	Note(int hours, int minutes, const Employee& employee, 
		const double& coffeeDiff, const double& currCoffee, 
		const int& noteHours, const int& noteMinutes);
	Note(const JournalItem& obj);
	Note(const Note& copied);
	~Note() {};
	double getCurrCoffee() const;
	int getNoteHours() const;
	int getNoteMinutes() const;
	void setCurrCoffee(double);
	void setNoteHours(int);
	void setNoteMinutes(int);
	id identify() const override;
};