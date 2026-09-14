/*
 * WaitingList.h
 * 
 * Waiting List Management module for the Campus Resource Reservation System.
 *
 * Design:
 *   - WaitingStudent   : one node's worth of data (a student waiting for
 *                        a specific resource).
 *   - WaitingList      : a single FIFO queue of WaitingStudent, built as a
 *                        singly linked list with front/rear pointers.
 *                        This is what appears on the team whiteboard as
 *                        "WAITING_LIST" with AddStudent / RemoveStudent /
 *                        DisplayWaiting.
 *   - WaitingListManager: holds one WaitingList per resource (keyed by
 *                        resourceID), so ReservationManager can say
 *                        "resource X is full, put this student on X's
 *                        waiting list" without every resource sharing one
 *                        big queue.
 */

#ifndef WAITING_LIST_H
#define WAITING_LIST_H

#include <string>
#include <vector>

// WaitingStudent: the payload stored in each queue node.
// Mirrors the STUDENT object on the whiteboard (studID, studName) plus
// which resource they're waiting for.

struct WaitingStudent {
    int studID;
    std::string studName;
    int resourceID;

    WaitingStudent()
        : studID(-1), studName(""), resourceID(-1) {}

    WaitingStudent(int id, const std::string& name, int resID)
        : studID(id), studName(name), resourceID(resID) {}
};

// Internal linked-list node. Not exposed outside this file.

struct WaitingNode {
    WaitingStudent data;
    WaitingNode* next;

    WaitingNode(const WaitingStudent& s) : data(s), next(nullptr) {}
};


// WaitingList: FIFO queue for ONE resource's line of waiting students.

class WaitingList {
private:
    WaitingNode* front;   // next student to be served
    WaitingNode* rear;    // most recently added student
    int count;

public:
    WaitingList();
    ~WaitingList();

    // Disable copying to avoid shallow-copy pointer bugs (rule of 3/5).
    WaitingList(const WaitingList& other) = delete;
    WaitingList& operator=(const WaitingList& other) = delete;

    // Add a student to the back of the line. O(1).
    // Returns false if the student is already waiting in this list.
    bool AddStudent(int studID, const std::string& studName, int resourceID);

    // Remove and return the student at the front of the line. O(1).
    // Returns true and fills 'removed' if the list was non-empty.
    bool RemoveStudent(WaitingStudent& removed);

    // Look at (but don't remove) the front of the line. O(1).
    bool PeekFront(WaitingStudent& out) const;

    // Print the whole waiting list in order, front to back. O(n).
    void DisplayWaiting() const;

    // Remove a specific student from anywhere in the line (e.g. they
    // cancel their interest before being served). O(n).
    bool RemoveStudentByID(int studID);

    bool IsEmpty() const;
    int Size() const;
};


// WaitingListManager: one WaitingList per resourceID.

class WaitingListManager {
private:
    struct Entry {
        int resourceID;
        WaitingList* list;
    };
    std::vector<Entry> lists;

    WaitingList* GetOrCreate(int resourceID);
    WaitingList* Find(int resourceID) const;

public:
    WaitingListManager();
    ~WaitingListManager();

    bool AddStudent(int resourceID, int studID, const std::string& studName);
    bool RemoveStudent(int resourceID, WaitingStudent& removed);
    void DisplayWaiting(int resourceID) const;
    void DisplayAll() const;
    int Size(int resourceID) const;
};
#endif