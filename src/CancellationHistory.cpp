/*
- Original Author: Dean Foote
- Editor: D'Antae Leathers
*/

#include "../include/CancellationHistory.h"

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

    restore = history.top(); // Gives the reservation to restore even as the original gets popped later
    history.pop();

    string stuID = restore.getStudentID();
    string stuName = restore.getStudentName();
    string resoID = restore.getResourceID();

    cout << "Trying to restore reservation for " << stuID << "|" << stuName << " with Resource ID: " << resoID << endl;
    cout << "Please note the reservation ID below..." << endl;
    return restore;
}

void CancellationHistory::DisplayHistory() const {
    if (history.empty()) { // Check if the history even has anything to begin with
        cout << "The cancellation history is empty!" << endl;
        return;
    }

    stack<Reservation>  copyStack = history; // Create copy of the stack

    while (!copyStack.empty()) { // Display everything in the stack until empty
        copyStack.top().display();
        copyStack.pop();
    }
    cout << endl;
}
