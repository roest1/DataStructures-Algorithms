import java.io.FileReader;
import java.io.IOException;
import java.util.Comparator;
import java.util.Scanner;

/**
 * A testbed for an augmented implementation of an AVL tree
 * 
 * @author William Duncan, Riley Oest
 * @see AVLTreeAPI
 * 
 * <pre>
 * Date: 10/16/22
 * Course: CSC 3102 
 * Programming Project # 2
 * Instructor: Dr. Duncan
 * </pre>
 */

public class Dendrologist {

    public static void main(String[] args) throws IOException {
        String usage = "Dendrologist <order-code> <command-file>\n";
        usage += "  <order-code>:\n";
        usage += "  0 ordered by increasing string length, primary key, and reverse lexicographical order, secondary key\n";
        usage += "  -1 for reverse lexicographical order\n";
        usage += "  1 for lexicographical order\n";
        usage += "  -2 ordered by decreasing string\n";
        usage += "  2 ordered by increasing string\n";
        usage += "  -3 ordered by decreasing string length, primary key, and reverse lexicographical order, secondary key\n";
        usage += "  3 ordered by increasing string length, primary key, and lexicographical order, secondary key\n";
        if (args.length != 2) {
            System.out.println(usage);
            throw new IllegalArgumentException("There should be 2 command line arguments.");
        }
        AVLTree<String> avl;
        Comparator<String> cmp;
        int order_code = Integer.parseInt(args[0]);
        switch (order_code) {
            case 1 : order_code = 0;
                // 0 = Ordered by increasing string length, primary key, and reverse
                // lexicographical order, secondary key
                cmp = Comparator.comparingInt(String::length).thenComparing(Comparator.reverseOrder());
                avl = new AVLTree<>(cmp);
                break;
            case 2 : order_code = -1;
                // -1 = Reverse lexicographical order
                cmp = Comparator.reverseOrder();
                avl = new AVLTree<>(cmp);
                break;
            case 3 : order_code = 1;
                // 1 = Lexicographical order
                cmp = Comparator.naturalOrder();
                avl = new AVLTree<>(cmp);
                break;
            case 4 : order_code = -2;
                // -2 = Ordered by decreasing string length
                cmp = Comparator.comparingInt(String::length).reversed();
                avl = new AVLTree<>(cmp);
                break;
            case 5 : order_code = 2;
                // 2 = Ordered by increasing string length
                cmp = Comparator.comparingInt(String::length);
                avl = new AVLTree<>(cmp);
                break;
            case 6 : order_code = -3;
                // -3 = Ordered by decreasing string length, primary key, and reverse
                // lexicographical order, secondary key
                cmp = Comparator.comparingInt(String::length).reversed().thenComparing(Comparator.reverseOrder());
                avl = new AVLTree<>(cmp);
                break;
            case 7 : order_code = 3;
                // 3 - Ordered by increasing string length, primary key, and lexicographical order, secondary key
                cmp = Comparator.comparingInt(String::length).thenComparing(Comparator.naturalOrder());
                avl = new AVLTree<>(cmp);
                break;
            default : 
                System.out.println(usage);
                throw new IllegalArgumentException("Invalid Order Code");
        }
        String command_file = args[1];
        Scanner scan = new Scanner(new FileReader(command_file));
        while (scan.hasNextLine()) {
            String word = scan.next();
            if (word.equals("stats")) {
                System.out.println("Stats: size = " + avl.size() + ", height = " + avl.height() + ", #full-nodes = "
                        + avl.fullCount() + ", fibonacci? = " + avl.isFibonacci());
            } else if (word.equals("traverse")) {
                System.out.println("In-Order Traversal : ");
                avl.traverse(x -> System.out.printf("%s\n", x));
            } else if (word.equals("paths")) {
                System.out.print("Root-to-Leaf Paths : " + avl.genPaths().size());
                String line = avl.genPaths().toString();
                line = line.replace("[", "").replace("]", "").replace(",", "");
                System.out.println(line);
            } else if (word.equals("insert")) {
                String item = scan.next();
                avl.insert(item);
                System.out.println("Inserted : " + item);
            } else if (word.equals("delete")) {
                String item = scan.next();
                avl.remove(item);
                System.out.println("Deleted : " + item);
            }
            else {
                throw new IllegalArgumentException("Parsing Error.");
            }
        }
        scan.close();
    }
}

