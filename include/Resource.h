/*
This class creates "Resource" objects. Resource objects, have a {id},{name},{type}, and {status}.
- Original Author: D'Antae Leathers
*/

#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
using namespace std;

class Resource{
    private:
        string id;       // e.g. "R101"
        string name;     // e.g. "Study Room 101"
        string type;     // e.g. "Study Room" / "Laptop" / "Calculator" / "Lab Equipment" / "Tutoring"
        string status;   // e.g. "Available" or "Unavailable"

    public:
        Resource();     // Default Constructor
        Resource(const string& id, const string& name, const string& type, const string& status);

        // Getters
        string getID() const;
        string getName() const;
        string getType() const;
        string getStatus() const;

        // Setters
        void setStatus(const string& newStatus);
        
        //Helpers
        bool isAvailable() const;   // Check if the resource is available, return false if unavailable
        void display()const;        // Display the resource information in one formatted line.
};

#endif