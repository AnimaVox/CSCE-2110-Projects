/*
- Original Author: D'Antae Leathers
*/

#include "../include/Helpers.h"
#include <string>
#include <sstream>
#include <cctype> // tolower

vector<string> Helpers::splitLine(const string& line, char delimiter) { // Just splits the line of text by the delimiter, in this case it should always be "|"
    vector<string> parts;
    stringstream ss(line);
    string part;

    while (getline(ss, part, delimiter)) {
        parts.push_back(part);
    }

    return parts;
}

string Helpers::toLower(const string& s) const {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), [](char c){return tolower(c);});
    return result;
}

string Helpers::checkDate(const string& date) const {
    //Check that the date is in the correct format e.g. 09/23/2026 (MM/DD/YYYY)
    const string formatError = "Date must be in the format MM/DD/YYYY."; // Return this if date is invalid

    if (date.length() != 10 || date[2] != '/' || date[5] != '/') { return formatError;} // Not long enough to be a date, '/' are in the wrong spots
    
    for(int i = 0; i < 10; i++){ // Check each character in the date string individually
        if (i == 2 || i == 5) {continue;} // skip over '/'
        if (date[i] < '0' || date[i] > '9') { return formatError;} // Not a digit
    }
    
    // Extract and isolate values to check for valid months, days, and year values
    // Subtracting '0' from a character results in subtracting its ASCII value, 
    // for numeric characters this works to convert them from string to their actual integer value without having to cast them as int.
    int month = (date[0] - '0') * 10 + (date[1] - '0');
    int day = (date [3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');

    if (month < 1 || month > 12) {return "Invalid month."; } // Month is not within the bound of 1 to 12
    if (year < 1) {return "Invalid year";} // Year is 0 or less

    int maxDay;
    if (month == 2) { // Check February (2nd month) for special cases since it does not have a similar amount of days to other months
        bool leap = (year % 4 == 0 && year % 100 !=0) || (year % 400 == 0); // Check if leap year, if so 02/29/YYYY would be valid, otherwise it must be 02/28/YYYY
        maxDay = leap ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) { // All the months with 30 days.
        maxDay = 30;
    } else { // If not Februray, or a month with 30 days, then it must be a month with 31 days.
        maxDay = 31;
    }

    if (day < 1 || day > maxDay) {return "Invalid day.";} // Day is negative or too much for the given month.

    return "";
}

bool Helpers::containsSubstring(const string& text, const string& substring) const { // Returns true if 'substring' appears anywhere inside 'text'
    if (substring.empty()) {return true;}   // An empty substring would match everything, so treat it as a match
    if (substring.size() > text.size()) {return false;}     // A substring longer than the text can never fit inside it
    
    // Convert both strings to lowercase for case-insensitive comparison
    string lowtext = toLower(text); 
    string lowsubstring = toLower(substring); 

    // Go through the text manually
    for(int i = 0; i <= text.length() - substring.length(); i++) { // Loop through the text, stopping when there isn't enough room left for the substring
        bool match = true;
        for(int j = 0; j < substring.length(); j++) { // Loop through the substring
            if(lowtext[i + j] != lowsubstring[j]) { // If any character doesn't match, break out of the loop
                match = false;
                break;
            }
        }
        if (match) {return true;} // Found the substring, return true
    }

    return false; // Could not find the substring anywhere in the text
}