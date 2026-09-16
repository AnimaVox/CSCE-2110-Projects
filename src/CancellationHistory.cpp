#include "../include/CancellationHistory.h"

void CancellationHistory::AddHistory(const Reservation& cancelled) {
    history.push(cancelled);
}

Reservation CancellationHistory::RestoreHistory() {
    restore = history.top();
    history.pop();
    return restore;
}

void CancellationHistory::DisplayHistory(const Reservation history) {
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
