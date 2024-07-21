#include <vector>
#include <iostream>
#include <mutex>

class Sort
{
private:
    Sort() {}
    ~Sort() {}

    static Sort *instance;
    static std::mutex mtx;

    Sort(const Sort &) = delete;
    Sort(Sort &&) = delete;

    static int partition(int left, int right, std::vector<int> &vec);

public:
    static Sort *GetInstance()
    {
        if (instance == nullptr)
        {
            std::unique_lock<std::mutex> lock(mtx);
            if (instance == nullptr)
            {
                instance = new Sort();
            }
        }
        return instance;
    }

    void QuickSort(std::vector<int> &test, int left, int right);
    void insertSort(std::vector<int> &test);
};

// 快速排序: 平均时间复杂度为 O(n log n)，
// 因为 partition 是 O(n)，而递归调用平均需要 log n 层。
// 但是如果每次都选择最大或最小作为 pivot，这样就会退化为 O(n^2)。
int Sort::partition(int left, int right, std::vector<int> &vec)
{
    int pivot = vec[left];
    int originalIndex = left;
    while (left < right)
    {
        while (left < right && vec[right] >= pivot)
            right--;
        while (left < right && vec[left] <= pivot)
            left++;
        if (left < right)
        {
            std::swap(vec[left], vec[right]);
        }
    }
    std::swap(vec[originalIndex], vec[left]); // 将 pivot 放置在正确的位置
    return left;                              // 返回 pivot 的最终位置
}

void Sort::QuickSort(std::vector<int> &test, int left, int right)
{
    if (left >= right)
        return;
    int pivot = Sort::partition(left, right, test);
    QuickSort(test, left, pivot - 1);
    QuickSort(test, pivot + 1, right);
}
// 插入排序，时间复杂度最差为On2（当数组为逆序时），最好的时间复杂度是O（n）（当数组有序时）
void Sort::insertSort(std::vector<int> &test)
{
    for (int i = 1; i < test.size(); i++)
    {
        int key = test[i];
        int j = i - 1;
        while (j >= 0 && test[j] > key)
        {
            test[j + 1] = test[j];
            j--;
        }
        test[j + 1] = key;
    }
}

Sort *Sort::instance = nullptr;
std::mutex Sort::mtx;

int main()
{
    std::vector<int> test = {12, 11, 13, 5, 6};
    std::vector<int> test2 = {5, 6, 3, 2, 4, 9, 1};
    std::vector<int> test3 = {10, 9, 8, 7, 6, 5, 4};
    Sort *res = Sort::GetInstance();
    res->QuickSort(test3, 0, test3.size() - 1);
    res->insertSort(test);
    for (auto num : test3)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    for (auto num : test)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    return 0;
}
