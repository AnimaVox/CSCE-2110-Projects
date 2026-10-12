/*
- Original Author: Dean Foote
- Editor: D'Antae Leathers
*/

#include "../include/WaitingList.h"

bool WaitingList::AddStudent(const Student& student, const string& resoID, const string& date) { // Adds student to queue
    queue<Request> copy = waitingStudents;
    while (!copy.empty()) {
        const Request& r = copy.front();
        if (r.stu.getID() == student.getID() && r.resoID == resoID && r.date == date) {
            return false; // Same student, resource, and date is already waiting
        }
        copy.pop();
    }
    
    Request r;
    r.stu = student;
    r.resoID = resoID;
    r.date = date;
    waitingStudents.push(r);
    return true;
}

void WaitingList::DisplayWaiting() const{
    if (waitingStudents.empty()) { // Check if the waiting list even has anything
        cout << "The waiting-list is empty!" << endl;
        return;
    }

    queue<Request>  copyQueue = waitingStudents; // Create copy of the queue
    int inQueue = 0;

    while (!copyQueue.empty()) { // Display everything in the queue until empty
        cout << copyQueue.front().stu.getID() << " " << copyQueue.front().stu.getName() << " " << copyQueue.front().resoID << " @ " 
        << copyQueue.front().date << endl;
        copyQueue.pop();
        inQueue++;
    }

    cout << "There are currently " << inQueue << " reservations in queue..." << endl;
}

bool WaitingList::peekWaiting(const string& resoID, const string& date, Student& result) const {
    queue<Request> copy = waitingStudents;
    while (!copy.empty()) {
        const Request& r = copy.front();
        if (r.resoID == resoID && r.date == date) { // Match both resource and date
            result = r.stu;
            return true;
        }
        copy.pop();
    }
    return false;
}

void WaitingList::removeWaiting(const string& resoID, const string& date, const string& studentID) {
    queue<Request> keep;
    bool removed = false;
    while (!waitingStudents.empty()) {
        Request cur = waitingStudents.front();
        waitingStudents.pop();
        if (!removed && cur.resoID == resoID && cur.date == date && cur.stu.getID() == studentID) {
            removed = true; // Drop only the first match
        } else {
            keep.push(cur);
        }
    }
    waitingStudents = move(keep);
}

void WaitingList::reportWaiting() {
   if (waitingStudents.empty()) { // Check if the waiting-list is empty
        cout << "There are no students currently on the waiting-list..." << endl;
        return;
    }

    // Get the counts from getWaitingCounts(). These counts are the number or students waiting for each resource.
    vector<RequestCount> tempCounts = getWaitingCounts();

    // Print out the count for each and every resource
    cout << "There are currently: " << endl;
    for (int i = 0; i < static_cast<int>(tempCounts.size()); i++){
        cout << tempCounts[i].count << (tempCounts[i].count == 1 ? " Student" : " Students") << " waiting for resource " << tempCounts[i].resoID << endl;
    }
}

vector<RequestCount> WaitingList::getWaitingCounts() const {
    
    vector<RequestCount> waitCounts;

    if (waitingStudents.empty()) { // Check if the waiting-list is empty
        return waitCounts; // Returning an empty vector
    }

    queue<Request> tempQueue = waitingStudents; // Instead of popping and rebuilding the queue, create a copy of the queue to manipulate.

    struct Tally{ // This in-scope struct is here because I need to bundle resource IDs with specific students. This avoids having to use three parallel vectors to track IDs, Students, and the counts of their appearances.
        string resoID;
        vector<string> studentIDs;
    };

    vector<Tally> tallies;

    // Go through the queue and take a tally of reservations for every resource
    while (!tempQueue.empty()){
        Request r = tempQueue.front();
        tempQueue.pop();

        int tallyIndex = -1;
        for(int j = 0; j < static_cast<int>(tallies.size()); j++){
            if(tallies[j].resoID == r.resoID){
                tallyIndex = j;
                break;
            }
        }

        if(tallyIndex == -1){
            Tally t;
            t.resoID = r.resoID;
            t.studentIDs.push_back(r.stu.getID());
            tallies.push_back(t);
        } else {
            bool found = false;
            for(int k = 0; k < static_cast<int>(tallies[tallyIndex].studentIDs.size()); k++){
                if(tallies[tallyIndex].studentIDs[k] == r.stu.getID()){
                    found = true;
                    break;
                }
            }
            
            if(!found){
                tallies[tallyIndex].studentIDs.push_back(r.stu.getID());
            }
        }
    }

    for (const auto& tally : tallies){
        waitCounts.push_back({tally.resoID, static_cast<int>(tally.studentIDs.size())});
    }

    return waitCounts;
}
