public class Trie {
    protected Node root;

    public Trie() {
        root = new Node('\0');
    }

    protected void insert(String s) {
        insertTrie(this.root, s);
    }

    /**
     * Node's children are unordered in the linked list
     * Assumes the character at p is already matched.
     * 
     * @param p
     * @param s
     */
    private void insertTrie(Node R, String s) {
        // System.out.println(s);
        if (s == null || s.isEmpty()) {
            R.isWord = true;
            return;
        }
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (R.alphabetChildren[c - 'a'] == null) {
                R.alphabetChildren[c - 'a'] = new Node(c);
                R = R.alphabetChildren[c - 'a'];
            } else {
                R = R.alphabetChildren[c - 'a'];
            }
        }
        R.isWord = true;
    }

    protected void query(Node p, String qprefix, String forbidden) {
        Node q = search(p, qprefix);
        preOrderMatch(q, qprefix, forbidden);
    }

    private Node search(Node p, String qprefix) {
        if (qprefix.length() == 0) {
            return p;
        }
        Node q = findChild(p.firstChild, qprefix.charAt(0));
        if (q == null)
            return null;
        return search(q, qprefix.substring(1, qprefix.length()));
    }

    protected static int answer;
    private static void preOrderMatch(Node p, String prefix, String forbidden) {
        if (p == null) {
            return;
        }
        if (p.isWord) {
            //System.out.println(prefix);
            answer++;
        }
        prefix = prefix + "" + p.letter;
        Node q = p.firstChild;
        while (q != null) {
            for (char n : forbidden.toCharArray()) {
                if (q.letter == n) {
                    q = q.rightSibling;
                    return;
                }
            }
            preOrderMatch(q, prefix, forbidden);
        }
    }

    /**
     * Takes Node p and char c as parameters and searches for
     * correct child node by following firstCHild and then rightSibling pointers
     * until it finds the node with c as its lead char.
     * 
     * @param p
     * @param c
     * @return
     */
    private static Node findChild(Node p, char c) {
        if (p != null) {
            Node q = p;
            if (q.letter != c) {
                findChild(q.rightSibling, c);
            }
            if (q.letter == c) {
                return q;
            }
        }
        return null;
    }

    class Node {
        char letter; // empty for root
        boolean isWord; // whether current node path represents a whole word
        // isWord is helpful when one word may be a prefix of another.
        Node[] alphabetChildren;
        Node rightSibling, firstChild;

        Node(char c) {
            alphabetChildren = new Node[26];// letters in alphabet.
            this.letter = c;
            isWord = false;
            this.rightSibling = this.firstChild = null;
        }
    }

}
