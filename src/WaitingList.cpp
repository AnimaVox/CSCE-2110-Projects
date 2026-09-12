#include "CSCE-2110-Projects/include/WaitingList.h" // I don't know how to find .h files when they're in a different folder
// TODO: Find out how the other classes and objects are handled to find out how to implement waiting list.
void WaitingList::AddStudent(const Student& students) {

}

void WaitingList::RemoveStudent() {

}

void WaitingList::DisplayWaiting(const Student& students) const {
    while (!students.empty()) {
        cout << students.front() << endl;
        students.pop();
    }
    cout << endl;
}
