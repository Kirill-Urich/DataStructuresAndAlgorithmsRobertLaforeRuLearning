// heap.cpp
// Работа с пирамидой

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

class HeapApp {
    public:
        static void main() {
            int value, value2;
            Heap* theHeap = new Heap(31);
            bool success;
            theHeap->insert(70);
            theHeap->insert(40);            
            theHeap->insert(50);
            theHeap->insert(20);
            theHeap->insert(60);
            theHeap->insert(100);
            theHeap->insert(80);
            theHeap->insert(30);
            theHeap->insert(10);
            theHeap->insert(90);

            char choice;
            while (true) {
                cout << "Enter first letter of ";
                cout << "show, insert, remove, change: ";
                cin >> choice;

                switch(choice) {
                    case 's':
                        theHeap->displayHeap();
                        break;
                    case 'i':
                        cout << "Enter value to insert: ";
                        cin >> value;
                        success = theHeap->insert(value);
                        if (!success)
                            cout << "Can't insert: heap full" << endl;
                        break;
                    case 'r':
                        if (!theHeap->isEmpty())
                            theHeap->remove();
                        else
                            cout << "Can't remove: heap empty" << endl;
                        break;
                    case 'c':
                        cout << "Enter current index of item: ";
                        cin >> value;
                        cout << "Enter new key: ";
                        cin >> value2;
                        success = theHeap->change(value, value2);
                        if (!success)
                            cout << "Invalid index" << endl;
                        break;
                    default:
                        cout << "Invalid entry\n" << endl;
                }
            }
        }
};

int main() {
    HeapApp::main();
    return 0;
}