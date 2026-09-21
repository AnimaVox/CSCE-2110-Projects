#ifndef RESERVATION_H
#define RESERVATION_H
 
#include <string>
using namespace std;
 
class Reservation {
    private:
        string id;             // e.g. "RSV101"
        string studentID;      // e.g. "S1001"
        string studentName;    // e.g. "Alice Chen"
        string resourceID;     // e.g. "R101"
        string date;           // e.g. "2026-09-20"
        string startTime;      // e.g. "10:00" (24-hour, zero-padded)
        string endTime;        // e.g. "11:00" (24-hour, zero-padded)
 
    public:
        Reservation();     // Default Constructor
        Reservation(const string& id, const string& studentID, const string& studentName,
                    const string& resourceID, const string& date,
                    const string& startTime, const string& endTime);
 
        // Getters
        string getID() const;
        string getStudentID() const;
        string getStudentName() const;
        string getResourceID() const;
        string getDate() const;
        string getStartTime() const;
        string getEndTime() const;
 
        // Setters
        void setDate(const string& newDate);
        void setStartTime(const string& newStartTime);
        void setEndTime(const string& newEndTime);
 
        // Helpers
        void display() const;   // Display the reservation information in one formatted line.
};
 
#endif
