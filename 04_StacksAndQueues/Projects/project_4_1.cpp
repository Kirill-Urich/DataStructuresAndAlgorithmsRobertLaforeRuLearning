// project_4_1.cpp

// queue.cpp
// Работа с очередью

#include <iostream>
using namespace std;

class Queue {
    private:
        int maxSize;
        long* queArray;
        int front;
        int rear;
        int nItems;
    public:
        Queue(int s) {
            maxSize = s;
            queArray = new long[maxSize];
            front = 0;
            rear = -1;
            nItems = 0;
        }
        void insert(long j) {
            if (rear == maxSize - 1)
                rear = -1;
            queArray[++rear] = j;
            nItems++;
        }
        long remove() {
            long temp = queArray[front++];
            if (front == maxSize)
                front = 0;
            nItems--;
            return temp;
        }
        long peekFront() {
            return queArray[front];
        }
        bool isEmpty() {
            return (nItems == 0);
        }
        bool isFull() {
            return (nItems == maxSize);
        }
        int size() {
            return nItems;
        }
        void display() {
            if (front < rear) {
                for (int i = front; i <= rear; i++)
                    cout << queArray[i] << " ";
                cout << endl;
            }
            else if (front >= rear) {
                for (int i = front; i < nItems; i++)
                    cout << queArray[i] << " ";
                for (int i = 0; i <= rear; i++)
                    cout << queArray[i] << " ";
                cout << endl;
            }
        }
};

class QueueApp {
    public:
        static void main() {
            Queue* theQueue = new Queue(5);

            theQueue->insert(10);
            theQueue->insert(20);
            theQueue->insert(30);
            theQueue->insert(40);
            theQueue->insert(50);
            
            theQueue->remove();
            theQueue->remove();

            theQueue->insert(60);
            theQueue->insert(70);
            theQueue->remove();

            theQueue->display();
        }
};

int main() {
    QueueApp::main();
    return 0;
}