#include <iostream>
#include <vector>

#include <chrono>
#include <functional>

#include <atomic>
#include <future>
#include <mutex>
#include <thread>

using namespace std;

void taskNoArgs()
{
    /* Simulating an activity */
    volatile int sum = 0;
    for (int i = 0; i < 1000000; i++)
    {
        sum += i;
    }
}

static double average = 0.0;
void taskWithArgs(int limit)
{
    /* Simulating an activity */
    volatile int sum = 0;
    for (int i = 0; i < limit; i++)
    {
        sum += i;
    }

    average = sum / limit;
}

static mutex mtx;
static int mutexCounter(0);
void incrementWithMutex(int limit)
{
    for (int i = 0; i < limit; i++)
    {
        /* Lock the mutex */
        mtx.lock();

        /* Update shared memory */
        ++mutexCounter;

        /* Unlock the mutex */
        mtx.unlock();
    }
}

static atomic<int> atomicCounter(0);
void incrementWithAtomic(int limit)
{
    for (int i = 0; i < limit; i++)
    {
        ++atomicCounter;
    }
}

template <typename Func, typename... Args>
long long benchmarkIt(Func &&func, Args &&...args)
{
    auto start = chrono::high_resolution_clock::now();
    invoke(forward<Func>(func), forward<Args>(args)...);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

int main()
{
    /* Non-joinable thread */
    thread nonJoinalbeThread(taskNoArgs);
    nonJoinalbeThread.detach();
    cout << "After detach, the thread is non-joinable: " << !nonJoinalbeThread.joinable() << endl;

    /* Joinable thread */
    thread joinalbeThread(taskNoArgs);
    joinalbeThread.join();

    /* Benchmarking thread vs async */
    constexpr int tasksLimit = 4;
    constexpr int countLimit = 10000000;

    auto threadDuration = benchmarkIt([&](int countLimit)
                                      {
                                          vector<thread> threads;
                                          for (int i = 0; i < tasksLimit; ++i)
                                              threads.emplace_back(taskWithArgs, countLimit);
                                          for (auto &t : threads)
                                              t.join(); },
                                      countLimit);
    cout << "[std::thread] " << threadDuration << " ms" << endl;

    auto asyncDuration = benchmarkIt([&](int countLimit)
                                     {
                                          vector<future<void>> futures;
                                          for (int i = 0; i < tasksLimit; ++i)
                                              futures.emplace_back(async(launch::async, taskWithArgs, countLimit));
                                          for (auto &f : futures)
                                              f.get(); },
                                     countLimit);
    cout << "[std::async] " << asyncDuration << " ms" << endl;

    /* Benchmarking mutex vs atomic */
    auto mutexDuration = benchmarkIt([&](int countLimit)
                                     {
                                         vector<thread> threads;
                                         for (int i = 0; i < tasksLimit; ++i)
                                             threads.emplace_back(incrementWithMutex, countLimit);
                                         for (auto &t : threads)
                                             t.join(); },
                                     countLimit);
    std::cout << "[std::mutex ] " << mutexDuration << " ms" << endl;

    auto atomicDuration = benchmarkIt([&](int countLimit)
                                      {
                                          std::vector<std::thread> threads;
                                          for (int i = 0; i < tasksLimit; ++i)
                                              threads.emplace_back(incrementWithAtomic, countLimit);
                                          for (auto& t : threads) t.join(); },
                                      countLimit);
    std::cout << "[std::atomic] " << atomicDuration << " ms" << endl;
}
