class Node {
    protected int key, data, min_Data;
    protected Node left, right, parent;

    Node(int key, int data) {
        left = right = parent = null;
        this.key = key;
        this.data = data;
        this.min_Data = data;
    }

    protected Node() {
        left = right = parent = null;
    }

    public String toString() {
        return "(" + key + ", " + data + ")";
    }
}
