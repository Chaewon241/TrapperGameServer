#include <iostream>
#include <chrono>
#include <functional>
#include "ThreadManager.h"
#include "ThreadPoolManager.h"

// 성능 측정용 함수
void work(int t, int id) 
{
    std::this_thread::sleep_for(std::chrono::seconds(t));
}

int main()
{
    // 테스트할 작업 수
    const int taskCount = 1000;
    const int poolSize = 3; // ThreadPool의 스레드 수


    auto start1 = std::chrono::high_resolution_clock::now();
    
    // ThreadManager 성능 측정
    ThreadManager threadManager;
    for (int i = 0; i < 10; i++)
    {
        threadManager.Launch([i]() { work(i % 3 + 1, i); });
    }

    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed1 = end1 - start1;

    std::cout << "No ThreadPool Elapsed time: " << elapsed1.count() << " seconds" << std::endl;
    
    auto start2 = std::chrono::high_resolution_clock::now();
    // ThreadPoolManager 성능 측정
    ThreadPoolManager threadPoolManager(poolSize);
    for (int i = 0; i < 10; i++) 
    {
        threadPoolManager.EnqueueJob([i]() { work(i % 3 + 1, i); });
    }

    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = end2 - start2;

    std::cout << "ThreadPool Elapsed time: " << elapsed2.count() << " seconds" << std::endl;

    return 0;
}