/*
This class manages "Resource" objects. It loads them from a file, stores them in a vector, and facilitates sorting and searching through said vector. The code assumes the file will have the proper format i.e. "ID|NAME|TYPE|AVAILABILITY". If it doesn't there is some validation include to catch that.
- Original Author: D'Antae Leathers
*/

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Resource.h"
#include "StringHelpers.h" // StringHelpers class for string manipulation
#include <vector>

using namespace std;

enum class SortCriteria{ // Using an enum here for readibility when calling sort functions
    ID,
    NAME,
    TYPE,
    STATUS
};

class ResourceManager {
    private:
        vector<Resource> resources;

        // Helpers
        static void printHeader(); // Prints the header for resource display
  
        StringHelpers strhlp; // Instance of StringHelpers for string manipulation    
    
    public:
        // Helpers
        void setStatus(const string& id, const string& status);
        
        // --- LOAD FROM FILE ---
        // Reads "ID|Name|Type|Status" for each line from text file and stores as Resource objects
        // Example input: R101|Study Room 101|Study Room|Available
        bool loadFile(const string& filename); 

        // --- DISPLAY ---
        void displayAll() const; // Displays all resources
        void displayAvailable() const; // Displays only available resources

        // --- SEARCH ---
        vector<Resource> search(const string& keyword) const; // Sub-string search for resources, case-insensitive
        
        // --- SORT ---
        void sortResources(SortCriteria criteria); // Sorts the resources based on the specified criteria (ID, Name, Type, or Status)

        // --- GETTERS ---
        int count() const; // Returns the total number of resources
        const vector<Resource>& getResources() const; // Returns a reference to the vector of resources

};

#endif