#include <thread>
#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

#define MAX_PRIME_VAL 100000000
#define NUM_THREADS 8
/*GLOBALS*/
std::vector<int> primes(MAX_PRIME_VAL, 1); /*If prime, index will be 1, else 0*/
double executionTimeSeconds;
int totalNumberOfPrimes;
long sumOfAllPrimes;
std::vector<int> topTenPrimes;

// function to get the runtime of function in seconds
template <typename Func>
double timeFunction(Func func)
{
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    return (duration.count() / 1000);
}

void sieveOfEratosthenes(int start, int end)
{
    for (int p = 2; p * p <= MAX_PRIME_VAL; ++p)
    {
        if (primes[p])
        {
            for (int i = std::max(p * p, (start + p - 1) / p * p); i <= end; i += p)
            {
                primes[i] = 0;
            }
        }
    }
}

void computePrimesParallel()
{
    int i, j, start, end;
    int segmentSize = MAX_PRIME_VAL / NUM_THREADS;
    std::thread threads[NUM_THREADS];

    for (i = 0; i < NUM_THREADS; i++)
    {

        // the index times the segment size is an easy
        // way to get the starting position of a chunk
        start = i * segmentSize + 1;
        end = (i + 1) * segmentSize;

        if (i == (NUM_THREADS - 1))
        {
            end = MAX_PRIME_VAL;
        }

        // creating threads
        // assign them to an index
        // send them the func and params to run
        threads[i] = std::thread(sieveOfEratosthenes, start, end);
    }

    // stop and join all the threads here before continuing
    for (j = 0; j < NUM_THREADS; j++)
    {
        threads[j].join();
    }
}

void generateTextFile(const std::string &filename, const std::string &content)
{
    std::ofstream file(filename);
    file << content;
    file.close();
}

void miscCalculations()
{
    int i, j;

    int primesSize = primes.size();

    // does not account for 1 and 0
    for (i = 2; i < primesSize; i++)
    {
        if (primes[i] == 1)
        {
            totalNumberOfPrimes++;
            sumOfAllPrimes += i;
        }
    }

    j = 0;

    while (topTenPrimes.size() < 10)
    {
        // starting from the top of the list count down
        if (primes[(primesSize - 1) - j] == 1)
        {
            topTenPrimes.push_back((primesSize - 1) - j);
        }
        j++;
    }

    // the vector is collected from greatest to least, so its reversed here
    std::reverse(topTenPrimes.begin(), topTenPrimes.end());
}

int main(int argc, char *argv[])
{

    double executionTimeSeconds = timeFunction(computePrimesParallel);
    // std::cout << "Time Seconds: " << executionTimeSeconds << std::endl;
    miscCalculations();

    std::string topTenPrimesString;
    for (int prime : topTenPrimes)
    {
        topTenPrimesString += std::to_string(prime) + " ";
    }

    std::string outputString = "Execution time: " + std::to_string(executionTimeSeconds) + " seconds" + "\n" +
                               "Total number of primes found: " + std::to_string(totalNumberOfPrimes) + "\n" +
                               "Sum of all primes found: " + std::to_string(sumOfAllPrimes) + "\n" +
                               "Top ten maximum primes: " + topTenPrimesString + "\n";

    generateTextFile("primes.txt", outputString);

    return 0;
}
