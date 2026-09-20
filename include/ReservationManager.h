/*
- Original Author: Erin Sen
- Editor: D'Antae Leathers
*/

#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H
 
#include "Reservation.h"
#include "ResourceManager.h"
#include "../include/StringHelpers.h" // StringHelpers class for string manipulation
#include <list> // Using STL implementation of a linked list to store active reservations - DL
using namespace std;
 
//Handles reservation operations.
class ReservationManager {
    public:
        // Removed constructor and destructor; using STL list automatically manages memory and nothing else should need to be done manually. -DL
        // Also removed copy constructor and assignment operator; STL list handles copying and assignment automatically. -DL

        // CREATE
        bool createReservation(string& id, const string& studentID, const string& studentName, const string& resourceID, const string& date, ResourceManager& rm);
        // Validates the fields, then inserts the new reservation at the end of the linked list. Returns false if validation fails.
        bool loadFile(const string& filename, ResourceManager& rm);
        // Added loadFile function to read reservations from a file. Returns false if the file cannot be opened or if any line has an incorrect format. -DL
 
        // CANCEL
        // Removes the reservation with the given ID from the linked list. Returns false if no reservation with that ID exists. 
        // If 'removed' is supplied, it is filled with the cancelled reservation so the caller can push it onto CancellationHistory (the stack).
        bool cancelReservation(const string& id);
 
        // SEARCH
        // Traverses the linked list and prints every reservation whose ID, student ID, student name, resource ID, or date contains 'keyword'. Returns how many matches were found.
        //int SearchReservation(const string& keyword) const; NOT CURRENTLY USED. REDO AND IMPLEMENT LATER. -DL
 
        // Exact-match lookup by reservation ID, no printing.
        //bool FindByID(const string& id, Reservation& found) const; NOT CURRENTLY USED. REDO AND IMPLEMENT LATER. -DL
 
        // DISPLAY
        void DisplayReservations() const; // Displays all active reservations
 
        // VALIDATE
        // Checks that fields are non-empty and that the reservation ID and resource ID aren't already in use by an active reservation.
        // Simplified to take a Reservation object instead of individual fields. -DL
        bool ValidateReservation(const Reservation& res) const;

        int count() const; // Simply returns the total number of reservations in the list.
 
    private:
        list<Reservation> reservations; // Using STL list to store active reservations. Removed other unnecessary variables/pointers -DL
 
        // Helpers
        static void printHeader(); // Prints the header for reservation display
        StringHelpers strhlp; // Instance of StringHelpers for string manipulation -DL
};
 
#endif
