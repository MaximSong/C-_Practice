#include <iostream>
using namespace std;
class Stack {
public:
    Stack(int capacity):capacity(capacity), topIndex(-1){
        stack = new int[capacity];
        if(!stack) {
            cout << "allocate memory failed!" << endl;
            exit(1);
        }
    }
    ~Stack() {
        delete []stack;
    }
    void push(int data) {
        if(topIndex == capacity - 1) {
            cout << "stack is full!" << endl;
        }
        topIndex++;
        stack[topIndex] = data;
    }
    int pop() {
        if(topIndex == -1) {
            cout<<"stack is empty!"<<endl;
            return -1;
        }
        return stack[topIndex--];
    }
    const int top() {
        if(topIndex == -1) {
            cout << "stack is empty!" << endl;
            return -1;
        }
        return stack[topIndex];
    }
    bool isEmpty() {
        return topIndex == -1;
    }
private:
    int* stack;
    int capacity;
    int topIndex;
};

int main() {
    Stack stk(10);
    stk.pop();
    stk.push(1);
    stk.isEmpty();
    stk.top();
}