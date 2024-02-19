# Arrays

* Arrays store elements in contiguous memory locations and allow direct access to elements using indices. 

### Basic Arrays

* **Access** $∈ Ο(1)$ - Direct access to any element using its index

* **Insertion/Deletion at an index** $∈ Ο(n)$ - Requires shifting elements to maintain order

* **Space Complexity** $∈ Ο(n)$ 

### Multi-Dimensional Arrays

* **Access** $∈ Ο(1)$ - Direct access to any element using its indices

* **Space Complexity** $∈ Ο(n×m)$ - For an $n×m$ array

### Dynamic Arrays

* **Access** $∈ Ο(1)$ - Direct access to any element using its index

* **Insertion at the end** $∈$ Amortized $Ο(1)$ - Typically, dynamic arrays double their size when they run out of space. While resizing is $Ο(n)$, it happens infrequently enough that the average time per insertion is constant

* **Deletion at the end** $∈ Ο(1)$

* **Insertion/Deletion at an index** $∈ Ο(n)$ - Requires resizing array

---

# Practice Problems


### Basic Array Manipulation

1. **Find the Maximum/Minimum Element**: Traverse an array to find its maximum or minimum element.

2. **Check if an Array is Sorted**: Determine whether an array is sorted in ascending or descending order.

3. **Reverse an Array**: Reverse the elements of an array in place.

4. **Rotate an Array**: Rotate the elements of an array to the right or left by a certain number of positions.

### Searching & Sorting

1. **Binary Search in a Sorted Array**: Implement binary search on a sorted array to find the index of a given element.

2. **First and Last Positions of an Element in a Sorted Array**: Find the first and last positions of a given element in a sorted array.

3. **Merge Two Sorted Arrays**: Merge two sorted arrays into one sorted array.

4. **Find the "Kth" Max/Min Element**: Determine the kth largest or smallest element in an unsorted array.

### Two-Pointer Technique

1. **Pair with Given Sum**: Find if there is a pair with a given sum in an array.

2. **Three Sum Problem**: Find all unique triplets in the array which gives the sum of zero.

3. **Container With Most Water**: Given n non-negative integers representing an elevation map where the width of each bar is 1, find two lines, which, together with the x-axis forms a container, such that the container contains the most water.

### Subarray Problems

1. **Maximum Subarray Sum (Kadane’s Algorithm)**: Find the contiguous subarray within an array, containing at least one number which has the largest sum.

2. **Subarray with Given Sum**: Find a subarray that sums to a given value.

3. **Longest Substring Without Repeating Characters**: Find the length of the longest substring without repeating characters.

### Sliding Window

1. **Maximum Sum Subarray of Size K**: Given an array of integers and a number k, find the maximum sum of a subarray of size k.

2. **Longest Subarray with Sum K**: Find the longest subarray with sum equal to k.

3. **Count Occurrences of Anagrams**: Given a word and a text, return the count of the occurrences of anagrams of the word in the text.

### Dynamic Arrays & Implementation

1. **Implement a Dynamic Array**: Implement your own dynamic array class mimicking the functionality of the Python List or Java ArrayList.

2. **Merge Intervals**: Given a collection of intervals, merge all overlapping intervals.

3. **Insert Interval**: Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

### Advanced Problems

1. **Spiral Matrix**: Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

2. **Rotate Image**: You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

3. **Jump Game**: Given an array of non-negative integers, you are initially positioned at the first index of the array. Each element in the array represents your maximum jump length at that position. Determine if you are able to reach the last index.

4. **First Missing Positive**: Given an unsorted integer array, find the smallest missing positive integer.