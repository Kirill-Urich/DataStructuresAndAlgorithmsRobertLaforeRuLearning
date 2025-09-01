// heapSort.cpp
// Пирамидальная сортировка

#include <iostream>
#include <experimental/random>
using namespace std;

class Node {
    private:
        int iData;
    public:
        Node(int key) : iData(key) {}
        int getKey() {
            return iData;
        }
};

class Heap {
    private:
        Node** heapArray;
        int maxSize;
        int currentSize;
    public:
        Heap(int mx) {
            maxSize = mx;
            currentSize = 0;
            heapArray = new Node*[maxSize];
        }
        Node* remove() {
            Node* root = heapArray[0];
            heapArray[0] = heapArray[--currentSize];
            trickleDown(0);
            return root;
        }
        void trickleDown(int index) {
            int largerChild;
            Node* top = heapArray[index];
            while (index < currentSize / 2) {
                int leftChild = index * 2 + 1;
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
        void displayHeap() {
            int nBlanks = 32;
            int itemsPerRow = 1;
            int column = 0;
            int j = 0;
            string dots = "...............................";
            cout << dots << dots << endl;

            while (currentSize > 0) {
                if (column == 0)
                    for (int k = 0; k < nBlanks; k++)
                        cout << " ";

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
        void displayArray() {
            for (int j = 0; j < maxSize; j++)
                cout << heapArray[j]->getKey() << " ";
            cout << endl;
        }
        void insertAt(int index, Node* newNode) {
            heapArray[index] = newNode;
        }
        void incrementSize() {
            currentSize++;
        }
};

class HeapSortApp {
    public:
        static void main() {
            int size, j;
            cout << "Enter number of items: ";
            cin >> size;
            Heap* theHeap = new Heap(size);

            for (j = 0; j < size; j++) {
                int random = experimental::randint(0, 100);
                Node* newNode = new Node(random);
                theHeap->insertAt(j, newNode);
                theHeap->incrementSize();
            }

            cout << "Random: ";
            theHeap->displayArray();

            for (j = size / 2; j >= 0; j--)
                theHeap->trickleDown(j);

            cout << "Heap: ";
            theHeap->displayArray();
            theHeap->displayHeap();

            for (j = size - 1; j >= 0; j--) {
                Node* biggestNode = theHeap->remove();
                theHeap->insertAt(j, biggestNode);
            }
            cout << "Sorted: ";
            theHeap->displayArray();
        }
};

int main() {
    HeapSortApp::main();
    return 0;
}