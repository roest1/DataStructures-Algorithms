import java.util.ArrayList;
import java.util.Scanner;
public class EratosthenesProfiler {
     /**
      * 
      * A program to profile the Eratosthene's Sieve prime number generator
      * and compares the exact value of the prime-counting function and n / ln(n) 
      *
      * CSC 3102 Programming Project # 0
      *
      * @author Riley Oest
      * @see EratosthenesUtil.java
      *
      * <pre>
      * Date : 8/28/2022
      * Course : CSC 3102 Section 1
      * Instructor : Dr. Duncan
      * Project : 0
      * </pre>
      *
      */
public static void main(String [] args) throws Exception {
      double percent = 10000 / Math.log(10000);
      System.out.printf("%f", percent);
          System.out.printf("Enter an integer n to generate primes in [2, n] ⟹ ");
          Scanner scan = new Scanner(System.in);
          int n = scan.nextInt();
          
          /////////Time Trial//////////////
          long start = System.nanoTime();
          ArrayList<Long> primes = EratosthenesUtil.sieve(n);
          int count = 0;
          for(long l : primes){ count++; }
          long  microseconds = (System.nanoTime() - start) / 1000;
          ////////////Time Trial///////////////

          System.out.printf("\nP(%d) = %s\n\n", n, EratosthenesUtil.toString(primes)); 
          System.out.printf("Time to Generate the Primes : %s microseconds\n", microseconds);
          System.out.printf("π(%d) = %d\n", n, count);
          System.out.printf("The approximation of π(n) ≈ n / ln(n) = %f\n\n", (n / (Math.log(n))));
          EratosthenesUtil.drawTable();
          System.out.printf("\n");
      }     


}
