/*
This class just holds some useful functions for managing strings.
Since these functions are used by both ResourceManager and ReservationManager for small tasks, I put them in their own file.
- Original Author: D'Antae Leathers
*/

/*
TODO: I implemented the template version of MergeSort, I'll leave it up to D'Antae to rename this so we know
this helper class now does more than help with strings.
- Dean Foote
 */

#ifndef STRING_HELPERS_H
#define STRING_HELPERS_H

#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class StringHelpers {
    public:
        vector<string> splitLine(const string& line, char delimiter); // Just splits the line of text by the delimiter, in this case it should always be "|"

        string toLower(const string& s) const; // Converts a string to lowercase
       // (The STL implementation of tolower() only works on single characters, so this is a helper to do it for the whole string)

       // Since we're not comparing simple numbers but member data, we use the comparator to use a lambda function
       // to determine what at runtime we are comparing (Type, Status, Name, ID)
       template<typename T> static void merge(vector<T>& vec, int left, int mid, int right, function<bool(const T&, const T&)> compare) {
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
               if (!compare(rightVec[j], leftVec[i])) { // We compare right to left because it would've taken the right object first on equality, which is unstable.
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

       template<typename T> static void mergeSort(vector<T>& vec, int left, int right, function<bool(const T&, const T&)> compare) {
           if (left >= right) return;

           int mid = left + (right - left) / 2;

           mergeSort(vec, left, mid, compare); // Sort left half
           mergeSort(vec, mid + 1, right, compare); // Sort right half
           merge(vec, left, mid, right, compare); // Merge the sorted halves
       }
};

#endif
