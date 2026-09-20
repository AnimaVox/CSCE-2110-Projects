/*
- Original Author: D'Antae Leathers
*/

#include "../include/Student.h"
#include <iostream> // cin, cout
#include <iomanip> // setw

Student::Student(){ // Default constructor (empty)
    id = "";
    name = "";
}

Student::Student(const string& id, const string& name){ // parameterized constructor
    this->id = id;
    this->name = name;
}

// Getters
string Student::getID() const {
    return id;
}

string Student::getName() const {
    return name;
}

// Setters
void Student::setID(const string& newID) {
    id = newID;
}

void Student::setName(const string& newName) {
    name = newName;
}

// Helpers
void Student::display() const { // Display the student information in one formatted line.
    cout << left
    << setw(8) << id
    << setw(20) << name
    << endl;
}