// project_12_3.cpp

#include <iostream>
using namespace std;

class Node {
    private:
        int iData;
    public:
        Node(int key) {
            iData = key;
        }
        int getKey() {
            return iData;
        }
        void setKey(int id) {
            iData = id;
        } 
};

class Heap {
    private:
        Node** heapArray;
        int maxSize;
        int currentSize;
    private:
        void trickleUp(int index) {
            int parent = (index - 1) / 2;
            Node* bottom = heapArray[index];
            while (index > 0 && heapArray[parent]->getKey() < bottom->getKey()) {
                heapArray[index] = heapArray[parent];
                index = parent;
                parent = (parent - 1) / 2;
            }
            heapArray[index] = bottom;
        }
        void trickleDown(int index) {
            int largerChild;
            Node* top = heapArray[index];
            while (index < currentSize / 2) {
                int leftChild = 2 * index + 1;
                int rightChild = leftChild + 1;
                if (rightChild < currentSize && heapArray[leftChild]->getKey() < heapArray[rightChild]->getKey())
                    largerChild = rightChild;
                else
                    largerChild = leftChild;
                
                if (top->getKey() >= heapArray[largerChild]->getKey())
                    break;

                heapArray[index] = heapArray[largerChild];
                index = largerChild;
            }
            heapArray[index] = top; 
        }
    public:
        Heap(int mx) {
            maxSize = mx;
            currentSize = 0;
            heapArray = new Node*[maxSize];
        }
        bool isEmpty() {
            return currentSize == 0;
        }
        bool insert(int key) {
            if (currentSize == maxSize)
                return false;
            Node* newNode = new Node(key);
            heapArray[currentSize] = newNode;
            trickleUp(currentSize++);
            return true;
        }
        Node* remove() {
            Node* root = heapArray[0];
            heapArray[0] = heapArray[--currentSize];
            trickleDown(0);
            return root;
        }
        bool change(int index, int newValue) {
            if (index < 0 || index >= currentSize)
                return false;
            int oldValue = heapArray[index]->getKey();
            heapArray[index]->setKey(newValue);

            if (oldValue < newValue)
                trickleUp(index);
            else
                trickleDown(index);
            return true;
        }
        int getLast() {
            return heapArray[currentSize - 1]->getKey();
        }
        void displayHeap() {
            cout << "heapArray: ";
            for (int m = 0; m < currentSize; m++) {
                if (heapArray[m] != nullptr)
                    cout << heapArray[m]->getKey() << " ";
                else
                    cout << "-- ";
            }
            cout << endl;

            int nBlanks = 32;
            int itemsPerRow = 1;
            int column = 0;
            int j = 0;
            string dots = "...............................";
            cout << dots << dots << endl;

            while (currentSize > 0) {
                if (column == 0)
                    for (int k = 0; k < nBlanks; k++)
                        cout << ' ';
                
                cout << heapArray[j]->getKey();
                if (++j == currentSize)
                    break;
                
                if (++column == itemsPerRow) {
                    nBlanks /= 2;
                    itemsPerRow *= 2;
                    column = 0;
                    cout << endl;
                } else 
                    for (int k = 0; k < nBlanks * 2 - 2; k++)
                        cout << ' ';
            }
            cout << '\n' << dots << dots << endl;
        }
};

class PriorityQ {
    private:
        int maxSize;
        Heap* queArray;
        int nItems;
    public:
        PriorityQ(int s) {
            maxSize = s;
            queArray = new Heap(maxSize);
            nItems = 0;
        }
        void insert(int item) {
            queArray->insert(item);
            ++nItems;
        }
        int remove() {
            Node* tempNode = queArray->remove();
            --nItems;
            return tempNode->getKey();
        }
        int peekMin() {
            return queArray->getLast();
        }
        bool isEmpty() {
            return nItems == 0;
        }
        bool isFull() {
            return nItems == maxSize;
        }
};

class PriorityQApp {
    public:
        static void main() {
            PriorityQ* thePQ = new PriorityQ(10);
            thePQ->insert(30);
            thePQ->insert(50);
            thePQ->insert(10);
            thePQ->insert(40);
            thePQ->insert(20);
            thePQ->remove();

            while (!thePQ->isEmpty()) {
                int item = thePQ->remove();
                cout << item << " ";
            }

            cout << endl;
        }
};

int main() {
    PriorityQApp::main();
    return 0;
}
