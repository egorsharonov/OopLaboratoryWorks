#pragma once
#include<iostream>
#include "Journal.h"
#include "Note.h"
using namespace std;
class MyArray
{
private:
    Note* items;
    int count;
    int allocated;
    double flask;
    void grow();
    double flaskDiff(double, double);
public:
    MyArray();
    MyArray(const MyArray&);
    ~MyArray();
    void add(const JournalItem&);
    void add(const Note&);
    void remove(const int&);
    void removeAll();
    Note get(const int&);
    bool checkArray() const;
    int size() const;
    void printInFile(const string&) const;
    void getFromFile(const string&);
    bool same(const MyArray&);
    const double MAX_FLASK = 200;
};