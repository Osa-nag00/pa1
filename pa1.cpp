#include <stdio.h>
#include <thread>
#include <bits/stdc++.h>
#include <vector>
#include <chrono>

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

std::vector<int> listOfPrimesNoMultithreading(std::vector<int> retval)
{
    int i;

    // TODO: change the range to the actual value
    for (i = 0; i <= TEST_MAX_PRIME_VAL; i++)
    {
        if (isPrime(i))
        {
            // adds prime number to vector
            retval.push_back(i);
        }
    }

    return retval;
}

std::vector<int> listOfPrimesMultithreadingHelper(std::vector<int> retval, int startOfChunk, int endOfChunk)
{

    int i = startOfChunk;

    for (; i <= endOfChunk; i++)
    {
        if (isPrime(i))
        {
            // adds prime number to vector
            retval.push_back(i);
        }
    }

    return retval;
}

std::vector<int> listOfPrimesMultithreading(std::vector<int> retval)
{

    // int i;

    // // each of the 8 threads will fine all primes within a chunk of 10^8
    // // 10^8 % 8 == 0, and 10^8 / 8 == 12500000
    // // so each thread will work on a chunk of size 12500000
    // std::vector<int> retval1;
    // std::vector<int> retval2;
    // std::vector<int> retval3;
    // std::vector<int> retval4;

    // // starts all the threads
    // std::thread t1(listOfPrimesMultithreadingHelper, retval1, 0, (TEST_MAX_PRIME_VAL - TEST_CHUNK_SIZE * 7));
    // std::thread t2(listOfPrimesMultithreadingHelper, retval2, TEST_CHUNK_SIZE * 1, (TEST_MAX_PRIME_VAL - TEST_CHUNK_SIZE * 6));
    // std::thread t3(listOfPrimesMultithreadingHelper, retval3, TEST_CHUNK_SIZE * 2, (TEST_MAX_PRIME_VAL - TEST_CHUNK_SIZE * 5));
    // std::thread t4(listOfPrimesMultithreadingHelper, retval4, TEST_CHUNK_SIZE * 3, (TEST_MAX_PRIME_VAL - TEST_CHUNK_SIZE * 4));

    // // stops all the threads here and joins them back to the main thread
    // t1.join();
    // t2.join();
    // t3.join();
    // t4.join();

    int numOfThreads = 8;
    std::vector<std::thread> threads;
    std::vector<std::vector<int>> retvals;
    int i;
    int start;
    int end;
    int chunkSize = TEST_MAX_PRIME_VAL / numOfThreads;

    // create all threads and calc chunks
    for (i = 0; i < numOfThreads; i++)
    {
        start = chunkSize * i;
        end = TEST_MAX_PRIME_VAL - chunkSize * (numOfThreads - (i + 1));
        threads.at(i) = std::thread(listOfPrimesMultithreadingHelper, retvals.at(i), start, end);
    }

    // insert resulting arrays to one single array
    for (i = 0; i < numOfThreads; i++)
    {
        retval.insert(retval.end(), retvals.at(i).begin(), retvals.at(i).end());
    }

    return retval;
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

    std::vector<int> nonMulti;
    std::vector<int> Multi;

    double msNonMulti = timeFunction(listOfPrimesNoMultithreading, nonMulti);
    double msMulti = timeFunction(listOfPrimesMultithreading, Multi);
    // std::vector<int> Multi = listOfPrimesMultithreading();

    sort(Multi.begin(), Multi.end());

    bool retval = checkEqual(Multi, nonMulti);

    printf("Non Multi: %f milliseconds \n", msNonMulti);
    printf(" Multi: %f milliseconds \n", msMulti);
    printf("%s", "Hello World!");
    return 0;
}
