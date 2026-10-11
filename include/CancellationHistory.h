/*
- Original Author: Dean Foote
- Editor: D'Antae Leathers
*/

#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include "Reservation.h"
#include <stack>
#include <iostream>
#include <iomanip>

using namespace std;

class CancellationHistory {
public:
    void AddHistory(const Reservation& cancelled);

    Reservation RestoreHistory(); // Returns the information of the most recent reservation in the history stack
    
    void removeHistory(); // Removes the most recent reservation from the history stack

    void DisplayHistory() const; // Should copy a stack so when popped, it shouldn't compromise the original

private:
    stack<Reservation> history; // Stack containing history of cancelled reservations
    
    static void printHeader(); // Prints the header for cancellation history display
};

#endif
