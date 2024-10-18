/*
设计的主要关键点：
引用计数：每个 shared_ptr 共享一个引用计数（refCount），记录当前有多少个 shared_ptr 实例管理同一个对象。当引用计数减少到 0 时，释放对象。

线程安全：使用 std::mutex 来保证在多线程环境下，引用计数的增减是安全的。所有修改 refCount 的操作都会通过互斥锁来保护。

资源管理：

当拷贝一个 shared_ptr 时，引用计数增加。
当析构 shared_ptr 时，引用计数减少。如果引用计数为 0，则释放资源。
注意mutex不能赋值可以变成指针
*/
#include <iostream>
#include <mutex>
using namespace std;
template <typename T>
class SharedPtr
{
public:
    SharedPtr(T *ptr) : resource(ptr), refCount(new int(1)) {}
    ~SharedPtr()
    {
        releasePtr();
    }
    SharedPtr(const SharedPtr<T> &other) : resourse(other.resource),
                                           refCount(other.refCount)
    {
        AddRef();
    }
    T *operator->()
    {
        return resource;
    }
    T &operator*()
    {
        return *resource;
    }
    int GetCount()
    {
        unique_lock<mutex> lck(refMutex);
        return *refCount;
    }

private:
    void releasePtr()
    {
        unique_lock<mutex> lck(refMutex);
        (*refCount)--;
        if (*refCount == 0)
        {
            delete resource;
            delete refCount;
        }
    }
    void AddRef()
    {
        unique_lock<mutex> lck(refMutex);
        (*refCount)++;
    }

    T *resource;
    int *refCount;
    mutex refMutex;
};