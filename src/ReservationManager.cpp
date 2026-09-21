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
            cout << "Error: Resource already has an active reservation for the given date." << endl;
            cout << "Added " << studentID << "|" << studentName << " to the queue for Resource: " << resourceID << endl;
            wl.AddStudent(Student(studentID, studentName));
            return false;
        }
    }
 
    return true; // All validations passed
}
 
int ReservationManager::count() const { // Simply returns the total number of reservations in the list.
    return static_cast<int>(reservations.size());
}

// CANCEL
bool ReservationManager::cancelReservation(const string& id, ResourceManager& rm, CancellationHistory& ch) {
    for (auto it = reservations.begin(); it != reservations.end(); ++it) { // Must use an iterator to use erase() 
        if (it->getID() == id) { // Find the reservation to cancel
            ch.AddHistory(*it);
            string resourceToFree = it->getResourceID(); // Get the resource for the reservation
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
                        resource.setStatus("Available");
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
 
// THIS FUNCTION IS COMMENTED OUT BECAUSE IT IS NOT CURRENTLY USED. REDO AND IMPLEMENT LATER. -DL
// int ReservationManager::SearchReservation(const string& keyword) const {
//     string lowerKeyword = strhlp.toLower(keyword);
//     int matches = 0;
//     bool headerPrinted = false;
 
//     ReservationNode* current = head;
//     while (current != nullptr) {
//         const Reservation& r = current->data;
//         if (strhlp.toLower(r.getID()).find(lowerKeyword) != string::npos ||
//             strhlp.toLower(r.getStudentID()).find(lowerKeyword) != string::npos ||
//             strhlp.toLower(r.getStudentName()).find(lowerKeyword) != string::npos ||
//             strhlp.toLower(r.getResourceID()).find(lowerKeyword) != string::npos ||
//             strhlp.toLower(r.getDate()).find(lowerKeyword) != string::npos) {
//             if (!headerPrinted) {
//                 printHeader();
//                 headerPrinted = true;
//             }
//             r.display();
//             matches++;
//         }
//         current = current->next;
//     }
 
//     if (matches == 0) {
//         cout << "(no reservations matched \"" << keyword << "\")" << endl;
//     }
 
//     return matches;
// }

 
// THIS FUNCTION IS COMMENTED OUT BECAUSE IT IS NOT CURRENTLY USED. REDO AND IMPLEMENT LATER. -DL
// bool ReservationManager::FindByID(const string& id, Reservation& found) const {
//     ReservationNode* current = head;
//     while (current != nullptr) {
//         if (current->data.getID() == id) {
//             found = current->data;
//             return true;
//         }
//         current = current->next;
//     }
//     return false;
// }