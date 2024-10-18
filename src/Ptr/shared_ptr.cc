#include <iostream>
#include <memory>
class SharedPtrPractice
{
public:
    SharedPtrPractice(std::string name, int age) : name(name), age(age) {}
    ~SharedPtrPractice() {}
    void print();

private:
    std::string name;
    int age;
};
void SharedPtrPractice::print()
{
    std::cout << "name: " << name << ", age: " << age << std::endl;
}
int main()
{
    auto ptr = std::make_shared<SharedPtrPractice>("zhangsan", 20);
    std::shared_ptr<SharedPtrPractice> ptr2 = ptr;
    std::cout << "ptr.use_count() = " << ptr.use_count() << std::endl;
    ptr->print();
}