/*
- Original Author: Dean Foote
- Editor: D'Antae Leathers
*/

#include "../include/WaitingList.h"

void WaitingList::AddStudent(const Student& student, const string& resoID) { // Adds student to queue
    Request r;
    r.stu = student;
    r.resoID = resoID;
    waitingStudents.push(r);
}

void WaitingList::RemoveStudent() { // Removes student at front of queue || TO-DO: Make it remove selected student (using date)
    waitingStudents.pop();
}

void WaitingList::DisplayWaiting() const{
    if (waitingStudents.empty()) { // Check if the waiting list even has anything
        cout << "The waiting list is empty!" << endl;
        return;
    }

    queue<Request>  copyQueue = waitingStudents; // Create copy of the queue
    int inQueue = 0;

    while (!copyQueue.empty()) { // Display everything in the queue until empty
        cout << copyQueue.front().stu.getID() << " " << copyQueue.front().stu.getName() << " " << copyQueue.front().resoID << endl;
        copyQueue.pop();
        inQueue++;
    }

    cout << "There are currently " << inQueue << " reservations in queue..." << endl;
}

bool WaitingList::checkWaiting(const string& resoID, Student& result) {
    if (waitingStudents.empty()) { // Check if the waiting empty
        return false;
    }

    queue<Request>  returnQueue;
    bool found = false;

    while (!waitingStudents.empty()){
        Request current = waitingStudents.front();
        waitingStudents.pop();
    
        if (current.resoID == resoID && !found){
            found = true;
            result = current.stu;
        } else {
            returnQueue.push(current);
        }
    }
    
    waitingStudents = move(returnQueue);

    return found;
}

int WaitingList::count() const { // Simply returns the total number of reservations in the list.
    return static_cast<int>(waitingStudents.size());
}
