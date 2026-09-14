#include "ResourceManager.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

// --- LOAD FROM FILE ---
bool ResourceManager::loadFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl; // Using cerr for error messages
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

        vector<string> parts = splitLine(line, '|'); // Split the line into parts using '|' as the delimiter
        
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
void ResourceManager::displayAll() const {
    if (resources.empty()) {
        cout << "No resources to display." << endl;
        return;
    }

    printHeader();
    for (const auto& resource : resources) {
        resource.display();
    }
}

void ResourceManager::displayAvailable() const {
    bool foundAvailable = false;

    printHeader();
    for (const auto& resource : resources) {
        if (resource.isAvailable()) {
            resource.display();
            foundAvailable = true;
        }
    }

    if (!foundAvailable) {
        cout << "No available resources found." << endl;
    }
}

// --- SEARCH ---
vector<Resource> ResourceManager::search(const string& keyword) const {
    vector<Resource> results; // Vector to store search results

    // By converting both the keyword and resource names to lowercase, search can be made case-insensitive
    string lowerKeyword = keyword; // Copy of keyword, to be converted to lowercase
    transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower); // Convert keyword to lowercase

    for (const auto& resource : resources) {
        string lowerName = resource.getName(); // ONLY CHECKS THE NAME OF THE RESOURCE
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower); // Convert resource name to lowercase

        if (lowerName.find(lowerKeyword) != string::npos) { // Check if the keyword is a substring of the resource name
            results.push_back(resource);
        }
    }

    return results; // Return the vector of matching resources
}


// --- SORT ---

// --- HELPERS ---
vector<string> ResourceManager::splitLine(const string& line, char delimiter) {
    vector<string> parts;
    stringstream ss(line);
    string part;

    while (getline(ss, part, delimiter)) {
        parts.push_back(part);
    }

    return parts;
}

void ResourceManager::printHeader() {
    cout << left
         << setw(8) << "ID"
         << setw(20) << "Name"
         << setw(18) << "Type"
         << setw(12) << "Status"
         << endl;
    cout << string(58, '-') << endl; // Line of dashes for separation
}