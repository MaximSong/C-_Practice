#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
using namespace std;
class ThreadPool
{
public:
    ThreadPool(size_t threadCount , size_t maxQueSize)
    :stop(false), maxQueSize_(maxQueSize)
    {
        for(int i = 0 ; i < threadCount; i ++)
        {
            workers.emplace_back([this](){
                while(true)
                {
                    function<void()>task;
                    {
                        unique_lock<mutex> lock(mtx);
                        notEmpty.wait(lock , [this](){
                            return stop || !tasks.empty();
                        });
                    
                    if(stop && tasks.empty())
                    {
                        return;
                    }
                    task = tasks.front();
                    tasks.pop();
                    notFull.notify_one();
                    }
                    task();
                }
                
            });
        }
    }
template<typename F , typename ...Args>
auto submitTask(F && func , Args&&... args) -> future<decltype(func(args...))>
{
    using returnType = decltype(func(args...));
    auto task = make_shared<packaged_task<returnType()>>(bind(forward<F>(func) , forward<Args>(args)...));
    future<returnType> future = task -> get_future();
    {
        unique_lock<mutex>lock(mtx);
        notFull.wait(lock , [this](){
            return stop || tasks.size() < maxQueSize_;
        });
        if(stop) throw runtime_error("Threadpool has stopped!");
        tasks.emplace([task](){
            (*task)();
        });
        notEmpty.notify_one();
        
    }
    return future;
}
~ThreadPool()
{
    {
        std::lock_guard<std::mutex> lock(mtx);
        stop = true;
    }
    notEmpty.notify_all();
    notFull.notify_all();

    for (std::thread &worker : workers)
    {
        if (worker.joinable())
        {
            worker.join();
        }
    }
}

private:
    vector<thread> workers;
    queue<function<void()>>tasks;
    mutex mtx;
    condition_variable notEmpty;
    condition_variable notFull;
    size_t maxQueSize_;
    bool stop;
};

int main()
{
    ThreadPool pool(4, 5);

    // 提交带参数任务
    auto future1 = pool.submitTask([](int a, int b)
                                   {
        std::cout << "Task 1: " << a + b << " (Thread " << std::this_thread::get_id() << ")" << std::endl;
        return a + b; }, 2, 3);

    auto future2 = pool.submitTask([](std::string msg)
                                   {
        std::cout << "Task 2: " << msg << " (Thread " << std::this_thread::get_id() << ")" << std::endl;
        return msg; }, "Hello, ThreadPool!");

    std::cout << "Result 1: " << future1.get() << std::endl;
    std::cout << "Result 2: " << future2.get() << std::endl;

    return 0;
}