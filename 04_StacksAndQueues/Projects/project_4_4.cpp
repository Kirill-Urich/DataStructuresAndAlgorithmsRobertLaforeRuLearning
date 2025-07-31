// project_4_5.cpp

#include <iostream>
using namespace std;

class PriorityQ {
    private:
        int maxSize;
        long* queArray;
        int nItems;
    public:
        PriorityQ(int s) {
            maxSize = s;
            queArray = new long[maxSize];
            nItems = 0;
        }
        void insert(long item) {
            if (isFull()) throw "PriorityQ is fulled.";
            queArray[nItems++] = item;
        }
        long remove() {
            if (isEmpty()) throw "PriorityQ is empty.";
            int min = queArray[0];
            int min_index = 0;
            
            for (int j = 1; j < nItems; j++) {
                if (queArray[j] < min) {
                    min = queArray[j];
                    min_index = j;
                }
            }

            for (int i = min_index; i < nItems - 1; i++)
                queArray[i] = queArray[i + 1];
            --nItems;

            return min;
        }
        long peekMin() {
            return queArray[--nItems];
        }
        bool isEmpty() {
            return nItems == 0;
        }
        bool isFull() {
            return nItems == maxSize;
        }
        void display() {
            for (int i = 0; i < nItems; i++)
                cout << queArray[i] << " ";
            cout << endl;
        }
};

class PriorityQApp {
    public:
        static void main() {
            PriorityQ* thePQ = new PriorityQ(5);
            thePQ->insert(30);
            thePQ->insert(50);
            thePQ->insert(10);
            thePQ->insert(40);
            thePQ->insert(20);

            thePQ->display();

            thePQ->remove();
            thePQ->display();
        }
};

int main() {
    PriorityQApp::main();
    return 0;
}