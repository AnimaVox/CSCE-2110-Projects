#include "Reservation.h"
#include <iostream>
#include <iomanip>
 
Reservation::Reservation(){
    id = "";
    studentID = "";
    studentName = "";
    resourceID = "";
    date = "";
}
 
Reservation::Reservation(const string& id, const string& studentID, const string& studentName,
                          const string& resourceID, const string& date){
    this->id = id;
    this->studentID = studentID;
    this->studentName = studentName;
    this->resourceID = resourceID;
    this->date = date;
}
 
// Getters
string Reservation::getID() const {
    return id;
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
 
string Reservation::getDate() const {
    return date;
}
 
// Setters
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
