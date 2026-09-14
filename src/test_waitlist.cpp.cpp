/*
 * test_waitlist.cpp
 * Standalone demo/test for WaitingList / WaitingListManager.
 * Not part of the final program - just here to prove the module works
 * before it's wired into ReservationManager. Safe to delete once
 * integrated, or keep as a quick manual test you can show in your demo.
 */

#include "WaitingList.h"
#include <iostream>

int main() {
    std::cout << "=== Waiting List Module Test ===\n\n";

    WaitingListManager manager;

    // Two students wait for Resource 101 (a study room), one waits for
    // Resource 202 (a laptop), to prove lists are separated per resource.
    std::cout << "Adding students to waiting lists...\n";
    manager.AddStudent(101, 1001, "Alice Chen");
    manager.AddStudent(101, 1002, "Ben Ortiz");
    manager.AddStudent(202, 1003, "Cara Diaz");

    // Duplicate add should fail.
    bool dup = manager.AddStudent(101, 1001, "Alice Chen");
    std::cout << "Duplicate add for student 1001 succeeded? "
               << (dup ? "yes (BUG)" : "no (correct)") << "\n\n";

    std::cout << "-- All waiting lists --\n";
    manager.DisplayAll();

    std::cout << "\nRemoving front of Resource 101's waiting list (FIFO order)...\n";
    WaitingStudent served;
    if (manager.RemoveStudent(101, served)) {
        std::cout << "Served: " << served.studName
                  << " (ID " << served.studID << ") for Resource " << served.resourceID << "\n";
    }

    std::cout << "\n-- Resource 101 waiting list after removal --\n";
    manager.DisplayWaiting(101);

    std::cout << "\nSize of Resource 101's list: " << manager.Size(101) << "\n";
    std::cout << "Size of Resource 202's list: " << manager.Size(202) << "\n";

    std::cout << "\n=== Test complete ===\n";
    return 0;
}