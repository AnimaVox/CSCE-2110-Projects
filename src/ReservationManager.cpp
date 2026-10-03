/*
- Original Author: Erin Sen
- Editor: D'Antae Leathers
*/

#include "../include/ReservationManager.h" // updated header file path - DL
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream> // ifstream (used to read file)
#include <sstream> // istringstream (used to parse lines)
#include <vector> // vector (used to store parts of a line)

// --- CREATE ---
bool ReservationManager::createReservation(string& id, const string& stuID, const string& stuName, const string& resoID, const string& date, ResourceManager& rm, WaitingList& wl) {
    for (auto& resource : rm.getResources()) {
        if (resource.getID() == resoID) { // Check if the resource exists in the ResourceManager
            // Resource exists, proceed
           
            // If no reservation ID was provided, generate a new reservation ID based on the reservations in the list.
            if (id.empty()) {
                // Get the last reservation's ID using reservations.back().getID().
                id = (reservations.back().getID());
        
                for (const auto& res : reservations) { // Check if the next ID is already in use
                    // Convert the ID to an integer using stoi(), increment it by 1, and convert it back to a string.
                    if (to_string(stoi(reservations.back().getID()) + 1) != res.getID()) { // If the next ID is not already in use, use it
                        id = to_string(stoi(reservations.back().getID()) + 1);
                        // Converting to int drops leading zeros, so pad the ID with leading zeros to ensure it is always 3 digits long
                        for (int i = id.length(); i < 3; ++i) { 
                            id = "0" + id;
                        }
                    }
                }
            }

            // Create a new reservation with the provided ID
            Reservation newReservation(id, date, resource, Student(stuID, stuName));
            if (!ValidateReservation(newReservation, wl)) {
                cout << "Reservation validation failed." << endl;
                return false; // Validation failed
            }
            reservations.push_back(newReservation);
            resource.setStatus("Unavailable"); // Mark the resource as unavailable
            cout << "Reservation created successfully with ID: " << id << endl;
            return true; // Successfully created the reservation
        }
    }

    cout << "Error: Resource with ID " << resoID << " does not exist." << endl;
    return false; // Resource does not exist
}

bool ReservationManager::loadFile(const string& filename, ResourceManager& rm, WaitingList& wl) { // Copied directly from ResourceManager.cpp; modified to work with Reservation objects. -DL
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl; // Using cerr for error messages. Writes immediately for debugging
        return false; // If file cannot be opened, return false
    }

    reservations.clear(); // Clear existing reservations before loading new ones

    string line;
    int lineNumber = 0; // Keep track of the line number for error reporting

    while (getline(file, line)) {
        lineNumber++;

        if (line.empty()) {
            continue; // Skip empty lines
        }

        vector<string> parts = strhlp.splitLine(line, '|'); // Split the line into parts using '|' as the delimiter

        if (parts.size() != 5) { // Ensure that there are exactly 5 parts (ID, Student ID, Student Name, Resource ID, Date)
            cerr << "Warning: Line " << lineNumber << " in file " << filename << " has incorrect format." << endl;
            continue; // Skip this line and continue with the next one
        }

        // Extract the parts into variables and set them to create a new Reservation object
        string id = parts[0];
        string stuID = parts[1];
        string stuName = parts[2];
        string resoID = parts[3];
        string date = parts[4];

        createReservation(id, stuID, stuName, resoID, date, rm, wl); // Create a new reservation with the parsed data
    }

    file.close();
    return true; // Successfully loaded the file
}

// VALIDATE
bool ReservationManager::ValidateReservation(const Reservation& resv, WaitingList& wl) const {
    const string& studentID = resv.getStudentID();
    const string& studentName = resv.getStudentName();
    const string& resourceID = resv.getResourceID();
    const string& date = resv.getDate();

    // Check that all inputted fields are non-empty. 
    // ResourceID is checked when creating the reservation 
    // and ReservationID is generated automatically -DL
    if (!studentID.empty() && !studentName.empty() && !date.empty()) {

        // Check that the student ID is numeric -DL
        for (char c : studentID) {
            if (!isdigit(c)) {
                cout << "Error: Student ID is not numeric." << endl;
                return false;
            }
        }

        // Check that the date is in the correct format e.g., 09/23/2026 (MM/DD/YYYY) -DL
        if (date.length() != 10 || date[2] != '/' || date[5] != '/') {
            cout << "Error: Date must be in the format MM/DD/YYYY." << endl;
            return false;
        } else if (date[0] > '1' || (date[0] == '1' && date[1] > '2')) {
            cout << "Error: Invalid month." << endl;
            return false;
        } else if (date[3] > '3' || (date[3] == '3' && (date[4] != '0' || date[4] != '1'))) { // Does not account for months with fewer than 30 days. -DL
            cout << "Error: Invalid day." << endl;
            return false;
        }
    }
    else{
    cout << "Error: Empty reservation data." << endl;
    return false; 
    }

    // Check that the resource ID isn't already reserved for the given date -DL
    for (const auto& res : reservations) {
        if (res.getResourceID() == resourceID && res.getDate() == date) {
            cout << "Resource already has an active reservation for the given date." << endl;
            cout << "Adding " << studentID << "|" << studentName << " to the queue for Resource: " << resourceID << endl;
            wl.AddStudent(Student(studentID, studentName), resourceID);
            return false;
        }
    }
 
    return true; // All validations passed
}
 
int ReservationManager::count() const { // Simply returns the total number of reservations in the list.
    return static_cast<int>(reservations.size());
}

