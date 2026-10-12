/*
- Original Author: Dean Foote
- Editor: D'Antae Leathers
*/

#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include "Student.h"
#include <queue>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Request{ // Struct for bundling Student info and resource ID. Stored in the waiting-list queue, and used to generate its contents.
    Student stu;
    string resoID;
    string date;
};

struct RequestCount{ // Struct for bundling resource IDs to a count. Used in getWaitingCount() 
    string resoID;
    int count;
};

class WaitingList {
public:
    // Takes student object to add to queue,
    // returns false if the student is already in the queue for that resource and date, true otherwise
    bool AddStudent(const Student& student, const string& resoID, const string& date); 

    void DisplayWaiting() const; // This should create a copy of the original queue so we don't accidentally destroy the actual queue displaying the data

    bool peekWaiting(const string& resoID, const string& date, Student& result) const;
    
    void removeWaiting(const string& resoID, const string& date, const string& studentID);

    void reportWaiting(); // Reports the number of students waiting for each resources that has student(s) waiting on them.

    vector<RequestCount> getWaitingCounts() const; // Returns a vector of the RequestCounts that can be used to see how many students are waiting on each resource in the waiting-list

private:
    queue<Request> waitingStudents; // Queue containing student and resource ID data
};

#endif
