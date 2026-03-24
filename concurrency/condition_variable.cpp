
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

std::mutex glock;
std::condition_variable gConditionVariable;

int main()
{
    int result = 0;
    bool notified = false;

    // Reporting thread
    std::thread reporter([&](){
        std::cout << "Reporter started..." << std::endl;
        std::unique_lock<std::mutex> lock_guard(glock);
        std::cout << "Reporter acquired lock..." << std::endl;
        if (!notified) 
        {
            std::cout << "Reporter wait for lock..." << std::endl;
            gConditionVariable.wait(lock_guard);
        }

        std::cout << "Reporter, result is " << result << std::endl;
    });


    // Working thread
    std::thread worker([&](){
        std::cout << "Worker started..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::unique_lock<std::mutex> lock_guard(glock);
        std::cout << "Worker acquired lock..." << std::endl;

        result = 42;

        notified = true;

        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Work complete..." << std::endl;

        // wake up reporter threa
        gConditionVariable.notify_one();
    });

    reporter.join();
    worker.join();

    return 0;
}