# Program Assignment 1 (c++) COP4250 (Ubuntu 22.04)

## HOW TO RUN

Since I am using jthreads and the vector reverse function, the code need to be compiled with c++20

1. Firstly compile the program with this command.

   ```bash
   g++ pa1.cpp -o pa1 -std=cpp+20
   ```

2. You can then run the program with this command.

   ```bash
   ./pa1
   ```

## My Approach / Experimental Evaluation

Initially I was not really sure how to start this assigment, since this was my first time using multiple threads in prgramming.

My first instict was to give each thread its own chunk of the 10^8. So If computing with 8 threads, each thread woud have 12500000 Number to check if their prime.

This initially failed becuase I was using an inefficient way to calculate primes.

I then switch to the shared counter method and still ran into the same problem of really slow runtimes for the same reason mentioned above.

I switched back to giving the threads each their own chunk of numbers to check, and swithc my finding primes algorithm to use the Sieve Of Eratosthenes which was far faster than what I was using and helped with dropping my runtime down to something resonable.

## Correctness and Efficency

### TODO write proof later
