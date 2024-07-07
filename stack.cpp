#include <iostream>
using namespace std;

class Stack
{
public:
    Stack(int capacity) : topindex(-1), capacity(capacity)
    {
        stack = (int *)malloc(sizeof(int) * capacity);
        if (!stack)
        {
            cout << "malloc failed" << endl;
            exit(1);
        }
    }
    ~Stack()
    {
        free(stack);
    }
    void push(int data)
    {
        if (topindex == capacity - 1)
        {
            cout << "stack is full" << endl;
            return;
        }
        topindex++;
        stack[topindex] = data;
    }
    int pop()
    {
        if (topindex == -1)
        {
            cout << "stack is empty" << endl;
            return;
        }
        return stack[topindex--];
    }
    int top() const
    {
        if (topindex == -1)
        {
            cout << "stack is empty" << endl;
            return;
        }
        return stack[topindex];
    }
    bool isEmpty() const
    {
        return topindex == -1;
    }

private:
    int *stack;
    int topindex;
    int capacity;
};