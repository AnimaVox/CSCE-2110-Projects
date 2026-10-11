/*
- Original Author: Erin Sen
- Editor: D'Antae Leathers
*/

#include "../include/ReservationManager.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream> // ifstream (used to read file)
#include <sstream> // istringstream (used to parse lines)
#include <vector> // vector (used to store parts of a line)

// -- HELPERS ---
void ReservationManager::printHeader() {
    cout << left
         << setw(8) << "ID"
         << setw(12) << "StudentID"
         << setw(20) << "StudentName"
         << setw(12) << "ResourceID"
         << setw(15) << "Date"
         << endl;
        cout << string(65, '-') << endl; // Line of dashes for separation
}

// --- CREATE ---
bool ReservationManager::createReservation(string& id, const string& stuID, const string& stuName, const string& resoID, const string& date, ResourceManager& rm, WaitingList& wl, bool bypass) {
    for (auto& resource : rm.getResources()) {
        if (resource.getID() == resoID) { // Check if the resource exists in the ResourceManager
            // Resource exists, proceed

            // If a reservation ID was provided e.g. through a canclled reservation being restored
            // check if it already exists and clear it to prevent duplicates.
            // This is to prevent a edge-case where the maxID reservation is cancelled, 
            // a new reservation is made (making it the new maxID with the same ID as the cancelled reservation),
            // then restored, creating a duplicate reservation ID in the list.
            if (!id.empty()) {
                for (const auto& res : reservations) {
                    if (res.getID() == id) {
                        id = ""; // By making the id empty, it will naturally generate a new one with the next block of code.
                        break;
                    }
                }
            }
           
            // If no reservation ID was provided, generate a new reservation ID based on the reservations in the list.
            if (id.empty()) {
                    // Check to see if there are any reservations.
                    if (!reservations.empty()){
                        int maxID = 0;
                        for (const auto& res: reservations){ maxID = max(maxID, stoi(res.getID())); } // This finds the highest resevation ID and sets it to maxID. 
                        id = to_string(maxID + 1); // Then just make the new reservation ID 1 after the highest.
                        for (int i = id.length(); i < 3; ++i) { // pad the ID with leading zeros to ensure it is always 3 digits long
                            id = "0" + id;
                        }
                    }
                else{ // If reservation ID is not provided and there are no reservatons made, then this will be the first reservation. Thus, give it the 001 ID.
                    id = "001";
                }
            }

            // Create a new reservation with the provided ID
            Reservation newReservation(id, date, resource, Student(stuID, stuName));

            // Bypss validation if told to by the call (used in loadFile).
            if(!bypass){
                if (!ValidateReservation(newReservation, rm, wl)) {
                    //cout << "Reservation validation failed." << endl;
                    return false; // Validation failed
                }
            }
            reservations.push_back(newReservation);

            if(!bypass){
            cout << "Reservation created successfully with ID: " << id << endl;
            }
            return true; // Successfully created the reservation
        }
    }

    if(!bypass){
        cout << "Error: Resource with ID {" << resoID << "} does not exist." << endl;
    }
    return false; // Resource does not exist
}

bool ReservationManager::loadFile(const string& filename, ResourceManager& rm, WaitingList& wl) { 
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl; // Error message for file failure
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

        // Bypass validation for pre-existing file records.
        createReservation(id, stuID, stuName, resoID, date, rm, wl, true); // Create a new reservation with the parsed data
    }

    file.close();
    return true; // Successfully loaded the file
}

