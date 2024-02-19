
How to do so? (**Solution:**)

Given a set of n elements, define

$$\text{Rank}(x) := (\text{number of elements} ∈ A[1...n]) ≤ x$$

Find element(s) of Rank = 

$$⌊ \frac{n + 1}{2} ⌋ \text{ and } ⌈ \frac{n + 1}{2} ⌉$$

> Note if n is odd, then these two ranks will yeild the same element.

1. Arrange n elements into $⌈ \frac{n}{5} ⌉$ columns of size 5


We can garuantee $\frac{1}{2}$ of the $⌈ \frac{n}{5} \rceil$ columns will have at least 3 elements > x

That is, except for the column that contains x and the one column with less than 5 elements. ( 2 columns )

$$∴ \text{ At least } 3(⌈ \frac{n}{10}⌉ - 2) \text{ elements} > x$$

Which we discard. 

$$⟹ n - 3(⌈ \frac{n}{10}⌉ - 2) = 7⌈\frac{n}{10} ⌉ + 6 \text{ maximal number of elements to partition}$$


**Reccurrence :**

$$f\left(x\right) = \left\{
     \begin{array}{lr}
       T(n) = 1 ∈ O(1) \text{ for } n ≤ 140 \le 1\\
       T(n) = T(⌈ \frac{n}{5} ⌉) + T(7⌈\frac{n}{10} ⌉ + 6) + \theta(n) \text{ for } n > 140
     \end{array}
   \right.\\
   $$

   > 140 is sort of an arbitrary constant (10 - 3) * 20

   (time to find median of medians) + (Max size partition) + (Sorting of all columsn)

* This doesn't work very well in practice since at every level of recursion we're calling another recursive algorithm to find the median ( A good example of asymptotic complexity vs performance)

**Why 5?**

(Fact) any reccurrence o f the form 

$$T(n) ≤ T(an) + T(bn) + cn$$

$$a + b < 1 ⟹  ∈ O(n)$$

Note : we could use sublists of size greater than 5 and still maintain linear run time. However, to keep the ocnstaant time bound as efficient as possible, we keep sublists size as small as possible.






