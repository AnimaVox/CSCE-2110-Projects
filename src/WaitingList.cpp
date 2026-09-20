#include "../include/WaitingList.h"

void WaitingList::AddStudent(queue<Student>& students) {
    students.push(students);
}

void WaitingList::RemoveStudent() {
    students.pop(students);
}

void WaitingList::DisplayWaiting(queue<Student> students) {
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
