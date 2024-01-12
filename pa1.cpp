#include <stdio.h>
#include <thread>
#include <bits/stdc++.h>
#include <vector>
#include <chrono>
#include "Counter.hpp"

#define MAX_PRIME_VAL 100000000
#define CHUNK_SIZE 12500000
#define TEST_MAX_PRIME_VAL 10000
#define TEST_CHUNK_SIZE 2500

Counter globalCounter(1);
int myCount = 1;

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

std::vector<int> listOfPrimesNoMultithreading(std::vector<int> retval)
{
    int i;

    // TODO: change the range to the actual value
    for (i = TEST_MAX_PRIME_VAL; i > 1; i--)
    {
        // saves making the function call if even
        if (i % 2 != 0 && isPrime(i))
        {
            // adds prime number to vector
            retval.push_back(i);
        }

        // corner case
        // 2 is prime, even though it is even
        if (i == 2)
        {
            retval.push_back(i);
        }
    }

    return retval;
}

void printPrimes()
{

    while (myCount < MAX_PRIME_VAL)
    {

        myCount = globalCounter.getNextCounterVal();
        if (isPrime(myCount))
        {
            printf("Prime: %d\n", myCount);
        }
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
    int j;
    int numThreads = 16;
    std::vector<std::thread> threads;

    for (j = 0; j < numThreads; j++)
    {
        // create threads
        threads.push_back(std::thread(printPrimes));
    }

    // sort(Multi.begin(), Multi.end());

    // bool retval = checkEqual(Multi, nonMulti);

    // printf("Non Multi: %f milliseconds \n", msNonMulti);
    // printf(" Multi: %f milliseconds \n", msMulti);
    printf("%s", "Hello World!");

    for (int x = 0; x < numThreads; x++)
    {
        threads.at(x).join();
    }

    return 0;
}
