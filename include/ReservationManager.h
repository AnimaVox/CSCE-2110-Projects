#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H
 
#include "Reservation.h"
using namespace std;
 
// RESERVATION_MANAGER - Handles reservation operations
class ReservationManager {
    public:
        ReservationManager();
        ~ReservationManager();
 
        // Disable copying - this class owns raw linked-list pointers, so a
        // shallow copy would cause double-free / dangling-pointer bugs.
        ReservationManager(const ReservationManager& other) = delete;
        ReservationManager& operator=(const ReservationManager& other) = delete;
 
        // CREATE
        // Validates the fields
        bool CreateReservation(const string& id, const string& studentID, const string& studentName,
                                const string& resourceID, const string& date,
                                const string& startTime, const string& endTime);
 
        // CANCEL
        // Removes the reservation with the given ID from the linked list.
        bool CancelReservation(const string& id);
        bool CancelReservation(const string& id, Reservation& removed);
 
        // SEARCH
        // Traverses the linked list and prints every reservation 
        int SearchReservation(const string& keyword) const;
 
        // Exact-match lookup by reservation ID, no printing.
        bool FindByID(const string& id, Reservation& found) const;
 
        // DISPLAY
        void DisplayReservation() const; // Displays all active reservations
 
        // VALIDATE
        // Checks that fields are non-empty, that startTime is before
        bool ValidateReservation(const string& id, const string& studentID, const string& studentName,
                                  const string& resourceID, const string& date,
                                  const string& startTime, const string& endTime) const;
 
        // Traverses the linked list to check whether a resource is free
        // for a given date/time range (no conflicting active reservation).
        bool IsResourceAvailable(const string& resourceID, const string& date,
                                  const string& startTime, const string& endTime) const;
 
        int Count() const; // Returns the total number of active reservations
 
    private:
        // Linked list node - one active reservation.
        struct ReservationNode {
            Reservation data;
            ReservationNode* next;
            ReservationNode(const Reservation& r) : data(r), next(nullptr) {}
        };
 
        ReservationNode* head;  // first (oldest) active reservation
        ReservationNode* tail;  // last (newest) active reservation
        int size;
 
        // Helpers
        static void printHeader();                 // Prints the header for reservation display
        static string toLower(const string& text); // Case-insensitive helper used by SearchReservation
        static bool timesOverlap(const string& startA, const string& endA,
                                  const string& startB, const string& endB); // "HH:MM" 24-hour strings
};
 
#endif
