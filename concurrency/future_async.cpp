
#include <iostream>
#include <future>
#include <chrono>

#define DELAY_s     (5)

int square(int x)
{
    std::this_thread::sleep_for(std::chrono::seconds(DELAY_s));
    return x*x;
}

int main()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::future<int> asyncFunction = std::async(&square, 12);
    std::this_thread::sleep_for(std::chrono::seconds(DELAY_s));
    
    int result = asyncFunction.get();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Result is: " << result << std::endl;
    std::cout << "Calculation took: " << std::chrono::duration_cast<std::chrono::milliseconds>((end - begin)).count() << " ms ..." << std::endl;

    return 0;
}