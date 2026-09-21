/*
This class just holds some useful functions for managing strings. 
Since these functions are used by both ResourceManager and ReservationManager for small tasks, I put them in their own file.
- Original Author: D'Antae Leathers
*/

#ifndef STRING_HELPERS_H
#define STRING_HELPERS_H

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class StringHelpers {
    public:
        vector<string> splitLine(const string& line, char delimiter); // Just splits the line of text by the delimiter, in this case it should always be "|"
        
        string toLower(const string& s) const; // Converts a string to lowercase 
       // (The STL implementation of tolower() only works on single characters, so this is a helper to do it for the whole string)
};

#endif