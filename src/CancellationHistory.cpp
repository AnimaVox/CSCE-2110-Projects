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

bool CancellationHistory::isEmpty() const {
    return history.empty();
}

void CancellationHistory::AddHistory(const Reservation& cancelled) {
    history.push(cancelled);
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
    cout << endl << "The most recent cancellation will be restored if possible." << endl;
}
