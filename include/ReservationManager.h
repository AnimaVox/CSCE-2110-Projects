/*
This class handles "Reservation" objects and their operations.
- Original Author: Erin Sen
- Editor: D'Antae Leathers
*/

#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H
 
#include "Reservation.h"
#include "ResourceManager.h"
#include "StringHelpers.h" // StringHelpers class for string manipulation
#include "CancellationHistory.h"
#include "WaitingList.h"
#include <list>
using namespace std;
 
class ReservationManager {
    private:
        list<Reservation> reservations;
 
        // Helpers
        static void printHeader(); // Prints the header for reservation display
        StringHelpers strhlp; // Instance of StringHelpers for string manipulation  
        
    public:
        // --- CREATE ---
        // Validates the fields, then inserts the new reservation at the end of the linked list. Returns false if validation fails.
        bool createReservation(string& id, const string& studentID, const string& studentName, const string& resourceID, const string& date, ResourceManager& rm, WaitingList& wl);
        
        // Read reservations from a file. Returns false if the file cannot be opened or if any line has an incorrect format.
        bool loadFile(const string& filename, ResourceManager& rm, WaitingList& wl);
 
        // --- CANCEL ---
        // Removes the reservation with the given ID from the linked list. Returns false if no reservation with that ID exists. 
        bool cancelReservation(const string& id, ResourceManager& rm, CancellationHistory& ch, WaitingList& wl);
        
        // --- VALIDATE ---
        // Checks that fields are non-empty and supplied with valid values e.g. date is MM/DD/YYY, ID is numeric. Also checks if resource is available for the given date of the reservation, if not adds the reservation to the waiting list.
        bool ValidateReservation(const Reservation& res, WaitingList& wl) const;
        
        // --- SEARCH ---

        
        // --- DISPLAY ---
        void DisplayReservations() const; // Displays all active reservations

        // --- REPORT ---
        // Prints the amount of reservations for each and every resource.
        void reportResourceUse(const vector<Resource>& resources) const;

        // Prints the amount of total requests for the top 5 resources. Requests include both active and waiting reservations.
        void reportMostWanted(const vector<Resource>& resources, const WaitingList& wl) const;

        // --- GETTER ---
        int count() const; // Simply returns the total number of reservations in the list.
};
 
#endif
