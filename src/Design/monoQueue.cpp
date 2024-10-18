#include <iostream>
#include <deque>
using namespace std;
template <typename T>
class monoQue
{
public:
    void push(T data)
    {
        while (!que.empty() && que.back() < data)
        {
            que.pop_back();
        }
        que.push_back(data);
    }
    bool isEmpty() const
    {
        return que.empty();
    }
    T maxVal() const
    {
        return que.front();
    }
    // 当且仅当最左端值和要pop的值一样的时候才pop（降序排列）
    void pop(T val)
    {
        if (val == que.front())
        {
            que.pop_front();
        }
    }

private:
    deque<T> que;
};
int main()
{
    monoQue<int> mq;
    vector<int> arr = {1, 3, 2, 5, 4, 6};
    int WindowSize = 3;
    for (int i = 0; i <= 5; i++)
    {
        mq.push(arr[i]);
        if (i >= WindowSize)
        {
            mq.pop(arr[i - WindowSize]);
        }
        if (i >= WindowSize - 1)
        {
            cout << "最大值: " << mq.maxVal() << endl;
        }
    }
}