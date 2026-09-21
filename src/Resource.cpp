/*
- Original Author: D'Antae Leathers
*/

#include "../include/Resource.h"
#include <iostream> // cin, cout
#include <iomanip> // setw

Resource::Resource(){ // Defualt constructor (empty)
    id = "";
    name = "";
    type = "";
    status = "";
}

Resource::Resource(const string& id, const string& name, const string& type, const string& status){ // parameterized constructor
    this->id = id;
    this->name = name;
    this->type = type;
    this->status = status;
}

// Getters
string Resource::getID() const {
    return id;
}

string Resource::getName() const {
    return name;
}

string Resource::getType() const {
    return type;
}

string Resource::getStatus() const {
    return status;
}

// Setters
void Resource::setStatus(const string& newStatus) {
    status = newStatus;
}

// Helpers
bool Resource::isAvailable() const { // Check if the resource is available, return false if unavailable
    return status == "Available";
}

void Resource::display() const { // Display the resource information in one formatted line.
    cout << left
    << setw(8) << id
    << setw(20) << name
    << setw(25) << type
    << setw(12) << status
    << endl;
}