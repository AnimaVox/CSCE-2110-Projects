#include "../include/CancellationHistory.h"

void CancellationHistory::AddHistory(stack<Reservation>& cancelled) {
    history.push(cancelled);
}

Reservation CancellationHistory::RestoreHistory() {
    restore = history.top(); // Gives the reservation to restore even as the original gets popped later
    history.pop();
    return restore;
}

void CancellationHistory::DisplayHistory(stack<Reservation> history) {
    if (history.empty()) { // Check if the history even has anything to begin with
        cout << "The cancellation history is empty!" << endl;
        return;
    }

    while (!history.empty()) { // Display the history, but hopefully the copy and not the original
        cout << history.top() << '\n';
        history.pop();
    }
    cout << endl;
}