// --- CANCEL ---
bool ReservationManager::cancelReservation(const string& id, ResourceManager& rm, CancellationHistory& ch, WaitingList& wl) {
    for (auto it = reservations.begin(); it != reservations.end(); ++it) { // Must use an iterator to use erase() 
        if (it->getID() == id) { // Find the reservation to cancel
            ch.AddHistory(*it);
            string resourceToFree = it->getResourceID(); // Get the resource for the reservation
            string dateToFree = it->getDate(); // Get the date for the reservation
            reservations.erase(it); // Remove the reservation from the list
            
            bool reservedByAnother = false; // Check if any other reservations use that resource for the same date.
            for(const auto& res: reservations){
                if (res.getResourceID() == resourceToFree && res.getDate() == dateToFree){
                    reservedByAnother = true;
                    break;
                }
            }
            
            for (auto& resource : rm.getResources()){ // If someone else was waiting for the resource, make their reservation now.
                if(resource.getID() == resourceToFree){
                    if (!reservedByAnother){
                        Student nextInLine;
                        string nextDate = "";
                        // nextInLine will be set to the next student in line for the resource, and nextDate will be set to the date they requested through checkWaiting().
                        if (wl.checkWaiting(resourceToFree, nextInLine, nextDate)) { 
                            string newID = ""; // let createReservation auto-generate it
                            cout << "Resource ID " << resourceToFree << " is now open for "<< dateToFree 
                            << ". Making reservation for [" << nextInLine.getID() << "] " << nextInLine.getName() << " on " << nextDate << endl;
                            createReservation(newID, nextInLine.getID(), nextInLine.getName(), resourceToFree, nextDate, rm, wl);
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

// --- VALIDATE---
bool ReservationManager::ValidateReservation(const Reservation& resv, ResourceManager& rm, WaitingList& wl) const {
    const string& studentID = resv.getStudentID();
    const string& studentName = resv.getStudentName();
    const string& resourceID = resv.getResourceID();
    const string& date = resv.getDate();

    // Check that all inputted fields are non-empty. 
    // ResourceID is checked when creating the reservation 
    // and ReservationID is generated automatically
    if (!studentID.empty() && !studentName.empty() && !date.empty()) {

        // Check that the student ID is numeric
        for (char c : studentID) {
            if (!isdigit(c)) {
                cout << "Error: Student ID is not numeric." << endl;
                return false;
            }
        }

        // Check that the date is in the correct format e.g., 09/23/2026 (MM/DD/YYYY)
        if (date.length() != 10 || date[2] != '/' || date[5] != '/') {
            cout << "Error: Date must be in the format MM/DD/YYYY." << endl;
            return false;
        } else if (date[0] > '1' || (date[0] == '1' && date[1] > '2') || (date[0] == '0' && date[1] == '0')) {
            cout << "Error: Invalid month." << endl;
            return false;
        } else if (date[3] > '3' || (date[3] == '3' && date[4] != '0' && date[4] != '1')) { // Does not account for months with fewer than 30 days.
            cout << "Error: Invalid day." << endl;
            return false;
        }
    }
    else{
        cout << "Error: Empty reservation data." << endl;
        return false; 
    }

    for(const auto& reso : rm.getResources()){ // Check if the resource itself is available.
        if(reso.getID() == resourceID){
            if(!reso.isAvailable()){
                cout << "Error: Resource is currently unavailable." << endl;
                return false;
            }
            break;
        }
    }

    // Check that the resource ID isn't already reserved for the given date
    for (const auto& res : reservations) {
        // If the resource is already reserved, add the student to the waiting-list for that resource
        if (res.getResourceID() == resourceID && res.getDate() == date) {
            cout << "Resource already has an active reservation for the given date." << endl;
            cout << "Adding [" << studentID << "] " << studentName << " to the queue for Resource: " << resourceID << endl;
            wl.AddStudent(Student(studentID, studentName), resourceID, date);
            return false;
        }
    }
 
    return true; // All validations passed
}

// --- SEARCH ---


// --- DISPLAY ---
void ReservationManager::DisplayReservations() const {
    // Check to see if there are any reservations
    if (reservations.empty()) {
        cout << "There are no active reservations." << endl;
        return;
    }
    
    int count = 0;
    printHeader();
    // Print out the information for every reservation
    for (const auto& res : reservations) {
        res.display();
        count++;
    }
    cout << endl << "There are currently " << count << " active reservations..." << endl;
}

// --- REPORT ---
void ReservationManager::reportResourceUse(const vector<Resource>& resources) const{
    
    // Print header
    cout << left
         << setw(20) << "Resource"
         << "# of Reservations"
         << endl;
    cout << string(40, '-') << endl; // Line of dashes for separation

    // For every resource, check how many reservations are present for it.
    for(int i = 0; i < (int)resources.size(); i++){
        int count = 0;

        for(const Reservation& res: reservations){
            if(res.getResourceID() == resources[i].getID()){
                count++;
            }
        }

        // Print the resource and its number of active resorvations
        // Because it prints directly from the resource vector, it will print in the order that is currently sorted.
        cout << left
        << setw(25) << resources[i].getName() 
        << (count == 0 ? "(none)" : to_string(count)) 
        << endl;
    }
}

void ReservationManager::reportMostWanted(const vector<Resource>& resources, const WaitingList& wl) const{
    
    struct Rank{ // Simple struct to bundle resources with their counts of active reservations (aCount) and waiting reservations (wCount)
        Resource resource;
        int tCount; // aCount + wCount = tCount (total requests)
        int aCount;
        int wCount;
    };

    vector<Rank> rankings; // Vector to store the ranks, is sorted later using selection sort in descending order.
    vector<RequestCount> waitCounts = wl.getWaitingCounts(); // Get the waiting-list information

    // Print header
    cout << left
         << setw(10) << "Ranking"
         << setw(20) << "Resource"
         << "Total Requests (Active | Waiting)"
         << endl;
    cout << string(55, '-') << endl; // Line of dashes for separation

    // For every resource get their counts of active reservations and waiting-list reservations
    for(int i = 0; i < (int)resources.size(); i++){

        // Active reservations count
        int activeCount = 0;
        for(const Reservation& res: reservations){
            if(res.getResourceID() == resources[i].getID()){
                activeCount++;
            }
        }

        // Waiting-list reservations count
        int waitingCount = 0;
        for(const auto& wait: waitCounts){
            if(wait.resoID == resources[i].getID()){
                waitingCount = wait.count;
                break;
            }
        }

        // Put the counts to their rank and add it to the rankings vector, but only if there are counts
        if((activeCount + waitingCount) > 0){     
            Rank r;
            r.resource = resources[i];
            r.tCount = activeCount + waitingCount;
            r.aCount = activeCount;
            r.wCount = waitingCount;
            rankings.push_back(r);
        }
    }

    int n = rankings.size();
    if (n == 0) {
        cout << "No resources have any active or waiting reservations." << endl;
        return;
    }

    int slots = (n < 5) ? n : 5; // Slots are the number or rankings to display, by default it is up to 5. If there are less than 5, this ensures that it will only print as much as is present.
    
    // For every slot fill it with a rank
    for(int i = 0; i < slots; i++){
        
        // Get the index of the maximum/most requested resource.
        int index_of_max = i;
        for(int j = i + 1; j < n; j++){
            if(rankings[j].tCount> rankings[index_of_max].tCount){
                index_of_max = j;
            }
        }

       // Sort the rankings vectors in descending order using selection sort (swaps the max into where it belongs) after every check for the max.
       // The previous max naturally becomes the next highest. 
       if(index_of_max != i){
            Rank temp = rankings[i];
            rankings[i] = rankings[index_of_max];
            rankings[index_of_max] = temp;
       }
    }

    // Print out the 1st up to the 5th (slot dependent) most requested resources
    for(int i = 0; i < slots; i++){
        cout << left
        << setw(10) << (i == 0 ? "1st" : (i == 1 ? "2nd" : (i == 2 ? "3rd" : (i == 3 ? "4th" : "5th"))))
        << setw(20) << rankings[i].resource.getName()
        << rankings[i].tCount << "  (" << rankings[i].aCount << " | " << rankings[i].wCount << ")"
        << endl;
    }

    if(!rankings.empty()){
    cout << endl << "There are " << (n - slots == 0 ? "no other requests..." : to_string(n - slots) + " other requests...") << endl;
    }
}
 
// --- GETTER ---
int ReservationManager::count() const {
    return static_cast<int>(reservations.size());
}