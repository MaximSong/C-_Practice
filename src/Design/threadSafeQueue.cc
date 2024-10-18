#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
template <typename T>
class LockQueue
{
public:
    void push(const T &data)
    {
        std::lock_guard<std::mutex> lock(mtx);
        que.push(data);
        cond.notify_one();
    }
    T pop()
    {
        std::unique_lock<std::mutex> lock(mtx);
        while (que.empty())
        {
            cond.wait(lock);
        }
        T data = que.front();
        que.pop();
        return data;
    }

private:
    std::mutex mtx;
    std::condition_variable cond;
    queue<T> que;
    LockQueue(const LockQueue &) = delete;
    LockQueue(LockQueue &&) = delete;
};