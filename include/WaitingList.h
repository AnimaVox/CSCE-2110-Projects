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

using namespace std;

struct Request{
    Student stu;
    string resoID;
};

class WaitingList { // TODO: Find out how the other classes and objects are handled to find out how to implement waiting list
public:
    void AddStudent(const Student& student, const string& resoID); // Takes student object to add to queue

    void RemoveStudent(); // Removes a student from the front of the queue

    void DisplayWaiting(); // This should create a copy of the original queue so we don't accidentally destroy the actual queue displaying the data

    bool checkWaiting(const string& resoID, Student& result);

private:
    queue<Request> waitingStudents; // Queue containing student data
};

#endif
