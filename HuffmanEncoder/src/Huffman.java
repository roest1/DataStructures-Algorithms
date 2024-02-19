import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;

public class Huffman {
     private static final int ALPHABET_SIZE = 256;

     private HuffmanCode compress(final String data){
          final int [] freq = buildFrequencyTable(data);
          final Node root = buildHuffmanTree(freq);
          final Map<Character, String> lookupTable = buildLookUpTable(root);
          return new HuffmanCode(generateEncodedData(data, lookupTable), root);
     }

     private static String generateEncodedData(final String data, final Map<Character, String> table){
          final StringBuilder build = new StringBuilder();
          for(final char character : data.toCharArray()){
               build.append(table.get(character));
          }
          return build.toString();
     }

     private static Map<Character, String> buildLookUpTable(final Node root){
          final Map <Character, String> lookupTable = new HashMap<>();
          buildTable(root, "", lookupTable);
          return lookupTable;
     }

     private static void buildTable(final Node node, final String s, final Map<Character, String> lookupT){
          if(!node.isLeaf()){
               buildTable(node.left, s + '0', lookupT);
               buildTable(node.right, s + '1', lookupT);
               /**
                *  Every time we walk down the left child by convention we append an '0'
                *  (Binary Trees)
                *  Every time we walk down the right, we append a '1'
                */
          }
          else{
               lookupT.put(node.character, s);
          }
     }
     private static Node buildHuffmanTree(int [] freq){
          final PriorityQueue <Node> pq = new PriorityQueue<>(); // uses overrided compareTo
          for(char i = 0; i < ALPHABET_SIZE; i++){
               if(freq[i] > 0){
                    pq.add(new Node(i, freq[i], null, null));
               }
          }
          if(pq.size() == 1){
               pq.add(new Node('\0', 1, null, null));
          }
          while(pq.size() > 1){
               final Node left = pq.poll();
               final Node right= pq.poll();
               final Node parent = new Node('\0', left.frequency + right.frequency, left, right);
               pq.add(parent);
          }
          return pq.poll(); // parent node 

     }

     private static class Node implements Comparable<Node> {
          private final char character;
          private final int frequency;
          private final Node left, right;

          Node(final char character, final int freq, final Node left, final Node right){
               this.character = character;
               this.frequency = freq;
               this.left = left;
               this.right = right;
          }

          boolean isLeaf(){
               return this.left == null && this.right == null;
          }

          @Override
          public int compareTo(final Node that) {
               final int frequencyComparison = Integer.compare(this.frequency, that.frequency);
               if(frequencyComparison != 0 ){
                    return frequencyComparison;
               }
               return Integer.compare(this.character, that.character);
          }
          
     }

     private static int [] buildFrequencyTable(final String data){
          final int [] frequency = new int [ALPHABET_SIZE];
          for(final char character : data.toCharArray()){
               frequency[character]++; // characters can be treated like ints
          }
          return frequency;
     }


     private String decompress(final HuffmanCode result){
          final StringBuilder decompressed = new StringBuilder();
          Node current = result.getRoot();
          int i = 0;
          while(i < result.getEncodedData().length()){
               while(!current.isLeaf()){
                    char bit = result.getEncodedData().charAt(i);
                    if(bit == '1'){// chars are primitive so we can use == compared to .equals() 
                         current = current.right;
                    }else if(bit == '0'){
                         current = current.left;
                    }else{
                         throw new IllegalArgumentException("This bit doesn't work → " + bit);
                    }
                    i++;
               }
               decompressed.append(current.character);
               current = result.getRoot(); 
          }
          return decompressed.toString();
     }
     // not necessary because we don't have to decompress anything else in this class.
     // this class does NOthing.
     // just good for debugging
     private static class HuffmanCode {

          final Node root;
          final String encodedData;

          HuffmanCode(final String encodedData, final Node root){
               this.root = root;
               this.encodedData = encodedData;
          }

          public Node getRoot(){
               return this.root;
          }

          public String getEncodedData(){
               return this.encodedData;
          }
     }


     public static void main(String [] args){
          final String test = "hello world!";
          final Huffman encoder = new Huffman();
          final HuffmanCode result = encoder.compress(test);
          System.out.println("encoded message : " + result.encodedData);
          System.out.println("unencoded message = " + encoder.decompress(result));
     }

}