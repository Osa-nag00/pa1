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

To test for correctness, I can change the program to use a single thread something like changing

```c++
#define NUM_THREADS 1
```

To

```c++
#define NUM_THREADS 8
```

Running the program with either 1 or 8 threads results in the same out put, with an exception for the excecution time of course. Running a single thread, the computation takes about 4.5 seconds. However running with 8 threads takes this down to about 3.7 seconds.
