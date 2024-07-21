#include <iostream>
#include <vector>
using namespace std;
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