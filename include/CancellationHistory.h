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

    bool isEmpty() const; // Checks if the cancellation history is empty

    void DisplayHistory() const; // Should copy a stack so when popped, it shouldn't compromise the original

    template<typename TryRestore>
    bool restoreMostRecent(TryRestore tryRestore) {
        stack<Reservation> skipped;
        bool restored = false;

        while (!history.empty() && !restored) {
            Reservation candidate = history.top();
            history.pop();

            if (tryRestore(candidate)) {restored = true;}        // Consumed, so it is not pushed back
            else {skipped.push(candidate);}   
        }

        while (!skipped.empty()) {      // Reversing the temp stack puts the original order back
            history.push(skipped.top());
            skipped.pop();
        }
    return restored;
    }

private:
    stack<Reservation> history; // Stack containing history of cancelled reservations
    
    static void printHeader(); // Prints the header for cancellation history display
};

#endif
