# Program Assignment 1 (c++) COP4250

## Thought Process

Use multithreading to find all the primes from 1 to 10^8

I can split 10^8 into 8 chunks, each thread will find prime numbers in its own chunk each chunk will have a size of 12500000.

## UPDATE

A chunk of 12500000 is still way too big to find all the prime numbers

Each chunk of 12500000 is not garunteed to have the same distrubution of primes, so splitting the work of this will not work

breaking up the work per number is a better idea
