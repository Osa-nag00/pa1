#include <stdio.h>
#include <thread>
#include <bits/stdc++.h>
#include <vector>
#include <chrono>
#include <iostream>
#include <functional>
#include "Counter.hpp"

#define MAX_PRIME_VAL 100000000
#define CHUNK_SIZE 12500000
#define TEST_MAX_PRIME_VAL 10000
#define TEST_CHUNK_SIZE 2500

template <typename Func>
double timeFunction(Func func, std::vector<int> vec)
{
    auto start = std::chrono::high_resolution_clock::now();
    func(vec);
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
    Counter counter(1); /* custom increment counter that is multithreading safe*/
    std::vector<std::thread> threads;

    for (j = 0; j < numThreads; j++)
    {
        threads.push_back(std::thread(printPrimes, std::ref(counter), 0));
    }

    for (int x = 0; x < numThreads; x++)
    {
        threads.at(x).join();
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
    printPrimesWrapper(2);
    return 0;
}
