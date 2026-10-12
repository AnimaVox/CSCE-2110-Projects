# CSCE-2110-Projects
This repository contains the code, files, and version history for the *CSCE 2110 Project 1 — Campus Resource Reservation System* of

> D'Antae Leathers, Dean Foote, and Erin Sen

for the UNT 2026 Fall Semester

This program allows the user to create and manage reservations for a collection of resources.


--- INSTALLATION ---

To compile, please run the following command: g++ -o NAME_OF_CHOICE src/*.cpp
in the root directory.

Resources must be provided through resources.txt in the 'data' folder. Each line of text in the file represents one resource and is expected to follow the following format:
> ResourceID|Name of Resource|Resource Type|Availabilty

- ResourceID: An unique 3-digit number following 'R' e.g. "R101"
- Name of Resource: Any alphanumeric string that represents what the resource should be called e.g. "Study Room 101"
- Resource Type: A string that denotes the type of resouce, this should be consistent for every resource that shares the same type e.g. "Study Room"
- Availability: The string "Available" or "Unavailable" exactly as written to denote if a resource is open for booking. Note, this refers to the operational capacity of the resource, not whether or not the resource has already been reserved/.

Reservation may be provided through reservations.txt in the 'data' folder. Though it is not necessary. Each line of text in the file represents one resource and is expected to follow the following format:
> ReservationID|StudentID|Student Name|ResourceID|Date

- ReservationID: An unique 3-digit number e.g. "301"
- StudentID: An unique 4-digit number that denotes a particular student making the reservation e.g. "1001"
- Student Name: An alphabetic string for the name of the student making the reservation e.g. "Alice Smith"
- ResourceID: The same as those found in resources.txt. Reservations using a ResourceID not found in resources.txt may be invalidated.
- Date: A single string consisting of the format MM/DD/YYYY, where M is a digit of the month, D is a digit of the day, and Y is a digit of the year.

--- USAGE ---

Once the program is up and running, use the menu options to select and input a number of your choice corresponding the desired operation.
Here is the full menu tree:

> MAIN MENU
1. Manage Resources
2. Manage Reservations
3. View Waiting-List
4. Generate Reports
0. Exit

Choosing either option 1, 2, or 4 here will open up a sub-menu

> Manage Resources [SUB-MENU]
1. Display All Resources
2. Display Available Resources
3. Search Resources
4. Sort Resources
0. Go Back

> Manage Reservations [SUB-MENU]
1. Display Active Reservations
2. Create a Reservation
3. Cancel a Reservation
4. Display Cancellation History
5. Undo Cancellation
6. Search Reservations
7. Sort Reservations
0. Go Back

> Reporting [SUB-MENU]
1. Report Resource Utilization
2. View Most Requested Resources
3. Report Waiting-list statistics
0. Go Back

By returning to the Main Menu and selecting option 0, the program will exit.

For further explanation of all the features provided by each option please view the User Documentation.
