import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    public static void main(String [] args) throws FileNotFoundException {
        Trie trie = new Trie();
        File inputFile = new File("/Users/rileyoest/VS_Code/Trie/Files/WORDS.LST");
        Scanner scan = new Scanner(inputFile);
        int count = 0;
        while(scan.hasNext()){
            String word = scan.next();
            if(word.length() == 5) { trie.add(word); count += 1; }
        }
        System.out.printf("%d words added to trie successfuly\n", count);
    }
}