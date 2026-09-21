/*
- Original Author: Dean Foote
- Editor: D'Antae Leathers
*/

#include "../include/WaitingList.h"

void WaitingList::AddStudent(const Student& student) { // Adds student to queue
    waitingStudents.push(student);
}

void WaitingList::RemoveStudent() { // Removes student at front of queue
    waitingStudents.pop();
}

void WaitingList::DisplayWaiting() {
    if (waitingStudents.empty()) { // Check if the waiting list even has anything
        cout << "The waiting list is empty!" << endl;
        return;
    }

    queue<Student>  copyQueue = waitingStudents; // Create copy of the queue

    while (!copyQueue.empty()) { // Display everything in the queue until empty
        copyQueue.front().display();
        copyQueue.pop();
    }
    cout << endl;
}
