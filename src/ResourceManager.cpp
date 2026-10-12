/*
- Original Author: D'Antae Leathers
*/

#include "../include/ResourceManager.h"
#include <iostream> // cin, cout
#include <iomanip> // setw
#include <algorithm> //any_of
#include <fstream> // ifstream (used to read file)
#include <sstream> // stringstream (used to easily convert digits into actual strings and split by delimiter)

// --- HELPERS ---
void ResourceManager::printHeader() { // Makes an neat organized header. To be used when printing other info.
    cout << left
         << setw(8) << "ID"
         << setw(20) << "Name"
         << setw(25) << "Type"
         << setw(12) << "Status"
         << endl;
    cout << string(65, '-') << endl; // Line of dashes for separation
}

void ResourceManager::setStatus(const string& id,const string& status){ // Allows other classes that need to to set the status of resource, but by telling ResourceManager to do it since ResourceManager has direct access to the resource vector.
    for(int i = 0; i < static_cast<int>(resources.size()); i++){
        if(resources[i].getID() == id){
            resources[i].setStatus(status);
        }
    }
}

// --- LOAD FROM FILE ---
bool ResourceManager::loadFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl; // Error message for file failure
        return false; // If file cannot be opened, return false
    }

    resources.clear(); // Clear existing resources before loading new ones

    string line;
    int lineNumber = 0; // Keep track of the line number for error reporting

    while (getline(file, line)) {
        lineNumber++;

        if (!line.empty() && line.back() == '\r') {line.pop_back();} // Remove carriage return if present
        if (line.empty()) {continue;} // Skip empty lines

        vector<string> parts = hlp.splitLine(line, '|'); // Split the line into parts using '|' as the delimiter

        if (parts.size() != 4) { // Ensure that there are exactly 4 parts (ID, Name, Type, Status)
            cerr << "Warning: Line " << lineNumber << " in file " << filename << " has incorrect format." << endl;
            continue; // Skip this line and continue with the next one
        }

        resources.emplace_back(parts[0], parts[1], parts[2], parts[3]);
    }

    file.close();
    return true; // Successfully loaded the file
}

// --- DISPLAY ---
void ResourceManager::displayAll() const { // Displays all loaded resources
    if (resources.empty()) {
        cout << "No resources to display." << endl; // If there are no loaded resources, print this.
        return;
    }

    int count = 0;
    printHeader();
    for (const auto& resource : resources) {
        resource.display();
        count++;
    }
    cout << endl << "There are currently " << count << " resources being managed..." << endl;
}

void ResourceManager::displayAvailable() const { // Display only Available resources
    if (resources.empty()) {
        cout << "No resources to display." << endl; // If there are no loaded resources, print this.
        return;
    }
    
    // Check if there are any available resources
    bool anyAvailable = any_of(resources.begin(), resources.end(), [](const Resource& res) { return res.isAvailable(); });

    if (!anyAvailable) { // If there are no Available resources, print this.
        cout << "No available resources found." << endl;
        return;
    }

    int count = 0;
    printHeader();
    for (const auto& resource : resources) {
        if (resource.isAvailable()) {
            resource.display();
            count++;
        }
    }
    cout << endl << "There are currently " << count << " available resources..." << endl;
}

// --- SEARCH ---
vector<Resource> ResourceManager::search(const string& keyword) const {
    vector<Resource> results; // Vector to store search results

    for (const auto& resource : resources) { // Check if the keyword is a substring i.e. is the keyword present?
        // It checks each character in the string until it finds a match or reaches the end of the string i.e Linear Search
        if(hlp.containsSubstring(resource.getID(), keyword) || // Checking ID
           hlp.containsSubstring(resource.getName(), keyword) || // Checking Name
           hlp.containsSubstring(resource.getType(), keyword)){ // Checking Type
           // No need to check status
            results.push_back(resource);
        }
    }
    return results; // Return the vector of matching resources
}

// --- SORT --- //
void ResourceManager::sortResources(SortCriteriaReso criteria) {
    if (resources.empty()) {
        cout << "No resources to sort." << endl; // If there are no loaded resources, print this.
        return;
    }
    
    switch (criteria) { // Switch case employing the use of the enum
        case SortCriteriaReso::ID:
            hlp.mergeSort(resources, 0, resources.size() - 1,
                      [](const Resource& a, const Resource& b) {
                          return a.getID() < b.getID(); // Sort by ID
                      });
            break;
        case SortCriteriaReso::NAME:
            hlp.mergeSort(resources, 0, resources.size() - 1,
                      [](const Resource& a, const Resource& b) {
                          return a.getName() < b.getName(); // Sort by Name
                      });
            break;
        case SortCriteriaReso::TYPE:
            hlp.mergeSort(resources, 0, resources.size() - 1,
                      [](const Resource& a, const Resource& b) {
                          return a.getType() < b.getType(); // Sort by Type
                      });
            break;
        case SortCriteriaReso::STATUS:
            hlp.mergeSort(resources, 0, resources.size() - 1,
                      [](const Resource& a, const Resource& b) {
                          return a.getStatus() < b.getStatus(); // Sort by status (Availability)
                      });
            break;
    }
}

// --- GETTERS ---
int ResourceManager::count() const { // Simply returns the total number of resources in the vector.
    return static_cast<int>(resources.size());
}

const vector<Resource>& ResourceManager::getResources() const{
    return resources; // Returns a reference to the vector of resources
}
