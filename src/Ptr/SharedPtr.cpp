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

    // 拷贝构造函数
    SharedPtr(const SharedPtr<T> &other) : resource(other.resource),
                                           refCount(other.refCount)
    {
        AddRef();
    }

    // 赋值运算符重载
    SharedPtr<T> &operator=(const SharedPtr<T> &other)
    {
        if (this != &other) // 防止自我赋值
        {
            releasePtr(); // 释放当前资源

            resource = other.resource;
            refCount = other.refCount;

            AddRef();
        }
        return *this;
    }

    // 访问资源
    T *operator->()
    {
        return resource;
    }

    // 解引用资源
    T &operator*()
    {
        return *resource;
    }

    // 获取引用计数
    int GetCount()
    {
        unique_lock<mutex> lck(refMutex);
        return *refCount;
    }

    // 布尔转换运算符，判断 SharedPtr 是否为空
    operator bool() const
    {
        return resource != nullptr;
    }

    // 比较两个 SharedPtr 是否指向相同的资源
    bool operator==(const SharedPtr<T> &other) const
    {
        return resource == other.resource;
    }

    bool operator!=(const SharedPtr<T> &other) const
    {
        return !(*this == other);
    }

private:
    // 释放资源
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

    // 增加引用计数
    void AddRef()
    {
        unique_lock<mutex> lck(refMutex);
        (*refCount)++;
    }

    T *resource;    // 资源指针
    int *refCount;  // 引用计数
    mutex refMutex; // 用于同步对引用计数的操作
};

// 测试代码
int main()
{
    SharedPtr<int> ptr1(new int(10));
    SharedPtr<int> ptr2 = ptr1; // 拷贝构造

    cout << "ptr1 count: " << ptr1.GetCount() << endl; // 输出 2
    cout << "ptr2 count: " << ptr2.GetCount() << endl; // 输出 2

    SharedPtr<int> ptr3(new int(20));
    ptr3 = ptr1; // 赋值运算符

    cout << "ptr1 count after assignment: " << ptr1.GetCount() << endl; // 输出 3
    cout << "ptr3 count after assignment: " << ptr3.GetCount() << endl; // 输出 3

    cout << "ptr1 == ptr2: " << (ptr1 == ptr2) << endl; // 输出 1 (true)
    cout << "ptr1 != ptr3: " << (ptr1 != ptr3) << endl; // 输出 0 (false)

    if (ptr1)
    {
        cout << "*ptr1: " << *ptr1 << endl; // 输出 10
    }

    return 0;
}
