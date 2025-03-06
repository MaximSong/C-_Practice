#include <iostream>
#include <vector>
#include <queue>
using namespace std;
vector<int> topKLargest(vector<int> &nums, int K)
{
    priority_queue<int, vector<int>, greater<int>> minHeap; // 小根堆

    for (int num : nums)
    {
        if (minHeap.size() < K)
        {
            minHeap.push(num);
        }
        else if (num > minHeap.top())
        {
            minHeap.pop();
            minHeap.push(num);
        }
    }

    vector<int> result;
    while (!minHeap.empty())
    {
        result.push_back(minHeap.top());
        minHeap.pop();
    }
    return result;
}
void heapify(vector<int>&vec , int n , int i)
{
    int largestIndex = i;
    int left = 2*i;
    int right = 2* i + 1;
    if(left <= right && vec[left] > vec[largestIndex])
    {
        largestIndex = left;
    }
    if(right >= left && vec[largestIndex])
    {
        largestIndex = right;
    }
    if(i != largestIndex)
    {
        swap(vec[i] , vec[largestIndex]);
        heapify(vec , n ,largestIndex);
    }

}
void buildHeap(vector<int>& vec)
{
    int n = vec.size() - 1;
    for(int i = n/2 ; i >=1 ; i --)
    {
        heapify(vec , n ,i);
    }
}

void HeapSort(vector<int>& vec)
{
    buildHeap(vec);
    for(int i = vec.size() - 1; i >=1 ;i --)
    {
        swap(vec[1] , vec[i]);
        heapify(vec, i - 1, 1);
    }
}