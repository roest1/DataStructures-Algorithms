import java.util.LinkedList;
import java.util.Queue;

/**
 *
 * @author rileyoest
 */
// class for Node objects used in Tree //
class Node {

    int data, height;
    Node left, right;

    // value parameterized constructor //
    public Node(int data) {
        this.data = data;
        left = right = null;
        height = 1;
    }
}

// class for Tree object to manipulate Node objects //
public class Tree {

    private Node rootNode; // declaration of a node that represents the root node

    // method to insert element in O(logn) where n = number of inputs //
    public void insertElement(int input) {
        rootNode = insertElement(rootNode, input);
    }

    private Node insertElement(Node node, int input) {
        if (node == null) {
            return (new Node(input)); // if current node is empty insert a new Node(int data)
        }
        if (input < node.data) { // if element to be inserted is less than the current node
            node.left = insertElement(node.left, input); // insert the element into the left child of the current Node()
        } else if (input > node.data) { // else if the element to be inserted is greater than the current node
            node.right = insertElement(node.right, input); // insert the element into the right child of the current
                                                           // Node()
        } else {
            if (input == node.data) {// and if the element to be inserted is the same value as the current Node()
                node.height += 1; // increment the current node's height
                node = insertElement(node, input); // insert the element into the current Node()
                return node;
            }
            return node;// otherwise, we've exhausted all necessary queries to insert the element
            // so return the current node.
        }
        // input to be inserted into the AVL tree has been successfully inserted

        node.height = 1 + getMaxHeight(height(node.left), height(node.right)); // update height of current node to its
                                                                               // ancestor

        // get balance factor (Tree_leftHeight - Tree_rightHeight) =
        // node.balanceFactor();
        int balance = getBalance(node);

        // If unbalanced, 4 cases
        int cases = 4;
        switch (cases) {
            case 1: // zigZig case

                if (balance > 1 && input < node.left.data) {
                    return rightRotate(node);
                }
                break;
            case 2: // zagZag case
                if (balance < -1 && input > node.right.data) {
                    return leftRotate(node);
                }
                break;
            case 3: // zigZag case
                if (balance > 1 && input > node.left.data) {
                    node.left = leftRotate(node.left);
                    return rightRotate(node);
                }
                break;
            case 4: // zagZig case
                if (balance < -1 && input < node.right.data) {
                    node.right = rightRotate(node.right);
                    return leftRotate(node);
                }
        }

        return node; // AVL is balanced return unchanged current node
    }

    // HELPER METHODS FOR insertElement() //

    // height(node) function returns height of current node and returns 0 if the
    // node is null//
    private int height(Node node) {
        if (node == null) {
            return 0;
        }
        return node.height;
    }

    // getMaxHeight(leftHeight, rightHeight) returns the greater of the 2
    // parameters//
    private int getMaxHeight(int leftNodeHeight, int rightNodeHeight) {
        if (leftNodeHeight > rightNodeHeight) {
            return leftNodeHeight;
        } else {
            return rightNodeHeight;
        }
    }
    // HELPER METHODS FOR insertElement() //

    // rightRotate(node) returns a node that has been rotated clockWise //
    private Node rightRotate(Node root) {
        Node zig = root.left;
        Node zigZag = zig.right;
        zig.right = root;
        root.left = zigZag;
        root.height = getMaxHeight(height(root.left), height(root.right) + 1);
        zig.height = getMaxHeight(height(zig.left), height(zig.right) + 1);
        return zig;
    }

    // leftRotate(node) returns a node that has been rotated counterClockWise //
    private Node leftRotate(Node root) {
        Node zag = root.right;
        Node zagZig = zag.left;
        zag.left = root;
        root.right = zagZig;
        root.height = getMaxHeight(height(root.left), height(root.right) + 1);
        zag.height = getMaxHeight(height(zag.left), height(zag.right) + 1);
        return zag;
    }

    // helper final array representing valid balanceFactor values //
    private static final int[] BALANCED = { -1, 0, 1 };

    // isBalanced(p) returns true if the proposition is a valid balanceFactor and
    // false otherwise//
    private boolean isBalanced(int proposition) {
        int i = 0;
        while (i < 3) {
            if (BALANCED[i] == proposition) {
                return true;
            }
            i++;
        }
        return false;
    }

    // getBalance(node) returns 0 if the node is null and returns the balance factor
    // of the current AVL tree
    private int getBalance(Node node) {
        if (node == null) {
            return 0;
        }
        return height(node.left) - height(node.right);// get balance factor (Tree_leftHeight - Tree_rightHeight) =
                                                      // node.balanceFactor();
    }

    // find range between element k1 and element k2//
    public void rangeReport(int k1, int k2) {
        System.out.print("[");
        rangeReport(rootNode, k1, k2);
        System.out.println("]");
    }

    // recursively find valid elements within range [k1, k2] (inclusive)
    // First, find elements from start node to k1 recursively printing valid nodes
    // Once, k1 is found, recursively search right, printing valid nodes, until
    // there is no further right child node that is within -> k2] (inclusive)
    private void rangeReport(Node node, int k1, int k2) {
        boolean k1notFound = true;
        if (node == null) {
            return; // if the current node is null, no further indexing for range necessary
        }
        if (k1notFound && k1 < node.data) { // if current node is within k1 and k1 hasnt been found yet
            rangeReport(node.left, k1, k2); // traverse down the tree left
        }
        if (k1 <= node.data && node.data <= k2) { // if the current node is within (inclusive) the range
            if (node.data == k1) {
                k1notFound = false; // find k1
            }
            System.out.print(node.data + " ");// list the node
        }
        rangeReport(node.right, k1, k2);// otherwise traverse down the tree right
    }

    public void printInOrder() {
        System.out.print("In-order traversal: ");
        inOrderTraversal(rootNode);
        System.out.println();
    }

    public void printPreOrder() {
        System.out.print("Pre-order traversal: ");
        preOrderTraversal(rootNode);
        System.out.println();
    }

    public void printPostOrder() {
        System.out.print("Post-order traversal: ");
        postOrderTraversal(rootNode);
        System.out.println();
    }

    public void printLevelOrder() {
        System.out.print("Level-order traversal: ");
        levelOrderTraversal(rootNode);
        System.out.println();
    }

    private static void inOrderTraversal(Node node) {
        if (node != null) {
            inOrderTraversal(node.left);
            System.out.print(node.data + " ");
            inOrderTraversal(node.right);
        }
    }

    private static void preOrderTraversal(Node node) {
        if (node != null) {
            System.out.print(node.data + " ");
            preOrderTraversal(node.left);
            preOrderTraversal(node.right);
        }
    }

    private static void postOrderTraversal(Node node) {
        if (node != null) {
            postOrderTraversal(node.left);
            postOrderTraversal(node.right);
            System.out.print(node.data + " ");
        }
    }

    private static void levelOrderTraversal(Node node) {
        if (node == null)
            return;

        Queue<Node> queue = new LinkedList<>();
        queue.add(node);

        while (!queue.isEmpty()) {
            Node currNode = queue.poll();
            System.out.print(currNode.data + " ");

            if (currNode.left != null)
                queue.add(currNode.left);

            if (currNode.right != null)
                queue.add(currNode.right);
        }
    }


}
