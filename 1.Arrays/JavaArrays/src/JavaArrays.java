import java.util.ArrayList;
import java.util.Collections;

public class JavaArrays {
    public static void main(String[] args) {
        // Fixed-size array initialization
        int[] fixedArray = {5, 2, 3, 1, 4};

        // Accessing an element
        System.out.println("Element at index 2: " + fixedArray[2]);

        // Sorting a fixed-size array
        java.util.Arrays.sort(fixedArray);
        System.out.print("Sorted Fixed Array: ");
        for(int i : fixedArray) System.out.print(i + " ");
        System.out.println();

        // Dynamic array (ArrayList) initialization
        ArrayList<Integer> arrayList = new ArrayList<>();
        Collections.addAll(arrayList, 5, 2, 3, 1, 4);

        // Adding an element
        arrayList.add(6);

        // Sorting the ArrayList
        Collections.sort(arrayList);

        // Accessing elements
        System.out.print("Sorted ArrayList: ");
        for(int i : arrayList) System.out.print(i + " ");
        System.out.println();

        // Removing an element by index
        arrayList.remove(Integer.valueOf(3));  // Removes the first occurrence of 3
        System.out.println("After removing 3: " + arrayList);

        // Inserting an element at a specific position
        arrayList.add(2, 7);  // Inserts 7 at index 2
        System.out.println("After inserting 7 at index 2: " + arrayList);

        // Finding an element
        if(arrayList.contains(4)) System.out.println("Element 4 found at index: " + arrayList.indexOf(4));
        else System.out.println("Element not found");
    }
}
