import java.util.Arrays;
import java.util.NoSuchElementException;


public class kArrayHeap {
    private int k;
    private int heapSize;
    private int [] heap;

    /**
     * Constructor *
     */
    public kArrayHeap(int capacity, int numChildren) {
        heapSize = 0;
        k = numChildren;
        heap = new int[capacity + 1];
        Arrays.fill(heap, -1);
    }

    /**
     * String printHeap()
     * 
     * @return prints the heap in order by index
     */
    protected void levelOrderTraversal() {
        System.out.print("\nlevel order = ");
        for (int i = 0; i < heapSize; i++) {
            System.out.print(heap[i] + " ");
        }
        System.out.println();
    }

   
    /**
     * Perform preorder traversal starting from the given index
     * 
     * @param index starting index for traversal
     */
    protected void preorderTraversal() {
        System.out.print("Pre order = ");
        preorderTraversal(0);
        System.out.println();
    }
    private void preorderTraversal(int index) {
        if (index >= heapSize) {
            return;
        }

        System.out.print(heap[index] + " ");

        for (int i = 1; i <= k; i++) {
            int childIndex = jthChild(index, i);
            preorderTraversal(childIndex);
        }
    }

    /**
     * Perform inorder traversal starting from the given index
     * 
     * @param index starting index for traversal
     */
    protected void inorderTraversal() {
        System.out.print("In order = ");
        inorderTraversal(0);
        System.out.println();
    }
    private void inorderTraversal(int index) {
        if (index >= heapSize) {
            return;
        }

        for (int i = 1; i <= k; i++) {
            int childIndex = jthChild(index, i);
            inorderTraversal(childIndex);

            if (childIndex < heapSize) {
                System.out.print(heap[childIndex] + " ");
            }
        }

        if (index == 0) {
            System.out.print(heap[index] + " ");
        }
    }

    /**
     * Perform postorder traversal starting from the given index
     * 
     * @param index starting index for traversal
     */
    protected void postorderTraversal() {
        System.out.print("Post order = ");
        postorderTraversal(0);
        System.out.println();
    }

    private void postorderTraversal(int index) {
        if (index >= heapSize) {
            return;
        }

        for (int i = 1; i <= k; i++) {
            int childIndex = jthChild(index, i);
            postorderTraversal(childIndex);
        }

        System.out.print(heap[index] + " ");
    }

    /**
     * void insert(x)
     * 
     * @param x element value to insert into k-array heap
     * @return void
     */
    protected void insert(int x) {
        if (isFull()) {
            throw new NoSuchElementException("Overflow Exception");
        }
        // percolate up
        heap[heapSize++] = x;
        heapifyUp(heapSize - 1);
    }

    /**
     * int delete()
     * 
     * @param i index of element to delete in k-array heap
     * @return value of element deleted
     */
    protected int delete(int i) {
        if (isEmpty()) {
            throw new NoSuchElementException("Underflow Exception");
        }
        int keyItem = heap[i];
        heap[i] = heap[heapSize - 1];
        heapifyDown(i);
        heapSize--;
        return keyItem;
    }

    /**
     * int findMin()
     * 
     * @return minimum element in k-array heap (first element)
     */
    protected int findMin() {
        if (isEmpty()) {
            throw new NoSuchElementException("Underflow Exception");
        }
        return heap[0];
    }


    private boolean isEmpty() {
        return heapSize == 0;
    }

    private boolean isFull() {
        return heapSize == heap.length - 1;
    }

    private void clear() {
        heapSize = 0;
    }


    /**
     * int parent(i)
     * @param i index of parent to return 
     * @return parent of element at index i
     */
    private int parent(int i) {
        return (i - 1) / k;
    }

    /**
     * int kthChild(i, j)
     * @param i index of parent
     * @param j th child of parent at index i
     * @return index of jth child of element at index i
     */

     private int jthChild(int i, int j) {
        return k * i + j;
     }

     /**
      * void heapifyUp(child)
      * @param child index to heapify up from 
      */
    private void heapifyUp(int child) {
        int temp = heap[child];
        while (child > 0 && temp < heap[parent(child)]) {
            heap[child] = heap[parent(child)];
            child = parent(child);
        }
        heap[child] = temp;
    }

    /**
     * void heapifyDown(i)
     * @param i index to heapify down 
     */
    private void heapifyDown(int i) {
        int child; 
        int temp = heap[i];
        while (jthChild(i, 1) < heapSize) {
            child = minChild(i);
            if (heap[child] < temp) {
                heap[i] = heap[child];
            } else {
                break;
            }
            i = child;
        }
        heap[i] = temp;
    }

    /**
     * int minChild(i)
     * @param i index of parent to find child of minimum value
     * @return index of minimum child of parent at index i
     */
    private int minChild(int i) {
        int bestChild = jthChild(i, 1);
        int x = 2;
        int pos = jthChild(i, x);
        while (k <= x && pos < heapSize) {
            if (heap[pos] < heap[bestChild]) {
                bestChild = pos;
            }
            pos = jthChild(i, x++);
        }
        return bestChild;
    }
}
