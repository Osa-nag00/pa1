#include <mutex>

class Counter
{
private:
    std::mutex lock;
    int counterVal;

public:
    Counter();
    Counter(int n);
    int getNextCounterVal();
};

Counter::Counter() {}

Counter::Counter(int n)
{
    this->counterVal = n;
}

int Counter::getNextCounterVal()
{
    // std::lock_guard<std::mutex> guard(lock);
    return this->counterVal++;
}
