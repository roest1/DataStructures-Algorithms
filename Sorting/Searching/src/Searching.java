package searching;

/**
 * @author rileyoest
 */
public class Searching {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        /**
        linear search:

        search for a specific value in the array
        iterate all elements of the array
        keep track of index when the value is encountered

        since the size of the search is directly proportional to the size of the array we find the solution ∈ Ο(n)
         */
        int[] array = {2, 4, 7, 3, 8, 1, 8, 5};

        int key = 5;
        
        System.out.println("Key found at index: " + Searching.linearSearch(array, key) + "from linear search");
        
        /**
        binary search:

        sort array by value
        locate by determining whether the value occurs in the first or second half of the array
        continue searching in the same manner
        
        since the size of the search is cut in half with each step we find the solution ∈ Ο(log(n))
        */
        System.out.println("Key found at index: " + Searching.binarySearch(array, key) + " from binary search ");
        

        // other algorithms:
        // encryption, decryption, compression, pathfindings ( graph algroithms ) , machine learning, artificial intelligence, bioinformatics
        
        // categories
        // brute force, greedy, recursive, backtracking, divide and conquer, dynamic programming, randomized
    }
    
    // the slowest it will run or worst case scenario is O(n) time complexity
    public static int linearSearch(int [] array, int key){
        for(int i = 0; i < array.length; i++){
            if(array[i] == key){
                return  i;
            }
        }
        return -1;
    }
    
    // the slowest it will run or worst case scenario is Ο(log(n))
    public static int binarySearch(int [] array, int key){
        int min = 0;
        int max = array.length -1;
    
        
        while(min <= max){
            int mid = (min + max)/2;
            
            if( array[mid] == key){
                return mid;
            }
            
            else if(array[mid] < key){
                min = mid +1;
            }
            else{
                max = mid - 1;
            }
            
            
        }
        return -1;
    }
}

