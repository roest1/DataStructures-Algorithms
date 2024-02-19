import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;

class Trie {
    static class Node {
        private char letter;
        private Map<Character, Node> children = new HashMap<>();

        private boolean isEmpty() {
            return letter == '\0';
        }

        private boolean isRoot() {
            return isEmpty() && (children.size() > 0);
        }

        private boolean isLeaf() {
            return isEmpty() && !isRoot();
        }

        Node(char c) {
            this.letter = c;
        }

        protected void insert(Queue<Character> chars) {
            if (chars.isEmpty()) {
                this.children.put('\0', new Node('\0'));
                return;
            }
            char nextLetter = chars.remove();
            if (!this.children.containsKey(nextLetter)) {
                this.children.put(nextLetter, new Node(nextLetter));
            }
            Node n = this.children.get(nextLetter);
            n.insert(chars);
        }

        protected List<String> getWords() {
            List<String> words = new ArrayList<>();
            if (isLeaf()) {
                words.add("");
                return words;
            }
            for (Node c : children.values()) {
                List<String> suffixes = c.getWords();
                for (String word : suffixes) {
                    words.add(letter + word);
                }
            }
            return words;
        }

        protected Node getSubtree(Queue<Character> chars) {
            if (chars.isEmpty()) {
                return this;
            }
            char nextLetter = chars.remove();
            if (!this.children.containsKey(nextLetter))
                return null;
            Node n = this.children.get(nextLetter);
            return n.getSubtree(chars);
        }
    }

    private Node root = new Node('\0');

    protected void add(String word) {
        word = word.toLowerCase();
        Queue<Character> chars = toCharQueue(word);
        this.root.insert(chars);
    }

    protected Queue<Character> toCharQueue(String s) {
        Queue<Character> q = new LinkedList<>();
        for (char c : s.toCharArray()) {
            q.add(c);
        }
        return q;
    }
}