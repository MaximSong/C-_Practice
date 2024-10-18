#include <condition_variable>
#include <mutex>
#include <queue>
#include <iostream>
#define MaxSize 100
template <typename T>
class TaskQueue
{
public:
    TaskQueue() {}
    ~TaskQueue() {}
    void submitTask(T tsk)
    {
        std::unique_lock<std::mutex> lock(mtx);
        while (task.size() >= MaxSize)
        {
            notFull.wait(lock);
        }
        task.push(tsk);
        notEmpty.notify_one();
    }
    void consumeTask()
    {
        std::unique_lock<std::mutex> lock(mtx);
        while (task.empty())
        {
            notEmpty.wait(lock);
        }
        task.pop();
        notFull.notify_one();
    }

private:
    std::mutex mtx;
    std::queue<T> task;
    std::condition_variable notEmpty;
    std::condition_variable notFull;
    TaskQueue(const TaskQueue &) = delete;
    TaskQueue(TaskQueue &&) = delete;
};
