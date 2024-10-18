#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <queue>

std::mutex mutxIdle;

template <typename T>
class TaskQueue
{
public:
    void submitTask(T task)
    {
        std::unique_lock<std::mutex> lock(mtx);
        while (taskQue.size() >= maxSize)
        {
            notFull.wait(lock);
        }
        std::cout << "Produced Task: " << task << " | Queue size: " << taskQue.size() << "\n";
        taskQue.push(task);
        notEmpty.notify_all();
    }

    void consumeTask()
    {
        std::unique_lock<std::mutex> lock(mtx);
        while (taskQue.size() == 0)
        {
            notEmpty.wait(lock);
        }
        T tsk = taskQue.front();
        std::cout << "Consumed Task: " << tsk << " | Queue size: " << taskQue.size() << "\n";
        taskQue.pop();
        notFull.notify_all();
    }

    int queueSize()
    {
        std::unique_lock<std::mutex> lock(mtx);
        return taskQue.size();
    }

private:
    const int maxSize = 100;
    std::queue<T> taskQue;
    std::mutex mtx;
    std::condition_variable notEmpty;
    std::condition_variable notFull;
};

void consumerThread(TaskQueue<int> &queue, bool &done, int &idleThread)
{
    while (!done)
    {
        {
            std::unique_lock<std::mutex> lock(mutxIdle);
            idleThread--;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        queue.consumeTask();
        {
            std::unique_lock<std::mutex> lock(mutxIdle);
            idleThread++;
        }
    }
}

void producerThread(TaskQueue<int> &queue, bool &done, int &taskCounter)
{
    while (!done)
    {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        queue.submitTask(taskCounter);
        taskCounter++;
    }
}

void managerThread(std::vector<std::thread> &consumerThreads, TaskQueue<int> &task, bool &done, int &idleThread)
{
    while (!done)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        int taskSize = task.queueSize();
        if (taskSize > idleThread)
        {
            std::cout << "Adding more threads" << std::endl;
            consumerThreads.push_back(std::thread(consumerThread, std::ref(task), std::ref(done), std::ref(idleThread)));
        }
        else if (taskSize < idleThread && idleThread > 1)
        {
            std::cout << "Removing idle thread" << std::endl;
            idleThread--;
            consumerThreads.back().join();
            consumerThreads.pop_back();
        }
    }
}

int main()
{
    TaskQueue<int> queue;
    int taskCounter = 0;
    bool done = false;     // 结束标志
    int idleConsumers = 0; // 空闲消费者计数

    // 初始化生产者和消费者线程
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    // 创建初始的1个生产者和1个消费者
    producers.push_back(std::thread(producerThread, std::ref(queue), std::ref(done), std::ref(taskCounter)));
    consumers.push_back(std::thread(consumerThread, std::ref(queue), std::ref(done), std::ref(idleConsumers)));
    idleConsumers = 1; // 初始时有1个空闲消费者

    // 管理线程的动态平衡
    std::thread manager(managerThread, std::ref(consumers), std::ref(queue), std::ref(done), std::ref(idleConsumers));

    // 模拟运行一段时间（例如 60 秒），然后结束程序
    std::this_thread::sleep_for(std::chrono::seconds(60));
    done = true; // 结束标志，通知所有线程退出

    // 等待所有生产者和消费者线程完成
    for (auto &p : producers)
    {
        if (p.joinable())
        {
            p.join();
        }
    }

    for (auto &c : consumers)
    {
        if (c.joinable())
        {
            c.join();
        }
    }

    if (manager.joinable())
    {
        manager.join();
    }

    std::cout << "All threads finished.\n";
    return 0;
}
