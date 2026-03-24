
#include <iostream>
#include <thread>
#include <vector>

void test(int x)
{
    std::cout << "Hey from thread - func." << std::endl;
    std::cout << "Argument: " << x << std::endl;
}

int main()
{
    std::thread t1(&test, 1);
    std::thread t2([](int x) {
        std::cout << "Hey from thread - lambda." << std::endl;
        std::cout << "Argument: " << x << std::endl;
    }, 2); 

    std::cout << "test" << std::endl;
    t1.join();
    t2.join();

    std::vector<std::jthread> threads_pool;
    for (int i = 0; i < 10; i++)
    {
        threads_pool.push_back(std::jthread([](int x){
            std::cout << "Hey from threads pool: " << std::this_thread::get_id() << std::endl;
            std::cout << "Argument: " << x << std::endl;
        }, i));
    }
    return 0;
}
