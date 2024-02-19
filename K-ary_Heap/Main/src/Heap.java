public class Heap {
    private int [] H;
    protected int H_size;
    private int next;
    private int k;

    Heap(int max_size, int numChildren)
    {
        H_size = max_size;
        H = new int[H_size - 1];
        next = 0;
        k = numChildren;
    }

    public void swap(int i, int j) {
        int temp = H[i];
        H[i] = H[j];
        H[j] = temp;
    }

    public void floatUp(int parent_index) {
        int child_index = (parent_index - 1) / k;
        while (child_index >= 0) {
            if (H[parent_index] < H[child_index]) {
                swap(parent_index, child_index);
                parent_index = child_index;
                child_index = (parent_index - 1) / k;
            } else {
                break;
            }
        }
        return;
    }

    public int minIndex(int... indices) {
        int minIndex = indices[0];
        int minValue = H[minIndex];

        for (int i : indices) {
            if (H[i] < minValue) {
                minIndex = i;
                minValue = H[i];
            }
        }
        return minIndex;
    }

    public void sinkDown(int start, int end) {
        int min = start * k + 1;
        int [] p = new int[k];
        for (int i = 0; i < k; i++) {
            p[i] = min + i;
        }
        if (p[k - 1] > end) {
            return;
        }
        
        int[] q = new int[k];
        for (int i = 0; i < k; i++) {
            if (H[p[i]] != 0) {
                q[i] = p[i];
            }
        }

        min = minIndex(q);

        if (H[0] <= H[min]) {
            return;
        }

        swap(0, min);
        sinkDown(0, end);
    }

    public int rootIndex(int[] A, int first, int last) {
        int min = first;
        for (int i = first; i < last; i++) {
            if (A[min] > A[i]) {
                min = i;
            }
        }
        return min;
    }

    public void insert(int data) {
        H[next] = data;
        floatUp(next);
        next++;
        return;
    }

    public void decreaseKey(int index, int newElement) {
        H[index] = newElement;
        floatUp(index);
        return;
    }

    public int extractMin() {
        int temp = H[H_size - 1];
        int[] newH = new int[H_size - 1];
        for (int i = 1; i < newH.length; i++) {
            newH[i] = H[((i < H_size - 1) ? i : i + 1)];
        }
        H = newH;
        H[0] = temp;
        sinkDown(0, H.length);
        return H[0];
    }
}
