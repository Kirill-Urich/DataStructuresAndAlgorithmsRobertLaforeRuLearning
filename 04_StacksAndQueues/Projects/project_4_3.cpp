// project_4_3.cpp
// Stack на основе Deque

#include <iostream>
using namespace std;

class Deque {
    protected:
        int maxSize;
        long* queArray;
        int front;
        int rear;
        int nItems;
    protected:
        Deque(int s) {
            maxSize = s;
            queArray = new long[maxSize];
            front = 0;
            rear = -1;
            nItems = 0;
        }
        void insertRight(long j) {
            if (isFull()) return;
            if (rear == maxSize - 1)
                rear = -1;
            queArray[++rear] = j;
            nItems++;
        }
        void insertLeft(long j) {
            if (isFull()) return;
            if (front == 0)
                front = maxSize;
            queArray[--front] = j;
            nItems++;
        }
        long removeLeft() {
            if (isEmpty()) throw "Deque is empty";
            long temp = queArray[front++];
            if (front == maxSize)
                front = 0;
            nItems--;
            return temp;
        }
        long removeRight() {
            if (isEmpty()) throw "Deque is empty";
            long temp = queArray[rear--];
            if (rear < 0)
                rear = maxSize - 1;
            nItems--;
            return temp;
        }
        bool isEmpty() {
            return nItems == 0;
        }
        bool isFull() {
            return nItems == maxSize;
        }
        int size() {
            return nItems;
        }
        void display() {
            if (rear > front) {
                for (int i = front; i <= rear; i++)
                    cout << queArray[i] << " ";
                cout << endl;
            }
            else {
                for (int i = front; i < nItems; i++)
                    cout << queArray[i] << " ";
                for (int i = 0; i <= rear; i++)
                    cout << queArray[i] << " ";
                cout << endl;
            }
        }
};

class StackX : private Deque {
    public:
        StackX(int s) : Deque(s) { }
        void push(long j) {
            Deque::insertRight(j);
        }
        long pop() {
            return Deque::removeRight();
        }
        long peek() {
            return queArray[rear];
        }
        bool isEmpty() {
            return Deque::isEmpty();
        }
        bool isFull() {
            return Deque::isFull();
        }
        void display() {
            Deque::display();
        }
};

class StackApp {
    public:
        static void main() {
            StackX theStack(10);
            theStack.push(20);
            theStack.push(40);
            theStack.push(60);
            theStack.push(80);

            theStack.display();

            theStack.pop();
            theStack.display();
        }
};

int main() {
    StackApp::main();
    return 0;
}