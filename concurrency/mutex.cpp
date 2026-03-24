
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

static int shared_value = 0;
static std::mutex glock;

static void shared_value_increment(int x)
{
    std::lock_guard<std::mutex> lock(glock);
    shared_value = shared_value + 1;
}

int main()
{
    std::vector<std::thread> threads;

    for (int i = 0; i < 100; i++)
    {
        threads.push_back(std::thread(shared_value_increment, i));
    }

    for (int i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }

    std::cout << "Shared value: " << shared_value << std::endl;


    return 0;
}
