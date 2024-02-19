import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
        Trie trie = new Trie();
        File input = new File("/Users/rileyoest/VS_Code/Trie/Files/WORDS.LST");
        Scanner scan = new Scanner(input);
        while (scan.hasNext()) {
            String word = scan.next();
            if (word.length() == 5) {
                trie.insert(word);
            }
        }
        File queryFile = new File("/Users/rileyoest/VS_Code/Trie/Files/inputFile.txt");
        scan = new Scanner(queryFile);
        String prefix = scan.next();
        String forbidden = scan.next();
        trie.query(trie.root, prefix, forbidden); // qprefix, forbidden
        scan.close();
        System.out.printf("There are %d matches in %s with %s prefix and %s forbidden characters", trie.answer, input, prefix, forbidden);
        // char a = 'a';
        // System.out.println((int) a);
        // System.out.println(a - 'a');
        // char h = 'h';
        // System.out.println(h - 'a');
        // char z = 'z';
        // System.out.println(z - 'a');
        // ∴ we can pass a letter - 'a' to find its index in the alphabet array
    }

    /**
     * inputfile : "WORD.LST"
     * NEED TO ONLY PICK 5 LETTER WORDS FROM FILE
     * insert all 5 letter words into the trie.
     * Trie is built using repeated inserts
     */

    /**
     * Once the trie is built, the query consists of two strings
     * (1) qprefix : prefix of every word to be output
     * (2) forbidden : output words must not contain any of the characters in
     * forbidden
     * 
     * This situation is similar to wordle where we already know that some letters
     * are eliminated during a previous trial
     *
     * During query we first match the qprefix and arrive at node q.
     * then we explore all the words under node q.
     * this is done via preOrderMatch → a preOrder algorithm
     * We prune the search in the case we encounter any node whose leadChar
     * field is among the forbidden list.
     * We stop exploring anything under that node → the words will be invalid
     * This our algorithm is a pruned version of preOrder.
     *
     * the output will be a list of matching words.
     */
}