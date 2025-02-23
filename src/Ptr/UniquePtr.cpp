#include <iostream>

template <typename T>
class UniquePtr
{
public:
    // 构造函数
    explicit UniquePtr(T *ptr = nullptr) : ptr_(ptr) {}

    // 析构函数，负责释放资源
    ~UniquePtr()
    {
        delete ptr_;
    }

    // 禁止拷贝构造和拷贝赋值
    UniquePtr(const UniquePtr &other) = delete;
    UniquePtr &operator=(const UniquePtr &other) = delete;

    // 移动构造函数
    UniquePtr(UniquePtr &&other) noexcept : ptr_(other.ptr_)
    {
        other.ptr_ = nullptr; // 使原对象指针为空，避免析构时释放资源
    }

    // 移动赋值运算符
    UniquePtr &operator=(UniquePtr &&other) noexcept
    {
        if (this != &other)
        {                         // 防止自我赋值
            delete ptr_;          // 先释放当前对象拥有的资源
            ptr_ = other.ptr_;    // 将资源的所有权转移给当前对象
            other.ptr_ = nullptr; // 使原对象指针为空，避免析构时释放资源
        }
        return *this;
    }

    // 获取底层指针
    T *get() const
    {
        return ptr_;
    }

    // 解引用操作符
    T &operator*() const
    {
        return *ptr_;
    }

    // 箭头操作符
    T *operator->() const
    {
        return ptr_;
    }

private:
    T *ptr_; // 原始指针
};

int main()
{
    // 创建一个 UniquePtr 指向一个 int
    UniquePtr<int> ptr1(new int(10));
    std::cout << "ptr1 points to: " << *ptr1 << std::endl;

    // 移动构造一个新的 UniquePtr
    UniquePtr<int> ptr2 = std::move(ptr1);
    std::cout << "ptr2 points to: " << *ptr2 << std::endl;

    // 现在 ptr1 不再拥有资源
    if (ptr1.get() == nullptr)
    {
        std::cout << "ptr1 is now null." << std::endl;
    }

    // 使用移动赋值运算符
    UniquePtr<int> ptr3(new int(20));
    ptr3 = std::move(ptr2); // 通过移动赋值转移资源
    std::cout << "ptr3 points to: " << *ptr3 << std::endl;

    return 0;
}
