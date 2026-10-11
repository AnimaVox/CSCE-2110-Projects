/*
- Original Author: Dean Foote
- Editor: D'Antae Leathers
*/

#include "../include/CancellationHistory.h"

void CancellationHistory::printHeader() {
    cout << left
         << setw(8) << "ID"
         << setw(12) << "StudentID"
         << setw(20) << "StudentName"
         << setw(12) << "ResourceID"
         << setw(15) << "Date"
         << endl;
        cout << string(65, '-') << endl; // Line of dashes for separation
}

void CancellationHistory::AddHistory(const Reservation& cancelled) {
    history.push(cancelled);
}

Reservation CancellationHistory::RestoreHistory() {
    
    Reservation restore; // Used to store and return the reservation being restored before removing it from the history

    if (history.empty()) { // Check if the history even has anything to begin with
        cout << "The cancellation history is empty!" << endl;
        Reservation empty;
        return empty;
    }

    restore = history.top(); // Gives the reservation to restore

    string stuID = restore.getStudentID();
    string stuName = restore.getStudentName();
    string resoID = restore.getResourceID();

    cout << "Trying to restore reservation for [" << stuID << "] " << stuName << " with Resource ID: " << resoID << endl;
    return restore;
}

void CancellationHistory::removeHistory() {
    if (!history.empty()) {
        history.pop();
    }
}

void CancellationHistory::DisplayHistory() const {
    if (history.empty()) { // Check if the history even has anything to begin with
        cout << "The cancellation history is empty!" << endl;
        return;
    }

    stack<Reservation>  copyStack = history; // Create copy of the stack
    bool isFirst = true;

    printHeader();
    while (!copyStack.empty()) { // Display everything in the stack until empty
        if (isFirst) {
            cout << "** Most recent cancellation **" << endl;
            copyStack.top().display();
            cout << string(65, '-') << endl;
            isFirst = false;
        } else {
            copyStack.top().display();
        }
        copyStack.pop();
    }
    cout << endl << "The most recent cancellation will be restored first." << endl;
}
