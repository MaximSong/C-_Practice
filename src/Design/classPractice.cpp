#include <iostream>
using namespace std;
class Base
{
public:
    Base(int _size) : data(new int[_size]), size(_size) {}
    ~Base() { delete[] data; }
    Base(const Base &other)
    {
        size = other.size;
        data = new int[other.size];
        // data = new char[other.size + 1]
        copy(other.data, other.data + other.size, data);
        // strcopy(data , other.data);
    }
    Base(Base &&other) : data(other.data), size(other.size)
    {
        other.data = nullptr;
        other.size = 0;
    }

private:
    int *data;
    int size;
};
