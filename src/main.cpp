/*
    +-------------------------------------------------+
    |      Computer Science and Engineering           |
    |   CSCE 2110 - Foundations of Data Structures    |
    |         D'Antae Leathers | dal0295              |
    |          D'antaeLeathers@my.unt.edu             |
    +-------------------------------------------------+
    THIS IS A BRANCH OF THE MAIN CODE. DO NOT MERGE THIS UNLESS OTHERWISE TOLD.
    I WILL ADD OTHER TEAM MEMBER NAMES TO THE MERGED VERSION
*/

#include "../include/ResourceManager.h"
#include <iostream> // cin, cout
using namespace std;

void clearInput() { // Small helper function that clears leftover input (e.g. after a bad menu choice)
    cin.clear();
    cin.ignore(100, '\n');
}

int main() {
    ResourceManager resManager;

    const string filename = "resources.txt"; // Assume the filename for input is always "resources.txt", otherwise change this code.
    if (!resManager.loadFile(filename)) {
        cout << "Could not load \"" << filename << "\". Make sure it's in the same folder as the program." << endl;
        return 1; 
        // This will exit the program with a value of '1' i.e. anything other than 0 means something went wrong.
        // Can change this later so that the program just runs with no resources loaded if the file fails to load.
    }

    cout << "Loaded " << resManager.count() << " resources from " << filename << ".\n" << endl;

    int choice = -1;
    while (choice != 0) { // The menu that the user will see. They will then pick from the list of options and perform the corresponding action.
        cout << "\n=== Resource Reservation System ===\n"
                  << "1. Display all resources\n"
                  << "2. Display available resources\n"
                  << "3. Search resources\n"
                  << "4. Sort resources\n"
                  << "0. Exit\n"
                  << "Choose an option: ";

        if (!(cin >> choice)) { // If input failed i.e. something other than a number was inputted, error message and try again.
            clearInput();
            cout << "Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                cout << "\n-- All Resources --\n"; // Display all resources
                resManager.displayAll();
                break;
            }
            case 2: {
                cout << "\n-- Available Resources --\n"; // Display Availabe resources
                resManager.displayAvailable();
                break;
            }
            case 3: {
                cout << "Enter a search term (matches ID, name, or type): "; // Search by term
                string keyword;
                clearInput();
                getline(cin, keyword);

                vector<Resource> results = resManager.search(keyword);
                if (results.empty()) {  // Term not found
                    cout << "No matches found.\n";
                } else {
                    cout << "\n-- Search Results (" << results.size() << ") --\n"; // Display all results that have the term
                    for (const auto& r : results) {
                        r.display();
                    }
                }
                break;
            }
            case 4: {
                cout << "Sort by: 1) ID  2) Name  3) Type  4) Status\n" // Sort resources. THIS IS A DIRECT OPERATION on the vector. YOU CANNOT UNSORT
                          << "Choice: ";
                int sortChoice;
                if (!(cin >> sortChoice)) {
                    clearInput();
                    cout << "Invalid choice.\n";
                    break;
                }

                switch (sortChoice) {
                    case 1: resManager.sortResources(SortCriteria::ID); break;      // Using that enum from ResourceManager.h
                    case 2: resManager.sortResources(SortCriteria::NAME); break;    // much easier to read "CHOICE" than "1" and then read have to read other code.
                    case 3: resManager.sortResources(SortCriteria::TYPE); break;
                    case 4: resManager.sortResources(SortCriteria::STATUS); break;
                    default:
                        cout << "Invalid choice.\n";
                        continue;
                }

                cout << "\n-- Sorted Resources --\n";
                resManager.displayAll();
                break;
            }
            case 0:
                cout << "Goodbye!\n";   // Exit message
                break;
            default:
                cout << "Invalid option, try again.\n"; // If the user doesn't choose a proper option, error message and go again
        }
    }

    return 0;
}