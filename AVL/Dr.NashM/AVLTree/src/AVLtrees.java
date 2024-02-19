
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

/**
 *
 * @author rileyoest
 */
public class AVLtrees {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        Tree heap = new Tree();
        heap.insertElement(10);
        heap.insertElement(20);
        heap.insertElement(30);
        heap.insertElement(40);
        heap.insertElement(50);
        heap.insertElement(55);
        heap.insertElement(60);
        heap.insertElement(65);
        heap.insertElement(70);
        heap.insertElement(75);
        heap.insertElement(77);
        heap.insertElement(80);
        heap.insertElement(99);
        heap.insertElement(100);
        System.out.println("range report [10, 100]");
        heap.rangeReport(10, 100);
        System.out.println("");

    
        System.out.println("range report [20, 99]");
        heap.rangeReport(20, 99);
        System.out.println("");
        System.out.println("range report [30, 80]");
        heap.rangeReport(30, 80);
        System.out.println("");
        System.out.println("range report [40, 77]");
        heap.rangeReport(40, 77);
        System.out.println("");
        System.out.println("range report [50, 75]");
        heap.rangeReport(50, 75);
        System.out.println("");
        System.out.println("range report [55, 70]");
        heap.rangeReport(55, 70);
        System.out.println();

        heap.printInOrder();
        heap.printPreOrder();
        heap.printPostOrder();
        heap.printLevelOrder();
    }
}
