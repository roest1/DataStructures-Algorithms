# Eratosthenes_Prime_Sieve

Prime generator from data structures &amp; algorithms class @ LSU


### Lemmas to sieve:

* The square of the smallest prime factor of a composite number c 
is less than or equal to c

* Any composite number less than p² is sifted (crossed out) a prime < p

* When sifting by p, start marking at p² 

* If we sift numbers up to m, stop sifting when p² ≥ m

**`Formulas to sieve:`**

* Value(index i) = 2i + 3

* Index(value v) = (v - 3) / 2

* Index(value(i)²) = 2i² + 6i + 3

