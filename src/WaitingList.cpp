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
    if (waitingStudents.empty()) { // Check if the waiting-list is empty
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

void WaitingList::reportWaiting() {
   if (waitingStudents.empty()) { // Check if the waiting-list is empty
        cout << "There are no students currently on the waiting-list..." << endl;
        return;
    }

    // Get the counts from getWaitingCounts(). These counts are the number or students waiting for each resource.
    vector<RequestCount> tempCounts = getWaitingCounts();

    // Print out the count for each and every resource
    cout << "There are currently: " << endl;
    for (int i = 0; i < (int)tempCounts.size(); i++){
        cout << tempCounts[i].count << (tempCounts[i].count == 1 ? " Student" : " Students") << " waiting for resource " << tempCounts[i].resoID << endl;
    }
}

vector<RequestCount> WaitingList::getWaitingCounts() const {
    
    vector<RequestCount> waitCounts;

    if (waitingStudents.empty()) { // Check if the waiting-list is empty
        return waitCounts; // Returning an empty vector
    }

    queue<Request> tempQueue = waitingStudents; // Instead of popping and rebuilding the queue like in checkWaiting(), creating a copy of the queue to manipulate. I do this here instead, because I don't need to perserve order here.

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
        for(int j = 0; j < (int)tallies.size(); j++){
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
            for(int k = 0; k < (int)tallies[tallyIndex].studentIDs.size(); k++){
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
        waitCounts.push_back({tally.resoID, (int)tally.studentIDs.size()});
    }

    return waitCounts;
}
