/*
- Original Author: D'Antae Leathers
*/

#include "../include/ResourceManager.h"
#include <iostream> // cin, cout, cerr
#include <iomanip> // setw
#include <algorithm> //transform, find
#include <cctype> // tolower
#include <fstream> // ifstream (used to read file)
#include <sstream> // stringstream (used to easily convert digits into actual strings and split by delimiter)

// --- LOAD FROM FILE ---
bool ResourceManager::loadFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl; // Using cerr for error messages. Writes immediately for debugging
        return false; // If file cannot be opened, return false
    }

    resources.clear(); // Clear existing resources before loading new ones

    string line;
    int lineNumber = 0; // Keep track of the line number for error reporting

    while (getline(file, line)) {
        lineNumber++;

        if (line.empty()) {
            continue; // Skip empty lines
        }

        vector<string> parts = strhlp.splitLine(line, '|'); // Split the line into parts using '|' as the delimiter

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

    printHeader();
    for (const auto& resource : resources) {
        resource.display();
    }
}

void ResourceManager::displayAvailable() const { // Display only Available resources
    bool foundAvailable = false;

    printHeader();
    for (const auto& resource : resources) {
        if (resource.isAvailable()) {
            resource.display();
            foundAvailable = true;
        }
    }

    if (!foundAvailable) { // If there are no Available resources, print this.
        cout << "No available resources found." << endl;
    }
}

// --- SEARCH ---

vector<Resource> ResourceManager::search(const string& keyword) const {
    vector<Resource> results; // Vector to store search results

    // By converting both the keyword and resource parts to lowercase, search is made case-insensitive
    string lowerKeyword = strhlp.toLower(keyword); // Copy of keyword, converted to lowercase

    for (const auto& resource : resources) { // Check if the keyword is a substring i.e. is the keyword present?
        // Using .find() is a form of Linear Search. 
        // It checks each character in the string until it finds a match or reaches the end of the string.
        if(strhlp.toLower(resource.getID()).find(lowerKeyword) != string::npos || // Checking ID
           strhlp.toLower(resource.getName()).find(lowerKeyword) != string::npos || // Checking Name
           strhlp.toLower(resource.getType()).find(lowerKeyword) != string::npos){ // Checking Type
           // No need to check status, it only matters if it is "Available"
            results.push_back(resource);
        }
    }
    return results; // Return the vector of matching resources
}

// --- SORT ---
void ResourceManager::sortResources(SortCriteria criteria) {
    switch (criteria) { // Switch case employing the use of the enum
        case SortCriteria::ID:
            sort(resources.begin(), resources.end(),
                      [](const Resource& a, const Resource& b) {
                          return a.getID() < b.getID(); // Sort by ID
                      });
            break;
        case SortCriteria::NAME:
            sort(resources.begin(), resources.end(),
                      [](const Resource& a, const Resource& b) {
                          return a.getName() < b.getName(); // Sort by Name
                      });
            break;
        case SortCriteria::TYPE:
            sort(resources.begin(), resources.end(),
                      [](const Resource& a, const Resource& b) {
                          return a.getType() < b.getType(); // Sort by Type
                      });
            break;
        case SortCriteria::STATUS:
            sort(resources.begin(), resources.end(),
                      [](const Resource& a, const Resource& b) {
                          return a.getStatus() < b.getStatus(); // Sort by status (Availability)
                      });
            break;
    }
}

int ResourceManager::count() const { // Simply returns the total number of resources in the vector.
    return static_cast<int>(resources.size());
}

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

// Getters
vector<Resource>& ResourceManager::getResources(){
    return resources; // Returns a reference to the vector of resources
}