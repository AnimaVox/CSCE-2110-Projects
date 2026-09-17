#include "../include/WaitingList.h"

void WaitingList::AddStudent(const Student& student) {
    students.push(student);
}

void WaitingList::RemoveStudent() {
    students.pop(student);
}

void WaitingList::DisplayWaiting(const Student student) {
    if (students.empty()) { // Check if the waiting list even has anything
        cout << "The waiting list is empty!" << endl;
        return;
    }

    while (!students.empty()) { // Display everything in the list until empty
        cout << students.front() << endl;
        students.pop();
    }
    cout << endl;
}
