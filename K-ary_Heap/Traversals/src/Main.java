public class Main {
    public static void main(String [] args) throws Exception {

        int [] elements = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int[] moreElements = { 10, 11, 12 };

        kArrayHeap heap = new kArrayHeap(elements.length + moreElements.length, 3); // ternary heap array

        for (int element : elements) {
            heap.insert(element);
        }
        
        heap.levelOrderTraversal();
        heap.inorderTraversal();
        heap.preorderTraversal();
        heap.postorderTraversal();
        
        heap.delete(0);
        System.out.println("deleting minimum element: ");

        heap.levelOrderTraversal();
        heap.inorderTraversal();
        heap.preorderTraversal();
        heap.postorderTraversal();
        System.out.println("inserting 10, 11, 12:");
        
        for (int element : moreElements) {
            heap.insert(element);
        }

        heap.levelOrderTraversal();
        heap.inorderTraversal();
        heap.preorderTraversal();
        heap.postorderTraversal();
    }
}
