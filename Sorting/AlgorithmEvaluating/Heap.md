# Heapify in Ο(n)

Link to this answer on stack overflow:

[Build Heap in Ο(n)](https://stackoverflow.com/questions/9755721/how-can-building-a-heap-be-on-time-complexity)

---

-    There are several questions buried in this topic

1. How do you implement **Heapify** ϵ **Ο(n)**
2. How to prove **Heapify** ϵ **Ο(n)** time
3. Why doesn't **Heap Sort** correlate to the same logic

-    Heap Sort ϵ Ο(nlogn)

---

## How to implement **Heapify** ⟹ heapify() ϵ Ο(n) time

Conventionally, we might think to use **siftUp** or **siftDown**

-    To acquire Ο(n) performance, it is critical to call these methods respectively at the most reasonable times.

Proper implementations of both **buildHeap** and **heapSort** will ONLY use **siftDown**.

**siftUp** is only needed to perform inserts into an existing heap.

**$∴$** siftUp would be used to implement a priority queue using a binary heap.

> For Example

### max Heap

-    max Heap is typically used for **heap Sort** or for a priority queue where higher values indicate higher priority.

MinHeaps are also useful for when retrieving items with integer keys in ascending order or strings in alphabetical order. **The same principles apply**. Only the order needs to be switched.

-    The **heap Property** says that each node in a binary heap must be at least as large as both of its children. ⟹ The largest item in the heap is at the root. The object is to move an offending node until it satisfies the **heap Property**.

### siftDown

-    Swaps a node that is too smal with its largest child (swapping down) until it is at least as large as both of the nodes below it.

### siftUp

-    Swaps a node that is too large with its parent (swapping up) until it is no larger than the node above it.

$Sift Up & Sift Down$

The number of operations required for both siftUp and siftDown is proportional to the distance the node may have to move respective to the function.

For siftDown :

-    It is the distance to the bottom of the tree.

Making it expensive for nodes positioned in the top of the tree. (roots)

For siftUp :

-    It is the distance to the top of the tree.

Making it expensive for nodes positioned at the bottom of the tree.

Now,

Both siftUp and siftDown ϵ Ο(logn) - worst case scensario.

-    In heap only one node is at the top whereas half the nodes lie in the bottom layer.

**$∴$** We can assume **$∵$** we have to apply one of the respective functions to each inserted node, that we would prefer **siftDown** over siftUp.

The **buildHeap** function takes an array of unsorted items and moves them until they all satisfy the heap property, returning a valid heap.

-    There are 2 approaches :

1. Start at the top of the heap (A[0]) and call **siftUp** on each element. At each steap, the previously sifted elements form a subarray validating the heap property.

2. Go in opposite direction → Start at the end (A[heap_size]) and move backwards towards the front. Each iteration will sift an element down until it satisfies the heap property.

The more efficient of the two, is **siftDown**.

## Proof

Let **h = logn** represent the height of the heap. The work required for the function **siftDown** is given by :

$\sum$ (0 × $\frac{n}{2}$) + (1 × $\frac{n}{4}$) + (2 × $\frac{n}{8}$) + ... + (h × 1)

Each term in the summation hasa maximum distance a node at the respective height will have to travel. (Where 0 corresponds to the bottom layer & h corresponds to the root) This height is multiplied in each term, by the number of nodes at that respective height.

In contrast, the summation for **siftUp** looks like :

$$ ∑~~~ (h × \frac{n}{2})+((h - 1) × \frac{n}{4}) + ((h - 2) × \frac{n}{8}) + ... + (0 × 1) $$

-    It is apparent that the ladder sum is is larger. Given the first term would be :

$$ (h × \frac{n}{2}) ⟹ \frac{nlogn}{2} $$

> **$∴$** **siftUp** ϵ **Ο(nlogn)**

## Proof for siftDown ϵ Ο(n)

-    One way to prove complexity for siftDown, among many other ways, is to turn the finite sum into an infinite series and then use Taylor series. Note : we may ignore the first term **$∵$** it is always zero.

We have,

$$
(1 × \frac{n}{4}) + (2 × \frac{n}{8}) + ... + (h × 1)
⟹ \sum_{k = 1}^{h} \frac{kn}{2^{k+1}} ⟹ \frac{n}{4} ∑_{k = 1}^{{h}} \frac{k}{2^{k - 1}} < \frac{n}{4} \sum_{k = 1}^{∞} \frac{k}{2^{k - 1}}
$$

-    ∵ All the terms are positive ⟹ the finite sum is smaller than the infinite sum.
     : (x = \frac{1}{2}),
     $$ ⟹ \frac{n}{4} \sum*{k = 1}^{∞} \frac{k}{2^{k - 1}} = \frac{n}{4} ∑*{k = 1}^{{∞}} kx^{k - 1}, x = \frac{1}{2}$$

-    The power series equivalent, for the sum, parameterized at $x = \frac{1}{2}$

$$
\frac{n}{4} \sum_{k = 1}^{∞} kx^{k - 1} : (x = \frac{1}{2}), = \frac{n}{4} \frac{d}{dx}\left[\sum_{k = 0}^{∞} x^k\right] = \frac{n}{4} \frac{d}{dx}\left[\frac{1}{1 - x}\right]
$$

-    The power series has a function (at the origin) $ \rightarrow$

$$ c = 0 : ∃f^n(c) ϵ f(x) = \frac{1}{1 - x} $$
'The power series representation is equal to the function at c where the $n^{th}$ derivate of f exists at c' : $∃f^n(c)$

> Generally, when we have a power series representation of a function, the function will be represented by a Taylor Series. However, since we are using the origin as our center, we can take from the definition of a MacLaurin series.

Recall the definition for Taylor Series of a function f(x) $→$

$$f(x) = f(c) + \frac{f'(c)}{1!}(x - c) + \frac{f''(c)}{2!}(x - c)^2 + \frac{f'''(c)}{3!}(x - c)^3 + ... + \frac{f^n(c)}{n!}(x - c)^n $$
..for the $n^{th}$ degree Taylor polynomial

Since the taylor series uses the center for the terms of the series, we can throw the operations using the center, away. By doing this, we arrive to the definition of a MacLaurin series.

Recall the definition for MacLaurin Series of a function f(x) $\rightarrow$

$$f(x) = \sum_{n = 0}^{∞} \frac{f^n(0)}{n!}x^n ⟹ f(0) + \frac{f'(0)}{1!}x + \frac{f''(0)}{2!}x^2 + \frac{f'''(0)}{3!}x^3  + ... + \frac{f^n(0)}{n!}x^n  $$

Substituting our function for $x → f(x) = \frac{1}{1-x}$
We get :
$$ 1 + x + x^2 + x^3 + x^4 + ... + x^n = \sum\_{n = 0}^{∞} x^n $$

Before we go any further, note the following properties of the space in math which I am using:

-    For any function
     $f(x) : x $ ϵ $ ℝ → $ its derivative is unique.

-    If a function converges respective to the ladder property, it has exactly one polynomial series.

> With this knowledge, we can use implicit differentiation to formalise type derivatives as isomorphism classes. And since implicit differentiation doesn't require any subtraction or division, we can also use it to analyse recursive type definitions.

See : [Calculus & Computer Science](https://stackoverflow.com/questions/9190352/abusing-the-algebra-of-algebraic-data-types-why-does-this-work)

However, since we are sure the terms of a series are strictly 'differentiable' if only implicitly, and the correspondence of functions with respect to their derivatives is certainly unique, we can assume that we will determine valid results even if we use such 'illegal' operations of division and subtraction.

Provided, we have that if a function has a macLaurin series, we can essentially find any series.

Essentially, with MacLaurin series, we can enumerate the number of members of a function with a certain number of elements.

-    The series is monotonic, since it is always increasing. We can use the following test for convergence :

For the sequence
$$ \{x^n\}\ |\_{0}^{∞} $$

Immediately we see
$$\lim_{n\rightarrow∞} x^n = ∞ ⟹ Inconclusive$$
Applying the Root Test :

> From definition : **Ratio Test** → $\lim_{n→∞} |({a_n})^{1/n}| = L$
>
> **If** $(L < 1) ⟹ Absolutely convergent$
>
> **If** $(L > 1)$ $|$ $(L = ∞) ⟹ Divergent$
>
> **If** $(L = 1) ⟹ Inconclusive$

We get :
$$ L = \lim*{n→∞}(|(x^n)^{1/n}|) ⟹ \lim*{n→∞}|x| ⟹ |x|×\lim\_{n→∞}(1) = 1 × |x| = |x| = L$$
Using the definition for the Root test the power series converges for :
$$ |x| < 1 ⟹ -1 < x < 1$$
Keep in mind our bounds are exclusive $(-1, 1)$ given
$1^n$ & $(-1)^n$
both diverge for n→∞

And ultimately, therefore, we can confirm $ x = \frac{1}{2}$ _ϵ_ $(-1, 1)$

To continue our proof of time complexity we can now replace the function of the power series representation with its derivative, and find the value of the infinite series.

$$\frac{d}{dx}\frac{1}{1 - x} = \frac{d}{dx}(1 - x)^{-1}$$
Applying chain rule :
$$\frac{d}{du}(u)^{-1}× \frac{d}{dx}(1 - x) ⟹ \frac{-1}{u^2}\times(-1)$$
$$ ⟹ \frac{-1}{(1 - x)^2} × (-1) = \frac{1}{(1 - x)^2}dx $$

Substituting into the sum :

$$ x = \frac{1}{2} ⟹ \frac{n}{4} \frac{1}{(1 - x)^2} = \frac{n}{4} \frac{1}{(1 - 1/2)^2} = \frac{n}{16}$$

For big-Ο complexity, we can ignore constants →
Giving us: ⟹ n
$∴$
SiftDown _ϵ_
$Ο(n)$

---

### Why does heapSort require Ο(nlogn) time?

Since we can buildHeap in linear time (Ο(n)), why does heap sort still require Ο(nlogn)?

-    Heap Sort consists of 2 stages.

1. First we call buildHeap on the array
     - This requires Ο(n) time when implemented optimally
2. Next is to repeatedly delete the largest item in the heap and put it at the end of the array.
     - When we delete an element from the heap, there is always an open spot just after the last element in the heap. This is where the largest element goes.

So heapSort achieves a sorted order by successively removing the next largest item and putting it into the array, starting its partition at the end of the array and moving towards the front.
This last part is what ultimates heap Sort.
The loop looks like this :

```
for(int i = n - 1; i > 0; i--){
     A[i] = deleteMax();
}
```

This loop runs Ο(n - 1) times. (Subtracting one because the last element is already in place)

The complexity for deleteMax() _ϵ_ Ο(logn)

-    It is typically implemented by removing the root (largest element) and replacing it with the last item in the heap, a leaf, and therefore one of the smallest items.
     -    The probability of this new root being out of place is almost certain, therefore we can assume we will need to call **siftDown** until we move it back into a position that satifsfies the heap property.
          By consequence of this we end up moving the next largest item up to the root.

Now, in contrast to buildHeap where most of the nodes inserted will use the siftDown function (starts from the bottom of the tree)

heapSort uses the siftDown function, but begins at the root every iteration.

-    The height of the tree stays constant until we have removed the first half of the nodes. This is when the bottom layer has been completely deleted. Then for the next row of deletion, the height will be h -= 1

The time function with respect to calling the heap function _ϵ_ Ο(logn) :
$$ (h × \frac{n}{2}) + ((h - 1) × \frac{n}{4}) + ((h - 2) × \frac{n}{8}) + ... + (0 × 1)$$

$∴$ heapSort _ϵ_ Ο(nlogn) just like buildHeap when siftUp is used instead of siftDown.
In the case when we want to heapSort, we have no choice but to siftUp, since we require the next largest item to be removed next.

> In short, heapSort is the summation of two stages :
>
> Ο(n) to buildHeap
>
> Ο(nlogn) to remove each node in order

> > $∴$ heapSort _ϵ_ Ο(nlogn) **best case scenario**
