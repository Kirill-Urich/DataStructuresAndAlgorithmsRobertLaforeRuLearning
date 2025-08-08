// project_4_5.cpp

#include <iostream>
#include <limits>
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
            int count = 0;
            int index = front;
            while (count < nItems) {
                cout << queArray[index] << " ";
                index = (index + 1) % maxSize;
                count++;
            }
            cout << endl;
        }
};

class Shop {
    private:
        Deque** queues;
        int maxSize;
        const int queSize = 10;
        const int weight_per_minutes = 10;
    public:
        Shop(int s) {
            maxSize = s + 1;
            queues = new Deque*[maxSize];
            for (int i = 0; i < maxSize; i++)
                queues[i] = new Deque(queSize);
        }
        void add(int order, int weight) {
            queues[order]->insertRight(weight);
        }
        void display() {
            int count = 0;
            while (count != maxSize) {
                if (queues[count]->size() != 0) {
                    cout << "Queue " << count << ": ";
                    queues[count]->display();
                }
                ++count;
            }
        }
        void movement() {
            cout << "Press Enter to show queues (any other key to exit): ";
            while (true) {
                if (isEmpty())
                    break;
                
                cout << "Press Enter to continue: ";

                if (cin.get() != '\n') {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                this->display();
                for (int count = 0; count < maxSize; count++) {
                    if (queues[count] != nullptr && !queues[count]->isEmpty()) {
                        long temp = queues[count]->removeLeft();
                        if (temp >= weight_per_minutes) {
                            temp -= weight_per_minutes;
                            queues[count]->insertLeft(temp);
                        }
                    }
                }
            }
        }
        bool isEmpty() {
            bool temp = true;
            for (int i = 0; i < maxSize; i++)
                if (!queues[i]->isEmpty())
                    return temp = false;
            return temp;
        }
};

class ShopApp {
    public:
        static void main() {
            Shop* theShop = new Shop(5);

            theShop->add(1, 55);
            theShop->add(1, 44);
            theShop->add(1, 12);
            theShop->add(1, 24);
            theShop->add(1, 96);

            theShop->add(2, 83);
            // theShop->add(2, 101);
            // theShop->add(2, 212);
            theShop->add(2, 44);
            theShop->add(2, 5);

            theShop->add(5, 4);
            theShop->add(5, 27);
            theShop->add(5, 19);
            theShop->add(5, 53);
            theShop->add(5, 8);
            theShop->add(5, 6);

            // theShop->display();

            theShop->movement();
        }
};

int main() {
    ShopApp::main();
    return 0;
}