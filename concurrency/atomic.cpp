
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

std::atomic<int> shared_value = 0;

int main()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 1000; i++)
    {
        threads.push_back(std::thread(
            [](int x)
            {
                shared_value++;
            },
            i
        ));
    }

    for (int i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }

    std::cout << "Result: " << shared_value << std::endl;

    return 0;
}
