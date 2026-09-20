#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include <stack>
#include <iostream>

using namespace std;

class CancellationHistory {
public:
    void AddHistory(stack<Reservation>& cancelled);

    Reservation RestoreHistory();

    void DisplayHistory(stack<Reservation> history); // Should copy a stack so when popped, it shouldn't compromise the original

private:
    stack<Reservation> history; // Stack containing history of cancelled reservations
    Reservation restore; // Used to store and return the reservation being restored before removing it from the history
};

#endif
