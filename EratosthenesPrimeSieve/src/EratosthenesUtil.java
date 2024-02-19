import java.util.ArrayList;
public class EratosthenesUtil {
     /**
      * Provides an implementation for the Eratosthene's sieve generator.
      *
      * CSC 3102 Programming Project # 0
      *
      * @author Riley Oest
      * @see EratosthenesProfiler.java
      *
      * <pre>
      * Data : 8/28/2022
      * Course : CSC 3102 Section 1
      * Instructor : Dr. Duncan
      * Project : 0
      * </pre>
      *
      */
       /**
        * Generates as sequence of all primes less than the specified parameter
        *
        * @param n the upperbound on the prime sequence
        * @return an ArrayList of allp rimes in [2, n] or an empty ArrayList if n < 2.
        *
        */
       public static ArrayList<Long> sieve(long n) {
          if(n < 2) return new ArrayList<Long>(0);
          boolean [] isPrime = new boolean[(int) n + 1];
          for(int i = 2; i <= n; i++) isPrime[i] = true;
          for(int i = 2; i * i <= n; i++){
               if(isPrime[i]){
                    for(int j = i; j * i <= n; j++) isPrime[i * j] = false;
               }
          }
          ArrayList<Long> primes = new ArrayList<Long>();
          for(int i = 2; i <= n; i++){
               if(isPrime[i]) primes.add((long) i);
          }
          return primes;
       }
       /**
        * Gives a string representation of the specified ArrayList in the form : 
        * {1, 2, 3, 4}.
        *
        * @param V an ArrayList of Long type
        * @return A string representation of the ArrayList in the form {1, 2, 3, 4}.
        *
        */
       public static String toString(ArrayList<Long> V){
          StringBuilder sb = new StringBuilder();
          for(int i = 0; i < V.size(); i++){
               if(i == V.size() - 1){ sb.append(", " + V.get(i) + "}"); break; }
               sb.append(i == 0 ? " {" + V.get(i) : ", " + V.get(i));
          }
          return sb.toString();
       }
       /**
        * 
        *  Draws table with time (μ) in microseconds, the exact and approximate values of π(n) and the percent error of the two.
        * 
        */
       public static void drawTable(){
          System.out.println("===============================================================");
          System.out.printf("n\tTime(μ)\t\tπ(n)\tn / ln(n)\t%%Error(π(n))\n");
          System.out.println("===============================================================");
          for(int n = 10000; n < 160000; n += 10000){
               long start = System.nanoTime();
               ArrayList<Long> primes = EratosthenesUtil.sieve(n);
               int count = 0;
               for(long l : primes){ count++; }
               System.out.printf("%d\t:%s\t\t:%d\t:%f\t    :%f\n", n, (long) ((System.nanoTime() - start) / 1000), count, (n / Math.log(n)), (((n / Math.log(n)) - count) / count) * 100);
          }
          System.out.println("===============================================================");
       }
}
