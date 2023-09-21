#pragma once
#include<iostream>
#include "Employee.h"
using namespace std;
class JournalItem {
private:
	int hours;
	int minutes;
	Employee employee;
	double coffeeDiff;
public:
	enum id {
		journalItem,
		note
	};
	JournalItem();
	JournalItem(int hours, int minutes, const Employee& employee,
		const double& coffeeDiff);
	JournalItem(const JournalItem& copied);
	~JournalItem() {};
	int getHours() const;
	int getMinutes() const;
	Employee getEmployee() const;
	double getCoffeeDiff() const;
	void setHours(int);
	void setMinutes(int);
	void setEmployee(Employee);
	void setCoffeeDiff(double);
	virtual id identify() const;
};