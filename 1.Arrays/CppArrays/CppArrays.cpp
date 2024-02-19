#include <iostream>
#include <vector>
#include <algorithm> // For sort() and reverse()

using namespace std;

int main() {
    // Fixed-size array declaration and initialization
    int fixedArray[5] = {5, 2, 3, 1, 4};

    // Accessing an element
    cout << "Element at index 2: " << fixedArray[2] << endl;

    // Sorting a fixed-size array
    sort(fixedArray, fixedArray + 5);
    cout << "Sorted Fixed Array: ";
    for(int i = 0; i < 5; i++) cout << fixedArray[i] << " ";
    cout << endl;

    // Reversing the sorted array
    reverse(fixedArray, fixedArray + 5);
    cout << "Reversed Fixed Array: ";
    for(int i = 0; i < 5; i++) cout << fixedArray[i] << " ";
    cout << endl;

    // Dynamic array (vector) declaration and initialization
    vector<int> vec = {5, 2, 3, 1, 4};

    // Adding an element to the vector
    vec.push_back(6);

    // Sorting the vector
    sort(vec.begin(), vec.end());

    // Accessing elements
    cout << "Sorted Vector: ";
    for(int i : vec) cout << i << " ";
    cout << endl;

    // Removing the last element
    vec.pop_back();

    // Finding an element (find the position of '3')
    auto it = find(vec.begin(), vec.end(), 3);
    if(it != vec.end()) cout << "Element '3' found at position: " << distance(vec.begin(), it) << endl;
    else cout << "Element not found" << endl;

    return 0;
}
