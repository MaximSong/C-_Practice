#include <iostream>
#include <memory>

class UniquePtrPractice
{
public:
    // 构造函数
    UniquePtrPractice();
    // 析构函数
    ~UniquePtrPractice();
    static void basicUsage();
    static void moveUsage();
    static void arrayUsage();
};
void UniquePtrPractice::basicUsage()
{
    std::unique_ptr<int> ptr(new int(10));
    std::cout << *ptr << std::endl;
}
void UniquePtrPractice::moveUsage()
{
    std::unique_ptr<int> k(new int(10));
    std::unique_ptr<int> l = std::move(k);
}
