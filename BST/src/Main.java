import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
        BinarySearchTree bst = new BinarySearchTree();
        File inputFile = new File("inputFile.txt");
        Scanner scan = new Scanner(inputFile);
        int num_Directions = scan.nextInt();
        for (int i = 0; i < num_Directions;) {
            String function = scan.next();
            int param1 = scan.nextInt();
            int param2 = scan.nextInt();
            if (function.equals("IN")) {
                Node obj = new Node(param1, param2);
                System.out.printf("Inserting %d @ index : %d\n", param2, param1);
                bst.insert(obj);
                bst.maintainMinData(obj);
                //bst.illustrateTree();
            }
            if (function.equals("RMQ")) {
                System.out.printf("Range minimum query between indicies: [%d, %d] = %d\n", param1, param2, bst.RMQ(param1, param2, bst.rootOfBST()));
            }
            i++;
        }
        scan.close();
        System.out.println("====================================================================");
        bst.illustrateTree();
    }
}