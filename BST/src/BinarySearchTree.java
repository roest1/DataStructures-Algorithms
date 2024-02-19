import java.util.Random;
import java.util.ArrayList;

class BinarySearchTree {
    private Node root;

    BinarySearchTree() {
        root = null;
    }

    private static ArrayList fillRandomList(int size) {
        Random random = new Random();
        ArrayList list = new ArrayList();
        while (size > 0) {
            list.add(random.nextInt(101) + 1);
            size--;
        }
        return list;
    }

    protected Node rootOfBST() {
        return root;
    }

    protected void insert(Node obj) {
        if (root == null) {
            root = insertNode(root, obj);
            return;
        }
        root.parent = insertNode(root, obj);
        return;
    }

    private Node insertNode(Node R, Node obj) {
        while (R != null) {
            if (R.key == obj.key) {
                if (R.data < obj.data) {
                    return R;
                }
                R.data = obj.data;
                return R;
            }
            // if the key to insert is left of roots current key
            else if (obj.key < R.key && R.left == null) {
                R.left = obj;
                R.parent = R;
                return R;
            } else if (obj.key < R.key && R.left != null) {
                R = R.left;
            }
            // if the key to insert is right of roots current key
            else if (obj.key > R.key && R.right == null) {
                R.right = obj;
                R.parent = R;
                return R;
            } else if (obj.key > R.key && R.right != null) {
                R = R.right;
            }
        }
        R = obj;
        return R;
    }

    protected void maintainMinData(Node N) {
        N.min_Data = RMQ(0, N.key, root);
    }

    protected int RMQ(int k1, int k2, Node R) {
        int min_Data = k1;
        if (R != null) {
            // need to cover inclusive indicies [k1, k2]
            // we could go in order
            // determine if the node is within bounds
            // if so add it to possible minData
            Node p = R;
            if (p.key >= k1 && p.key <= k2) {
                min_Data = findNextMin(p, k1, k2);
                int min = findNextMin(p.left, k1, k2);
                if (min < min_Data) {
                    min_Data = min;
                }
                min = findNextMin(p.right, k1, k2);
                if (min < min_Data) {
                    min_Data = min;
                }
            }
            RMQ(k1, k2, R.left);
            RMQ(k1, k2, R.right);
        }
        return min_Data;
    }

    private int findNextMin(Node N, int k1, int k2) {
        if (N == null) {
            return Integer.MAX_VALUE;
        }
        int minValue = N.data;
        while (N.left != null && k1 <= N.left.key && N.left.key <= k2) {
            minValue = N.left.data;
            N = N.left;
        }
        return minValue;
    }

    // prettyPrintTree is used from LEETCODE
    // I did not make this myself I just used it to help me debug code!
    private void prettyPrintTree(Node root, String prefix, boolean isLeft) {
        if (root == null) {
            System.out.println("Empty tree");
            return;
        }

        if (root.right != null) {
            prettyPrintTree(root.right, prefix + (isLeft ? "│   " : "    "), false);
        }

        System.out.println(prefix + (isLeft ? "└── " : "┌── ") + root);

        if (root.left != null) {
            prettyPrintTree(root.left, prefix + (isLeft ? "    " : "│   "), true);
        }
    }

    private void prettyPrintTree(Node r) {
        System.out.println("      |");
        System.out.println("      V");
        prettyPrintTree(r, "      ", true);
    }

    /////////////////////////////////////
    private void printInOrder(Node r) {
        if (r == null) {
            return;
        }
        printInOrder(r.left);
        System.out.print(r + " -> ");
        printInOrder(r.right);
    }

    protected void illustrateTree() {
        System.out.println("In Order Traversal:");
        printInOrder(root);
        System.out.println("\nTree view:\n");
        prettyPrintTree(root);
    }
}