// CANCEL
bool ReservationManager::cancelReservation(const string& id, ResourceManager& rm, CancellationHistory& ch, WaitingList& wl) {
    for (auto it = reservations.begin(); it != reservations.end(); ++it) { // Must use an iterator to use erase() 
        if (it->getID() == id) { // Find the reservation to cancel
            ch.AddHistory(*it);
            string resourceToFree = it->getResourceID(); // Get the resource for the reservation
            string dateToFree = it->getDate();
            reservations.erase(it); // Remove the reservation from the list
            
            bool reservedByAnother = false; // Check if any other reservations use that resource
            for(const auto& res: reservations){
                if (res.getResourceID() == resourceToFree){
                    reservedByAnother = true;
                }
            }
            
            for (auto& resource : rm.getResources()){ // Find the resource in the collection and set it to "Available" if there are no other reservations.
                if(resource.getID() == resourceToFree){
                    if (!reservedByAnother){
                        Student nextInLine;
                        if (wl.checkWaiting(resourceToFree, nextInLine)) {
                            string newID = ""; // let createReservation auto-generate it
                            createReservation(newID, nextInLine.getID(), nextInLine.getName(), resourceToFree, dateToFree, rm, wl);
                        }
                        else{
                            resource.setStatus("Available");
                        }
                    }                   
                }
            }

            cout << "Reservation with ID " << id << " has been cancelled." << endl;
            return true; // Successfully cancelled the reservation
        }
    }    
    cout << "Error: No reservation with ID " << id << " exists." << endl;
    return false; // No reservation with the given ID exists
}
 
// DISPLAY
void ReservationManager::printHeader() {
    cout << left
         << setw(8) << "ID"
         << setw(10) << "StudentID"
         << setw(20) << "StudentName"
         << setw(12) << "ResourceID"
         << setw(15) << "Date"
         << endl;
        cout << string(65, '-') << endl; // Line of dashes for separation
}
 
void ReservationManager::DisplayReservations() const {
    if (reservations.empty()) {
        cout << "There are no active reservations." << endl;
        return;
    }
 
    printHeader();
    for (const auto& res : reservations) {
        res.display();
    }
}
 
// SEARCH
 
// SEARCH
// All of these use LINEAR SEARCH: start at the first reservation and check each one in order until the end. Time complexity is O(n).

bool ReservationManager::contains(const string& text, const string& pattern) { // Returns true if 'pattern' appears anywhere inside 'text'
    if (pattern.empty()) {                  // An empty pattern would match everything, so treat it as a match
        return true;
    }
    if (pattern.size() > text.size()) {     // A pattern longer than the text can never fit inside it
        return false;
    }

    for (size_t i = 0; i + pattern.size() <= text.size(); i++) { // i = every position in text where the pattern could START
        size_t j = 0;                       // j = how many characters of the pattern have matched so far
        while (j < pattern.size() && text[i + j] == pattern[j]) { // Keep going while characters match and the pattern isn't used up
            j++;                            // This character matched, move on to the next one
        }
        if (j == pattern.size()) {          // Every character of the pattern matched, so it was found
            return true;
        }
    }
    return false;                           // Tried every start position with no match
}

bool ReservationManager::searchByID(const string& id) const {
    for (const auto& res : reservations) {  // Look at every reservation in the list, one at a time, in order
        if (res.getID() == id) {            // Exact match: does this reservation's ID equal the one we want?
            printHeader();                  // Print the column headers first
            res.display();                  // Print the matching reservation
            return true;                    // Found it, so stop searching (IDs are unique)
        }
    }
    cout << "No reservation with ID " << id << " was found." << endl; // Reached the end of the list without a match
    return false;
}

int ReservationManager::searchReservation(const string& keyword) const {
    string lowerKeyword = strhlp.toLower(keyword); // Lowercase copy of the keyword so the search is case-insensitive
    int matches = 0;                               // Counts how many reservations match
    bool headerPrinted = false;                    // Makes sure the header prints only once, and only if there is a match

    for (const auto& res : reservations) {         // Visit every reservation (linear search)
        // Lowercase each field, then check whether the keyword appears inside it using contains()
        if (contains(strhlp.toLower(res.getID()), lowerKeyword) ||
            contains(strhlp.toLower(res.getStudentID()), lowerKeyword) ||
            contains(strhlp.toLower(res.getStudentName()), lowerKeyword) ||
            contains(strhlp.toLower(res.getResourceID()), lowerKeyword) ||
            contains(strhlp.toLower(res.getDate()), lowerKeyword)) {
            if (!headerPrinted) {                  // First match found: print the header now
                printHeader();
                headerPrinted = true;              // Don't print it again
            }
            res.display();                         // Print this matching reservation
            matches++;                             // Count it
        }
    }

    if (matches == 0) {                            // Nothing matched at all
        cout << "(no reservations matched \"" << keyword << "\")" << endl;
    }
    return matches;                                // Tell the caller how many were found
}

int ReservationManager::searchByStudent(const string& student) const {
    string lowerStudent = strhlp.toLower(student); // Lowercase copy so "john" matches "John Smith"
    int matches = 0;                               // Number of reservations found for this student
    bool headerPrinted = false;                    // Same print-header-once idea as above

    for (const auto& res : reservations) {         // Check every reservation (linear search)
        // Match either the student's ID or any part of their name
        if (contains(strhlp.toLower(res.getStudentID()), lowerStudent) ||
            contains(strhlp.toLower(res.getStudentName()), lowerStudent)) {
            if (!headerPrinted) {                  // First match: print the header
                printHeader();
                headerPrinted = true;
            }
            res.display();                         // Print the matching reservation
            matches++;                             // Count it
        }
    }

    if (matches == 0) {                            // No reservations for that student
        cout << "(no reservations found for student \"" << student << "\")" << endl;
    }
    return matches;
}
