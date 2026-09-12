#include "CSCE-2110-Projects/include/WaitingList.h" // FIXME: Header include doesn't work

void WaitingList::AddStudent(const Student& student) {
    students.push(student);
}

void WaitingList::RemoveStudent() {
    students.pop(student);
}

void WaitingList::DisplayWaiting(const Student& student) const {
    while (!students.empty()) {
        cout << students.front() << endl;
        students.pop();
    }
    cout << endl;
}
