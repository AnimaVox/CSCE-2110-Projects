#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include <stack>
#include <iostream>

using namespace std;

class CancellationHistory {
public:
    void AddHistory(const Reservation& cancelled); // NOTE: Might need to be a pointer to access from the actual reservation file?

    Reservation RestoreHistory();

    void DisplayHistory(const Reservation history); // Should copy a stack so when popped, it shouldn't compromise the original.

private:
    stack<Reservation> history; // Stack containing history of cancelled reservations
    Reservation restore;
};

#endif
