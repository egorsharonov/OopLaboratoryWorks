#pragma once
#include<iostream>
using namespace std;
class Employee
{
private:
	string firstName;
	string lastName;
	string fatherName;
	string post;
	string degree;
	void setFirstName(const string&);
	void setLastName(const string&);
	void setFatherName(const string&);
	void setPost(const string&);
	void setDegree(const string&);
	bool checkValue(const string&);
public:
	Employee();
	Employee(const string& firstName, const string& lastName, 
		const string& fatherName, const string& post, const string& degree);
	Employee(const Employee& copied);
	~Employee() {};
	string getFirstName() const;
	string getLastName() const;
	string getFatherName() const;
	string getPost() const;
	string getDegree() const;
};