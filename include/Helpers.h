/*
This class just holds some useful functions for managing strings.
Since these functions are used by both ResourceManager and ReservationManager for small tasks, I put them in their own file.
- Original Author: D'Antae Leathers
- Editor: Dean Foote
*/

#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>

using namespace std;

class Helpers {
    public:
        vector<string> splitLine(const string& line, char delimiter); // Just splits the line of text by the delimiter, in this case it should always be "|"

        string toLower(const string& s) const; // Converts a string to lowercase
        // (The STL implementation of tolower() only works on single characters, so this is a helper to do it for the whole string)

        // A helper to perform a more robust date validation. Used by ReservationManager::ValidateReservation()
        string checkDate(const string& date) const;

        // Returns true if 'substring' appears anywhere inside 'text', case-insensitive
        // This is a manual implementation of substring search, which is a linear search algorithm. 
        // It checks each character in the text until it finds a match or reaches the end of the text.
        bool containsSubstring(const string& text, const string& substring) const;

        // The following two functions are manual template implementations of MergeSort and Merge, they can be used together to sort any *vector* of objects
        // Template merge implementation
        template<typename T, typename Compare> static void merge(vector<T>& vec, int left, int mid, int right, Compare compare) {
            int n1 = mid - left + 1;
            int n2 = right - mid;
            vector<T> leftVec(n1), rightVec(n2);

            for (int i = 0; i < n1; i++) { // Copying the data into temporary vectors
                leftVec[i] = vec[left + i];
            }
            for (int j = 0; j < n2; j++) {
                rightVec[j] = vec[mid + 1 + j];
            }

            int i = 0, j = 0, k = left;
            // Because these aren't something simple like ints, we use the comparator here instead
            while (i < n1 && j < n2) { // Merge the temp vectors back
                if (!compare(rightVec[j], leftVec[i])) { 
                    vec[k] = leftVec[i];
                    i++;
                } else {
                    vec[k] = rightVec[j];
                    j++;
                }
                k++;
            }
            while (i < n1) {
                vec[k] = leftVec[i];
                i++;
                k++;
            }

            while (j < n2) {
                vec[k] = rightVec[j];
                j++;
                k++;
            }
        }

        // Template mergeSort implementation
        template<typename T, typename Compare> static void mergeSort(vector<T>& vec, int left, int right, Compare compare) {
            if (left >= right) return;

            int mid = left + (right - left) / 2;

            mergeSort(vec, left, mid, compare); // Sort left half
            mergeSort(vec, mid + 1, right, compare); // Sort right half
            merge(vec, left, mid, right, compare); // Merge the sorted halves
        }

        //Manual template implementation of InsertionSort, it can be used to sort any *list* of objects
        template<typename T, typename Compare> static void insertionSort(list<T>& lists, Compare compare) {
            list<T> sorted; // The "Sorted" part of the list

            while (!lists.empty()) { // The idea being that we're emptying the orignal list into the sorted list to then move back into the orignal list once it's sorted
                auto current = lists.begin(); // Points to the next node to insert
                const T& value = *current; // "value" saves the current "value" so the code can compare it while moving the node

                // Quick check to make sure if the "sorted" list isn't already empty or if the "value" should belong at the end of the sorted list
                if (sorted.empty() || !compare(value, sorted.back())) {
                    sorted.splice(sorted.end(), lists, current); // Puts the "value" at the end of the "Sorted" list
                } else { // Else, search for where the "value" should be
                    auto position = sorted.begin();

                    while (position != sorted.end() && !compare(value, *position)) { // This includes moving the position past "equivalant values", this preserves the stability of the original order of said "equivalant values"
                        ++position;
                    }
                    sorted.splice(position, lists, current); // Moves the node at "current" out from the original list into the sorted list.
                }
            }
            
            lists.splice(lists.end(), sorted); // After the orignal list was emptied and sorted, tranfer the sorted list back into the orignal list.
        }
};

#endif
