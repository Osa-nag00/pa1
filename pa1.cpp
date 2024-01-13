#include <stdio.h>
#include <thread>
#include <bits/stdc++.h>
#include <vector>
#include <chrono>
#include <iostream>
#include <functional>
#include <iomanip>
#include "Counter.hpp"

#define MAX_PRIME_VAL 100000000
#define TEST_MAX_PRIME_VAL 100000

template <typename Func>
double timeFunction(Func func, int numThreads)
{
    auto start = std::chrono::high_resolution_clock::now();
    func(numThreads);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

bool isPrime(int n)
{
    // Corner case
    if (n <= 1)
        return false;

    // Check from 2 to n-1
    for (int i = 2; i <= n / 2; i++)
        if (n % i == 0)
            return false;

    return true;
}

void printPrimes(Counter &counter, int i)
{

    while (i < MAX_PRIME_VAL)
    {

        i = counter.getNextCounterVal();
        if (isPrime(i))
        {
            printf("Prime: %d\n", i);
        }
    }
}

void printPrimesWrapper(int numThreads)
{
    int j;
    Counter counter(1); /* custom increment counter that is multithreading safe, this is also shared between all the threads*/
    std::vector<std::jthread> jthreads;

    for (j = 0; j < numThreads; j++)
    {
        jthreads.push_back(std::jthread(printPrimes, std::ref(counter), 0));
    }
}

bool checkEqual(std::vector<int> a, std::vector<int> b)
{

    for (int i = 0; i < a.size() && i < b.size(); i++)
    {
        if (a.at(i) != b.at(i))
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char *argv[])
{

    double timeTaken = timeFunction(printPrimesWrapper, 8);

    std::cout << "Time Taken: " << std::setprecision(2) << timeTaken / 1000 << " seconds" << std::endl;
    return 0;
}
