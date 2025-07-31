// project_4_2.cpp
// реализация Deque

#include <iostream>
using namespace std;

class Deque {
    private:
        int maxSize;
        long* queArray;
        int front;
        int rear;
        int nItems;
    public:
        Deque(int s) {
            maxSize = s;
            queArray = new long[maxSize];
            front = 0;
            rear = -1;
            nItems = 0;
        }
        void insertRight(long j) {
            if (rear == maxSize - 1)
                rear = -1;
            queArray[++rear] = j;
            nItems++;
        }
        void insertLeft(long j) {
            if (rear == maxSize - 1)
                rear = -1;
            rear++;
            for (int i = rear; i > 0; i--)
                queArray[i] = queArray[i - 1];
            queArray[0] = j;
            nItems++;
        }
        long removeLeft() {
            long temp = queArray[front++];
            if (front == maxSize)
                front = 0;
            nItems--;
            return temp;
        }
        long removeRight() {
            long temp = queArray[rear--];
            if (rear == 0)
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

class DequeApp {
    public:
        static void main() {
            Deque* deque = new Deque(5);

            cout << "Insertion: " << endl;
            deque->insertRight(44);
            deque->insertRight(77);
            deque->insertLeft(66);
            deque->insertRight(55);
            deque->insertLeft(99);
            deque->display();

            cout << "Removing: " << endl;
            deque->removeLeft();
            deque->removeRight();
            deque->display();
        }
};

int main() {
    DequeApp::main();
    return 0;
}