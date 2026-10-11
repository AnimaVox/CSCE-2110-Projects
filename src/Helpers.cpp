/*
- Original Author: D'Antae Leathers
*/

#include "../include/Helpers.h"
#include <string>
#include <sstream>

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
