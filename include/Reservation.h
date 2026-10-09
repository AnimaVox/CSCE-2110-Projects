/*
- Original Author: Erin Sen
- Editor: D'Antae Leathers
*/

#ifndef RESERVATION_H
#define RESERVATION_H
 
#include "Resource.h" // include Resource class to access resource information
#include "Student.h"  // include Student class to access student information
#include <string>
using namespace std;
 
class Reservation {
    private:
        string id;             
        string date;    

        string studentID;      // e.g. "1001"
        string studentName;    // e.g. "John Smith"

        string resourceID;     // e.g. "R101"

    public:
        Reservation(); // Default Constructor
        Reservation(const string& id, const string& date, const Resource& resource, const Student& student); 

        // Getters
        string getID() const;
        string getDate() const;
        
        string getStudentID() const;
        string getStudentName() const;

        string getResourceID() const;

        // Setters
        void setID(const string& newID);
        void setDate(const string& newDate);
 
        // Helpers
        void display() const; // Display the reservation information in one formatted line.
};
 
#endif