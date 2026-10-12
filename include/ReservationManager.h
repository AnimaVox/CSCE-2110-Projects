/*
This class handles "Reservation" objects and their operations.
- Original Author: Erin Sen
- Editors: D'Antae Leathers, Dean Foote
*/

#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H
 
#include "Reservation.h"
#include "ResourceManager.h"
#include "Helpers.h" // Helpers class for string manipulation and sorting
#include "CancellationHistory.h"
#include "WaitingList.h"
#include <list>
using namespace std;
 
enum class SortCriteriaResv{ // Using an enum here for readibility when calling sort functions
    ID,
    STUDENTID,
    STUDENTNAME,
    RESOURCEID,
    DATE
};

class ReservationManager {
    private:
        list<Reservation> reservations;
 
        // Helpers
        static void printHeader(); // Prints the header for reservation display
        Helpers hlp; // Instance of Helpers for string manipulation and sorting

    public:
        // --- CREATE ---
        // Validates the fields, then inserts the new reservation at the end of the linked list. Returns false if validation fails.
        // If bypass is true, it will skip validation and add the reservation directly. This is used when loading from a file.
        // If queueOnConflict is true, it will add the student to the waiting list if the resource is already reserved for the given date.
        bool createReservation(string& id, const string& studentID, const string& studentName, const string& resourceID, const string& date, ResourceManager& rm, WaitingList& wl, bool bypass = false, bool queueOnConflict = true); 
        // Read reservations from a file. Returns false if the file cannot be opened.
        bool loadFile(const string& filename, ResourceManager& rm, WaitingList& wl);
 
        // --- CANCEL ---
        // Removes the reservation with the given ID from the linked list. Returns false if no reservation with that ID exists. 
        bool cancelReservation(const string& id, ResourceManager& rm, CancellationHistory& ch, WaitingList& wl);
        
        // --- VALIDATE ---
        // Checks that fields are non-empty and supplied with valid values e.g. date is MM/DD/YYYY, checks StudentID is numeric. 
        // Also checks if resource is available for the given date of the reservation. 
        // If there is a date conflict, adds the reservation to the waiting list.
        bool ValidateReservation(const Reservation& res, ResourceManager& rm, WaitingList& wl, bool queueOnConflict = true) const;
        
        // --- SEARCH ---
        vector<Reservation> search(const string& keyword) const; // Sub-string search for reservations, case-insensitive

        // --- SORT ---
        // Sorts the reservations based on the specified criteria (ID, Date, StudentID, StudentName, or ResourceID) using an Insertion Sort algorithm
        void sortReservations(SortCriteriaResv criteria); 

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
