#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;  // 创建互斥锁

std::mutex mtx1, mtx2;

void incrementCounter(int& counter) {
    std::lock_guard<std::mutex> lock(mtx);  // 在临界区加锁
    counter++;  // 对共享资源进行操作
}  // 在离开作用域时自动解锁

void threadFunction(int n)
{
    // 使用 std::scoped_lock 锁定多个互斥锁
    std::scoped_lock lock(mtx1, mtx2);
    // 互斥锁被锁定，可以执行线程安全的操作
    std::cout << "Thread "<< n << " is running..." << std::endl;

    // 互斥锁在作用域结束时自动释放
}

int main() {
    // int counter = 0;
    // const int numThreads = 10;
    // std::thread threads[numThreads];

    // for (int i = 0; i < numThreads; ++i) {
    //     threads[i] = std::thread(incrementCounter, std::ref(counter));
    // }

    // for (int i = 0; i < numThreads; ++i) {
    //     threads[i].join(); // 当前线程阻塞，会等待 threads[i] 线程执行完毕，然后再继续执行后续的代码
    // }

    // std::cout << "Final Counter Value: " << counter << std::endl;

    const int numThreads = 10;
    std::thread t[numThreads];
    for (int i = 0; i < numThreads; i++)
    {
        t[i] = std::thread(threadFunction, i);
    }

    // {
    //     std::lock_guard<std::mutex> lock(mtx1);

    //     // 互斥锁被锁定，可以执行线程安全的操作
    //     std::cout << "Main thread is running..." << std::endl;

    //     // 互斥锁在作用域结束时自动释放
    // }

    for (int i = 0; i < numThreads; ++i) 
    {
        t[i].join(); // 当前线程阻塞，会等待 threads[i] 线程执行完毕，然后再继续执行后续的代码
    }

    return 0;
}

// std::ref(counter) 是用于将变量counter包装成一个引用。
// 在C++中，线程函数默认是按值传递参数的，因此如果直接将counter作为参数传递给线程函数，会创建一个副本，而不是直接对原始的counter进行操作。