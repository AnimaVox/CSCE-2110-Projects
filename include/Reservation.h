#ifndef RESERVATION_H
#define RESERVATION_H
 
#include <string>
using namespace std;
 
class Reservation {
    private:
        string id;             
        string studentID;    
        string studentName;   
        string resourceID;    
        string date;    
 
    public:
        Reservation();     // Default Constructor
        Reservation(const string& id, const string& studentID, const string& studentName,
                    const string& resourceID, const string& date);
 
        // Getters
        string getID() const;
        string getStudentID() const;
        string getStudentName() const;
        string getResourceID() const;
        string getDate() const;
 
        // Setters
        void setDate(const string& newDate);
 
        // Helpers
        void display() const;   // Display the reservation information in one formatted line.
};
 
#endif
