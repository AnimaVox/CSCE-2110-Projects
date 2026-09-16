#include "../include/CancellationHistory.h" // I still need to figure out how cross-folder includes work

void CancellationHistory::AddHistory(const Reservation& cancelled) {
    history.push(cancelled);
}

void CancellationHistory::RestoreHistory() {
    history.pop(); // Need to put something before, how to return the reservation back?
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
