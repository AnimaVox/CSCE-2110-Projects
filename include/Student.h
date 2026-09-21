/*
This class creates "Student" objects. Student objects, have a {id} and {name}. 
- Original Author: D'Antae Leathers
*/

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

class Student{
    private:
        string id;       // e.g. "1001"
        string name;     // e.g. "John Smith"

    public:
        Student();     // Default Constructor
        Student(const string& id, const string& name);

        // Getters
        string getID() const;
        string getName() const;

        // Setters
        void setID(const string& newID);
        void setName(const string& newName);

        //Helpers
        void display()const;        // Display the student information in one formatted line.
};

#endif