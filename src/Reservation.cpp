/*
- Original Author: Erin Sen
- Editor: D'Antae Leathers
*/

#include "../include/Reservation.h" // updated header file path - DL
#include <iostream>
#include <iomanip>
 
Reservation::Reservation(){
    id = "";
    date = "";
    
    studentID = "";
    studentName = "";
    
    resourceID = "";
}
 
Reservation::Reservation(const string& id, const string& date, const Resource& resource, const Student& student){
    this->id = id;
    this->date = date;
    this->studentID = student.getID();
    this->studentName = student.getName();
    this->resourceID = resource.getID();
}
 
// Getters
string Reservation::getID() const {
    return id;
}
 
string Reservation::getDate() const {
    return date;
}
 
string Reservation::getStudentID() const {
    return studentID;
}

string Reservation::getStudentName() const {
    return studentName;
}

string Reservation::getResourceID() const {
    return resourceID;
}

// Setters
void Reservation::setID(const string& newID) {
    id = newID;
}

void Reservation::setDate(const string& newDate) {
    date = newDate;
}
 
// Helpers
void Reservation::display() const { // Display the reservation information in one formatted line.
    cout << left
         << setw(10) << id
         << setw(10) << studentID
         << setw(20) << studentName
         << setw(12) << resourceID
         << setw(12) << date
         << endl;
}