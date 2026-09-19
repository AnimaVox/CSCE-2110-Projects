#include "ReservationManager.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
 
ReservationManager::ReservationManager(){
    head = nullptr;
    tail = nullptr;
    size = 0;
}
 
ReservationManager::~ReservationManager(){
    ReservationNode* current = head;
    while (current != nullptr) {
        ReservationNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}
 
// VALIDATE
bool ReservationManager::ValidateReservation(const string& id, const string& studentID, const string& studentName,
                                              const string& resourceID, const string& date) const {
    if (id.empty() || studentID.empty() || studentName.empty() || resourceID.empty() || date.empty()) {
        return false; 
    }
 
    ReservationNode* current = head;
    while (current != nullptr) {
        if (current->data.getID() == id) {
            return false; // reservation ID already in use
        }
        if (current->data.getResourceID() == resourceID) {
            return false; // resource already has an active reservation
        }
        current = current->next;
    }
 
    return true;
}
 
// CREATE
bool ReservationManager::CreateReservation(const string& id, const string& studentID, const string& studentName,
                                            const string& resourceID, const string& date) {
    if (!ValidateReservation(id, studentID, studentName, resourceID, date)) {
        return false;
    }
 
    Reservation newReservation(id, studentID, studentName, resourceID, date);
    ReservationNode* newNode = new ReservationNode(newReservation);
 
    if (tail == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
 
    size++;
    return true;
}
 
// CANCEL
bool ReservationManager::CancelReservation(const string& id, Reservation& removed) {
    ReservationNode* current = head;
    ReservationNode* prev = nullptr;
 
    while (current != nullptr) {
        if (current->data.getID() == id) {
            removed = current->data;
 
            if (prev == nullptr) {
                head = current->next;
                if (head == nullptr) {
                    tail = nullptr;
                }
            } else {
                prev->next = current->next;
                if (current == tail) {
                    tail = prev;
                }
            }
 
            delete current;
            size--;
            return true;
        }
        prev = current;
        current = current->next;
    }
 
    return false; // reservation ID not found
}
 
bool ReservationManager::CancelReservation(const string& id) {
    Reservation discarded;
    return CancelReservation(id, discarded);
}
 
// DISPLAY
void ReservationManager::printHeader() {
    cout << left
         << setw(10) << "ID"
         << setw(10) << "StudentID"
         << setw(20) << "StudentName"
         << setw(12) << "ResourceID"
         << setw(12) << "Date"
         << endl;
}
 
void ReservationManager::DisplayReservation() const {
    if (head == nullptr) {
        cout << "(no active reservations)" << endl;
        return;
    }
 
    printHeader();
    ReservationNode* current = head;
    while (current != nullptr) {
        current->data.display();
        current = current->next;
    }
}
 
// SEARCH
string ReservationManager::toLower(const string& text) {
    string result = text;
    transform(result.begin(), result.end(), result.begin(),
              [](unsigned char c) { return tolower(c); });
    return result;
}
 
int ReservationManager::SearchReservation(const string& keyword) const {
    string lowerKeyword = toLower(keyword);
    int matches = 0;
    bool headerPrinted = false;
 
    ReservationNode* current = head;
    while (current != nullptr) {
        const Reservation& r = current->data;
        if (toLower(r.getID()).find(lowerKeyword) != string::npos ||
            toLower(r.getStudentID()).find(lowerKeyword) != string::npos ||
            toLower(r.getStudentName()).find(lowerKeyword) != string::npos ||
            toLower(r.getResourceID()).find(lowerKeyword) != string::npos ||
            toLower(r.getDate()).find(lowerKeyword) != string::npos) {
            if (!headerPrinted) {
                printHeader();
                headerPrinted = true;
            }
            r.display();
            matches++;
        }
        current = current->next;
    }
 
    if (matches == 0) {
        cout << "(no reservations matched \"" << keyword << "\")" << endl;
    }
 
    return matches;
}
 
bool ReservationManager::FindByID(const string& id, Reservation& found) const {
    ReservationNode* current = head;
    while (current != nullptr) {
        if (current->data.getID() == id) {
            found = current->data;
            return true;
        }
        current = current->next;
    }
    return false;
}
 
int ReservationManager::Count() const {
    return size;
}
