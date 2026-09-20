/*
    +-------------------------------------------------+
    |      Computer Science and Engineering           |
    |   CSCE 2110 - Foundations of Data Structures    |
    |         D'Antae Leathers | dal0295              |
    |          D'antaeLeathers@my.unt.edu             |
    |                                                 |
    |           Dean Foote | df0309                   |
    |           DeanFoote@my.unt.edu                  |
    |                                                 |
    |             Erin Sen | ps1003                   |
    |           prajuktaSen@my.unt.edu                |
    +-------------------------------------------------+

*/
#include "../include/ReservationManager.h"
#include "../include/ResourceManager.h"
#include <iostream> // cin, cout
using namespace std;

void clearInput() { // Small helper function that clears leftover input (e.g. after a bad menu choice)
    cin.clear();
    cin.ignore(100, '\n');
}

int main() {
    ResourceManager resManager;
    ReservationManager resvManager;

    const string filenameRESOURCES = "resources.txt"; // Assume the filename for input is always "resources.txt", otherwise change this code.
    if (!resManager.loadFile(filenameRESOURCES)) {
        cout << "Could not load \"" << filenameRESOURCES << "\". Make sure it's in the same folder as the program." << endl;
        return 1; 
        // This will exit the program with a value of '1' i.e. anything other than 0 means something went wrong.
        // Can change this later so that the program just runs with no resources loaded if the file fails to load.
    }

    const string filenameRESERVATIONS = "reservations.txt"; // Assume the filename for input is always "reservations.txt", otherwise change this code.
    if (!resvManager.loadFile(filenameRESERVATIONS, resManager)) {
        cout << "Could not load \"" << filenameRESERVATIONS << "\". Make sure it's in the same folder as the program." << endl;
        return 1;
        // This will exit the program with a value of '1' i.e. anything other than 0 means something went wrong.
        // Can change this later so that the program just runs with no reservations loaded if the file fails to load.
    }

    cout << "Loaded " << resManager.count() << " resources from " << filenameRESOURCES << "." << endl;
    cout << "Loaded " << resvManager.count() << " reservations from " << filenameRESERVATIONS << "." << endl;

    int choice = -1;
    while (choice != 0) { // The menu that the user will see. They will then pick from the list of options and perform the corresponding action.
        cout << "\n==== Campus Resource Reservation System ====\n"
                  << "1. View Resources\n"
                  << "2. View All Reservations\n"
                  << "3. Create a Reservation\n"
                  << "4. Cancel a Reservation\n"
                  << "5. View Waiting List\n"
                  << "6. Undo Cancellation\n"
                  << "7. Search Reservations\n"
                  << "8. Sort Resources\n"
                  << "9. Generate Report\n"
                  << "0. Exit\n"
                  << "Choose an option: ";

        if (!(cin >> choice)) { // If input failed i.e. something other than a number was inputted, error message and try again.
            clearInput();
            cout << "Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: { // View Resources
                int subchoice = -1;
                while (subchoice != 0){
                cout << "\n === Viewing Resources ===\n"
                  << "1. Display All Resources\n"
                  << "2. Display Available Resources\n"
                  << "3. Search Resources\n"
                  << "0. Go Back\n"
                  << "Choose an option: ";

                if (!(cin >> subchoice)) { // If input failed i.e. something other than a number was inputted, error message and try again.
                clearInput();
                cout << "Please enter a number.\n";
                continue;
                }

                switch (subchoice) {
                    case 1: { // Display All resources
                        cout << "\n-- All Resources --\n"; 
                        resManager.displayAll();
                        break;
                    }
                    case 2: { // Display Availabe resources
                        cout << "\n-- Available Resources --\n"; 
                        resManager.displayAvailable();
                        break;
                    }
                    case 3: { // Search by term
                        cout << "Enter a search term (matches ID, name, or type): "; 
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
                    case 0: // Go back to main menu
                        cout << "Returning to main menu.\n";
                        break;
                    default:
                        cout << "Invalid option, try again.\n";
                    }
                }
                break;
            }
            case 2: { // View All Reservations
                cout << "\n-- All Reservations --\n"; 
                resvManager.DisplayReservations();
                break;
            }
            case 3: { // Create a Reservation
                string id, studentID, studentName, resourceID, date;
                cout << "Enter the following information:\n";
                clearInput();
                cout << "Student ID: ";
                getline(cin, studentID);
                cout << "Student Name: ";
                getline(cin, studentName);
                cout << "Resource ID: ";
                getline(cin, resourceID);
                cout << "Date (MM/DD/YYYY): ";
                getline(cin, date);

                id = ""; // The ID will be generated automatically.
                resvManager.createReservation(id, studentID, studentName, resourceID, date, resManager);
                break;
            }
            case 4: { // Cancel a Reservation
                string removeID;
                cout << "Enter the Reservation ID to cancel: ";
                clearInput();
                getline(cin, removeID);

                resvManager.cancelReservation(removeID, resManager);
                break;
            }
            case 5: { // View Waiting List
                cout << "Feature not implemented yet.\n";
                break;
            }
            case 6: { // Undo Cancellation
                cout << "Feature not implemented yet.\n";
                break;
            }
            case 7: { // Search Reservations
                cout << "Feature not implemented yet.\n";
                break;
            }
            case 8: { // Sort resources. THIS IS A DIRECT OPERATION on the vector. YOU CANNOT UNSORT
                cout << "Sort by: 1) ID  2) Name  3) Type  4) Status\n" 
                     << "Choice: ";
                    int sortChoice;
                    if (!(cin >> sortChoice)) {
                        clearInput();
                        cout << "Invalid choice.\n";
                        break;
                    }

                    switch (sortChoice) {
                        case 1: resManager.sortResources(SortCriteria::ID); break;      // Using that enum from ResourceManager.h
                        case 2: resManager.sortResources(SortCriteria::NAME); break;
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
            case 9: { // Generate Report
                cout << "Feature not implemented yet.\n";
                break;
            }
            case 0: { // Exit message
                cout << "Thank you for using the Campus Resource Reservation System. Goodbye!\n";   
                break;
            }
            default:
                cout << "Invalid option, try again.\n"; // If the user doesn't choose a proper option, error message and go again
        }
    }
    return 0;
}