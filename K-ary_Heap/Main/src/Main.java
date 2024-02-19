import java.io.FileNotFoundException;
import java.io.File;
import java.util.Scanner;

public class Main {
    public static void main(String [] args) throws FileNotFoundException {
        File file = new File("/Users/rileyoest/VS_Code/k-ary_Heap/src/inputFile.txt");
        Scanner scan = new Scanner(file);
        int numDirections = scan.nextInt();
        Heap heap = new Heap(numDirections, 3);
        int lastEM = 0;
        for (int i = 1; i <= numDirections;) {
            String function = scan.next();

            if (function.equals("IN")) {
                heap.insert(scan.nextInt());
            }
            else if (function.equals("EM")) {
                heap.H_size--;
                lastEM = heap.extractMin();
            }
            else if (function.equals("DK")) {
                heap.H_size--;
                heap.decreaseKey(scan.nextInt(), scan.nextInt()); // index, newElement
            }
            i++;
        }
        scan.close();
        System.out.printf("Last Extract Min value = %d", lastEM); // answer from last EM
    }
}
