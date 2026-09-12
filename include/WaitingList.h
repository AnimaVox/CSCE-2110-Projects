#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <queue>
#include <iostream>

using namespace std;

class WaitingList { // TODO: Find out how the other classes and objects are handled to find out how to implement waiting list
public:
    void AddStudent(const Student& students); // Takes student object to add to queue

    void RemoveStudent(); // Removes a student from the front of the queue

    void DisplayWaiting(const Student& students) const; // This should create a copy of the original queue so we don't accidentally destroy the actual queue displaying the data

private:
    queue<Student> students; // Queue containing student data
};

#endif
