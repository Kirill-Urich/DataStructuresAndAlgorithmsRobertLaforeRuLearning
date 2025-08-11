// stackTriangle2.cpp
// Вычисление треугольных чисел (стек вместо рекурсии)

#include <iostream>
using namespace std;

class StackX {
    private:
        int maxSize;
        int* stackArray;
        int top;
    public:
        StackX(int s) {
            maxSize = s;
            stackArray = new int[maxSize];
            top = -1;
        }
        void push(int p) {
            stackArray[++top] = p;
        }
        int pop() {
            return stackArray[top--];   
        }
        int peek() {
            return stackArray[top];
        }
        bool isEmpty() {
            return top == -1;
        }
};

class StackTriangle2App {
    private:
        int theNumber;
        int theAnswer;
        StackX* theStack;
    public:
        void main() {
            cout << "Enter a number: ";
            cin >> theNumber;
            stackTriangle();
            cout << "Triangle = " << theAnswer << endl;
        }
        void stackTriangle() {
            theStack = new StackX(10'000);
            theAnswer = 0;
            while (theNumber > 0) {
                theStack->push(theNumber);
                --theNumber;
            }
            while (!theStack->isEmpty()) {
                int newN = theStack->pop();
                theAnswer += newN;
            }
        }
};

int main() {
    StackTriangle2App st2a;
    st2a.main();
    return 0;
}