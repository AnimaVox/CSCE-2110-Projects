/*
This class manages "Resource" objects. It loads them from a file, stores them in a vector, and facilities sorting and searching through said vector.
The code assumes the file will have the proper format i.e. "ID|NAME|TYPE|AVAILABILITY". If it doesn't there some validation including to catch that (Check the .cpp).
*/

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

//#include
#include "Resource.h"
#include <vector>

using namespace std;

enum class SortCriteria{ // Using an enum here to avoid arbitrary ints/strings to pass to sorting functions. 
    // The user will see a list of options which will be mapped to these enum values.
    ID,
    NAME,
    TYPE,
    STATUS
    // Could just use 1, 2, 3, 4 here instead for each value, yes. But then have to remember which number goes to what value.
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
        static vector<string> splitLine(const string& line, char delimiter); // Splits a line of text into parts by delimiter, then stores in vector
        static void printHeader(); // Prints the header for resource display
};

#endif