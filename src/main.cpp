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
#include "../include/WaitingList.h"
#include "../include/CancellationHistory.h"
#include <iostream> // cin, cout
using namespace std;

void clearLine() { // Small helper function that clears leftover input (e.g. after a bad menu choice)
    cin.ignore(1000, '\n');
}

void resetInput(){
    cin.clear();
    clearLine();
}

int main() {
    ResourceManager resManager;
    ReservationManager resvManager;
    WaitingList waitList;
    CancellationHistory cancels;

    // --- SETUP ---

    const string filenameRESOURCES = "data/resources.txt"; // Assume the filename for input is always "resources.txt", otherwise change this code.
    if (!resManager.loadFile(filenameRESOURCES)) {
        cout << "Could not load \"" << filenameRESOURCES << "\". Make sure it's in the 'data' folder." << endl;
        return 1; 
        // This will exit the program with a value of '1' i.e. anything other than 0 means something went wrong.
        // Can change this later so that the program just runs with no resources loaded if the file fails to load.
    }

    const string filenameRESERVATIONS = "data/reservations.txt"; // Assume the filename for input is always "reservations.txt", otherwise change this code.
    if (!resvManager.loadFile(filenameRESERVATIONS, resManager, waitList)) {
        cout << "Could not load \"" << filenameRESERVATIONS << "\". Make sure it's in the 'data' folder." << endl;
        return 1;
        // This will exit the program with a value of '1' i.e. anything other than 0 means something went wrong.
        // Can change this later so that the program just runs with no reservations loaded if the file fails to load.
    }

    cout << "Loaded " << resManager.count() << " resources from " << filenameRESOURCES << "." << endl;
    cout << "Loaded " << resvManager.count() << " reservations from " << filenameRESERVATIONS << "." << endl;


    // --- USER INTERFACE / MENU ---

    int choice = -1;
    while (choice != 0) { // The menu that the user will see. They will then pick from the list of options and perform the corresponding action.
        cout << "\n==== Campus Resource Reservation System ====\n"
                  << "1. Manage Resources\n"
                  << "2. Manage Reservations\n"
                  << "3. View Waiting-List\n"
                  << "4. Generate Reports\n"
                  << "0. Exit\n"
                  << "Choose an option: ";

        if (!(cin >> choice)) { // If input failed i.e. something other than a number was inputted, error message and try again.
            if (cin.eof()) {return 0;}
            resetInput();
            choice = -1;
            cout << "Please enter a number.\n";
            continue;
        }
        clearLine();

        switch (choice) { // --- MAIN MENU ---
            case 1: { //  // --- SUB-MENU [RESOURCES] "Manage Resources" ---
                int subchoice = -1;
                while (subchoice != 0){
                    cout << "\n === Managing Resources ===\n"
                    << "1. Display All Resources\n"
                    << "2. Display Available Resources\n"
                    << "3. Search Resources\n"
                    << "4. Sort Resources\n"
                    << "0. Go Back\n"
                    << "Choose an option: ";

                    if (!(cin >> subchoice)) {
                        if(cin.eof()) {subchoice = 0; continue;}
                        resetInput();
                        subchoice = -1;
                        cout << "Please enter a number.\n";
                        continue;
                    }
                    clearLine();

                    switch (subchoice) {
                        case 1: { // Display All resources
                            cout << "\n-- All Resources --\n"; 
                            resManager.displayAll();
                            break;
                        }
                        case 2: { // Display Available resources
                            cout << "\n-- Available Resources --\n"; 
                            resManager.displayAvailable();
                            break;
                        }
                        case 3: { // Search Resources (by term) **** TO BE IMPLEMENTED ****
                            cout << "Enter a search term (matches ID, name, or type): "; 
                            string keyword;
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
                        case 4: { // Sort Resources (by term) **** TO BE IMPLEMENTED ****
                            cout << "Sort by: 1) ID  2) Name  3) Type  4) Status\n";
                            cout << "Choice: ";
                            int sortChoice;
                            if (!(cin >> sortChoice)) {
                                resetInput();
                                cout << "Invalid choice.\n";
                                break;
                            }
                            clearLine();

                            switch (sortChoice) {
                                case 1: resManager.sortResources(SortCriteria::ID); break;      // Using enum from ResourceManager.h
                                case 2: resManager.sortResources(SortCriteria::NAME); break;
                                case 3: resManager.sortResources(SortCriteria::TYPE); break;
                                case 4: resManager.sortResources(SortCriteria::STATUS); break;
                                default:
                                    cout << "Invalid choice.\n";
                                    continue;
                            }
                                
                            cout << "\n-- Sorted Resources " << 
                            (sortChoice == 1 ? "(by ID)" :
                            (sortChoice == 2 ? "(by Name)" :
                            (sortChoice == 3 ? "(by Type)" : "(by Status)"))) << " --\n";
                            resManager.displayAll();
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

            case 2: { // --- SUB-MENU [RESERVATIONS] "Manage Reservations"
                int subchoice = -1;
                while (subchoice != 0){
                    cout << "\n === Managing Reservations ===\n"
                    << "1. Display Active Reservations\n"
                    << "2. Create a Reservation\n"
                    << "3. Cancel a Reservation\n"
                    << "4. Undo Cancellation\n"
                    << "5. Search Reservations\n"
                    << "6. Sort Reservations\n"
                    << "0. Go Back\n"
                    << "Choose an option: ";

                    if (!(cin >> subchoice)) {
                        if(cin.eof()) {subchoice = 0; continue;}
                        resetInput();
                        subchoice = -1;
                        cout << "Please enter a number.\n";
                        continue;
                    }
                    clearLine();

                    switch (subchoice) {
                        case 1: { // Display Active Reservations
                            cout << "\n-- Active Reservations --\n"; 
                            resvManager.DisplayReservations();
                            break;
                        }
                        case 2: { // Create a Reservation
                            string id, studentID, studentName, resourceID, date;
                            cout << "Enter the following information:\n";
                            cout << "Student ID: "; getline(cin, studentID);
                            cout << "Student Name: "; getline(cin, studentName);
                            cout << "Resource ID: "; getline(cin, resourceID);
                            cout << "Date (MM/DD/YYYY): "; getline(cin, date);

                            id = ""; // The ID will be generated automatically.
                            resvManager.createReservation(id, studentID, studentName, resourceID, date, resManager, waitList);
                            break;
                        }
                        case 3: { // Cancel a Reservation
                            string removeID;
                            cout << "Enter the Reservation ID to cancel: ";
                            getline(cin, removeID);
                            resvManager.cancelReservation(removeID, resManager, cancels, waitList);
                            break;
                        }
                        case 4: { // Undo Cancellation
                            Reservation retrievedReservation = cancels.RestoreHistory();
                            string restoreID = retrievedReservation.getID();
                            string restoreStuID = retrievedReservation.getStudentID();
                            string restoreStuName = retrievedReservation.getStudentName();
                            string restoreResoID = retrievedReservation.getResourceID();
                            string restoreDate = retrievedReservation.getDate();

                            resvManager.createReservation(restoreID, restoreStuID, restoreStuName, restoreResoID, restoreDate, resManager, waitList);
                            break;
                        }
                        case 5: { // Search Reservations **** TO BE IMPLEMENTED ****
                            cout << "This feature is not yet implemented... \n";
                            break;
                        }
                        case 6: { // Sort Reservations **** TO BE IMPLEMENTED ****
                            cout << "This feature is not yet implemented...\n";
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

            case 3: { // View Waiting List
                cout << "\n-- Waiting-List --\n"; 
                waitList.DisplayWaiting();
                break;
            }

            case 4: { // --- SUB-MENU [REPORTS] "Generate Reports"
                int subchoice = -1;
                while (subchoice != 0){
                    cout << "\n === Generating Reports ===\n"
                    << "1. Report Resource Utilization\n"
                    << "2. View Most Requested Resources\n"
                    << "3. Report Waiting-list statistics\n"
                    << "0. Go Back\n"
                    << "Choose an option: ";

                    if (!(cin >> subchoice)) {
                        if(cin.eof()) {subchoice = 0; continue;}
                        resetInput();
                        subchoice = -1;
                        cout << "Please enter a number.\n";
                        continue;
                    }
                    clearLine();

                    switch (subchoice) {
                        case 1: { // Report Resource Utilization
                            cout << "\n-- Current Resource Utilization --\n"; 
                            resvManager.reportResourceUse(resManager.getResources());
                            break;
                        }
                        case 2: { // View Most Requested Resources
                            cout << "\n-- Most Requested Resources --\n";
                            resvManager.reportMostWanted(resManager.getResources(), waitList);
                            break;
                        }
                        case 3: { // Report Waiting-list Statistics
                            cout << "\n-- Current Waiting-List Status --\n";                             
                            waitList.reportWaiting();
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