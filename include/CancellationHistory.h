/*
- Original Author: Dean Foote
- Editor: D'Antae Leathers
*/

#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include "Reservation.h"
#include <stack>
#include <iostream>

using namespace std;

class CancellationHistory {
public:
    void AddHistory(const Reservation& cancelled);

    Reservation RestoreHistory();

    void DisplayHistory() const; // Should copy a stack so when popped, it shouldn't compromise the original

private:
    stack<Reservation> history; // Stack containing history of cancelled reservations
};

#endif
