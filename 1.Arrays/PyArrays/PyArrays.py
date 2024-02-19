# Python list as dynamic array

# Initializing a list
arr = [5, 2, 3, 1, 4]

# Accessing an element
print(f"Element at index 2: {arr[2]}")

# Adding an element to the end
arr.append(6)
print(f"After appending 6: {arr}")

# Sorting the list
arr.sort()
print(f"Sorted list: {arr}")

# Reversing the list
arr.reverse()
print(f"Reversed list: {arr}")

# Removing an element by value
arr.remove(3)  # Removes the first occurrence of 3
print(f"After removing 3: {arr}")

# Inserting an element at a specific position
arr.insert(2, 7)  # Inserts 7 at index 2
print(f"After inserting 7 at index 2: {arr}")

# Finding an element
if 4 in arr:
    print(f"Element 4 found at index: {arr.index(4)}")
else:
    print("Element not found")
