/*
- Original Author: D'Antae Leathers
*/

#ifndef REPORTING_H
#define REPORTING_H

#include "ReservationManager.h"
#include "ResourceManager.h"
#include "WaitingList.h"

class Reporting {
private:
    stack<Reservation> history; // Stack containing history of cancelled reservations

public:
    void ActiveReservations() const; // Reports the number of currently active reservations

    void UsedResources() const; // Reports the amount of resources being used.

    void MostWantedResources() const; // Reports the each resource and how many times they are reserved. Sorted in descending order from most reserved.

    void FufilledRequests() const; // Reports the number of reservations/requests successfully filled from the waiting list.

};

#endif