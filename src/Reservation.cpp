#include "../include/Reservation.h"
#include <iostream>
#include <iomanip>
 
Reservation::Reservation(){
    id = "";
    studentID = "";
    studentName = "";
    resourceID = "";
    date = "";
    startTime = "";
    endTime = "";
}
 
Reservation::Reservation(const string& id, const string& studentID, const string& studentName,
                          const string& resourceID, const string& date,
                          const string& startTime, const string& endTime){
    this->id = id;
    this->studentID = studentID;
    this->studentName = studentName;
    this->resourceID = resourceID;
    this->date = date;
    this->startTime = startTime;
    this->endTime = endTime;
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
 
string Reservation::getStartTime() const {
    return startTime;
}
 
string Reservation::getEndTime() const {
    return endTime;
}
 
// Setters
void Reservation::setDate(const string& newDate) {
    date = newDate;
}
 
void Reservation::setStartTime(const string& newStartTime) {
    startTime = newStartTime;
}
 
void Reservation::setEndTime(const string& newEndTime) {
    endTime = newEndTime;
}
 
// Helpers
void Reservation::display() const { // Display the reservation information in one formatted line.
    cout << left
         << setw(10) << id
         << setw(10) << studentID
         << setw(20) << studentName
         << setw(12) << resourceID
         << setw(12) << date
         << setw(8)  << startTime
         << setw(8)  << endTime
         << endl;
}
