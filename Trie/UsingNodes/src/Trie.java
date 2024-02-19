import java.io.FileNotFoundException;
import java.util.Scanner;
import java.io.File;

public class Trie {
    public static void main (String [] args) throws FileNotFoundException {
        File file = new File("/Users/rileyoest/VS_Code/Trie/Files/WORDS.LST");
        Scanner scan = new Scanner(file);
        Node trie = new Node();
        while(scan.hasNext()){
            String word = scan.next();
            if(word.length() == 5){ 
                trie.insert(trie.root, word);
            }
        }
        File queryFile = new File("/Users/rileyoest/VS_Code/Trie/Files/inputFile.txt");
        scan = new Scanner(queryFile);
        String prefix = scan.next();
        String forbidden = scan.next();
        trie.query(trie, prefix, forbidden); // qprefix, forbidden
        scan.close();
        System.out.printf("There are %d matches in %s with %s prefix and %s forbidden characters", trie.answer, file, prefix, forbidden);
    }
}