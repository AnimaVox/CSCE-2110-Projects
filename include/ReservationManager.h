#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H
 
#include "Reservation.h"
using namespace std;
 
//Handles reservation operations.
class ReservationManager {
    public:
        ReservationManager();
        ~ReservationManager();
 
        // Disable copying - this class owns raw linked-list pointers, so a shallow copy would cause double free/dangling pointer bugs.
        ReservationManager(const ReservationManager& other) = delete;
        ReservationManager& operator=(const ReservationManager& other) = delete;
 
        // CREATE
        // Validates the fields, then inserts the new reservation at the end
        // of the linked list. Returns false if validation fails.
        bool CreateReservation(const string& id, const string& studentID, const string& studentName,
                                const string& resourceID, const string& date);
 
        // CANCEL
        // Removes the reservation with the given ID from the linked list.
        // Returns false if no reservation with that ID exists. If 'removed' is supplied, it is filled with the cancelled reservation so the caller can push it onto CancellationHistory (the stack).
        bool CancelReservation(const string& id);
        bool CancelReservation(const string& id, Reservation& removed);
 
        // SEARCH
        // Traverses the linked list and prints every reservation whose ID, student ID, student name, resource ID, or date contains 'keyword'. Returns how many matches were found.
        int SearchReservation(const string& keyword) const;
 
        // Exact-match lookup by reservation ID, no printing.
        bool FindByID(const string& id, Reservation& found) const;
 
        // DISPLAY
        void DisplayReservation() const; // Displays all active reservations
 
        // VALIDATE
        // Checks that fields are non-empty and that the reservation ID and resource ID aren't already in use by an active reservation.
        bool ValidateReservation(const string& id, const string& studentID, const string& studentName,
                                  const string& resourceID, const string& date) const;
 
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
};
 
#endif
