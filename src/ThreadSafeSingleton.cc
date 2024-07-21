#include <iostream>
#include <thread>
#include <mutex>
class Singleton
{
private:
    static Singleton *instance;
    static std::mutex mtx;
    Singleton() {}

public:
    static Singleton *GetInstance()
    {
        if (instance == nullptr)
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (instance == nullptr)
            {
                instance = new Singleton();
            }
        }
        return instance;
    }
    Singleton(const Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(const Singleton &) = delete;
    Singleton &operator=(Singleton &&) = delete;
};