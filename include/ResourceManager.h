#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

//#include
#include <vector>
#include "Resource.h"
#include <fstream>
using namespace std;

enum class SortCriteria{
    ID,
    NAME,
    TYPE,
    STATUS
};

class ResourceManager {
    public:
        // LOAD FROM FILE
        // Reads "ID|Name|Type|Status" for each line from text file and stores as Resource objects  
        bool loadFile(const string& filename); // Example input: R101|Study Room 101|Study Room|Available

        // DISPLAY
        void displayAll() const; // Displays all resources
        void displayAvailable() const; // Displays only available resources

        // SEARCH
        vector<Resource> search(const string& keyword) const; // Sub-string search for resources, case-insensitive
        
        // SORT
        void sortResources(SortCriteria criteria); // Sorts the resources based on the specified criteria (ID, Name, Type, or Status)
        int count() const; // Returns the total number of resources

    private:
        vector<Resource> resources;

        // Helpers
        static vector<string> splitLine(const string& line, char delimiter); // Splits a line of text into parts by delimiter, then storess in vector
        static void printHeader(); // Prints the header for resource display
};

#endif