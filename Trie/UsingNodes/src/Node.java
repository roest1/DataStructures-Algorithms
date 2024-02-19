public class Node {

    protected Node root;
    Node() { root = new Node('\0'); }
    private char letter;
    private Node firstChild, rightSibling;
    private boolean isWord;
    public Node(char c) {
        letter = c;
        firstChild = rightSibling = null;
        isWord = false;
    }

    protected void insert(Node root, String word) {
        if (word.length() == 0) {
            root.isWord = true;
            return;
        }
        char c = word.charAt(0);
        String restOfword = word.substring(1, word.length());
        Node child = findChild(root, c);
        if (child == null) {
            Node in = new Node(c);
            in.rightSibling = root.firstChild;
            root.firstChild = in;
            insert(in, restOfword);
        } else {
            insert(child, restOfword);
        }
    }
    private Node findChild(Node root, char c) {
        if(root.firstChild == null) { return null; }
        Node child = root.firstChild;
        while(child != null && c != child.letter) { child = child.rightSibling; }
        return child;
    }
    protected int answer;
    private void findMatches(Node q, String prefix, String forbidden) {
        if(q == null) { return; }
        if(q.isWord) { answer ++; }
        Node cloud = q.firstChild;
        while(cloud != null) {
            if(forbidden.indexOf(cloud.letter) == -1) { findMatches(cloud, prefix + cloud.letter, forbidden); }
            cloud = cloud.rightSibling;
        }
    }
    protected void query(Node p, String prefix, String forbidden) {
        Node q = prefixTree(p, prefix);
        findMatches(q, prefix, forbidden);
    }
    private Node prefixTree(Node root, String prefix) {
        if(prefix.length() == 0) { return root; }
        Node sT = findChild(root, prefix.charAt(0));
        if(sT == null){ return null; }
        return prefixTree(sT, prefix.substring(1, prefix.length()));
    }
}