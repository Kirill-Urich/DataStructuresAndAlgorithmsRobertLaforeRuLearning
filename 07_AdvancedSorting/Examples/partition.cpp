// partition.cpp
// Демонстрация разбиения в массиве

#include <iostream>
#include <random>
using namespace std;

class ArrayPar {
    private:
        long* theArray;
        int nElems;
    public:
        ArrayPar(int max) {
            theArray = new long[max];
            nElems = 0;
        }
        void insert(long value) {
            theArray[nElems++] = value;
        }
        int size() {
            return nElems;
        }
        void display() {
            cout << "A = ";
            for (int j = 0; j < nElems; j++)
                cout << theArray[j] << " ";
            cout << endl;
        }
        int partitionIt(int left, int right, long pivot) {
            int leftPtr = left - 1;
            int rightPtr = right + 1;
            while (true) {
                while (leftPtr < right && theArray[++leftPtr] < pivot) {}   // поиск большего элемента
                while (rightPtr > left && theArray[--rightPtr] > pivot) {}  // поиск меньшего элемента
                if (leftPtr >= rightPtr)
                    break;
                else
                    swap(leftPtr, rightPtr);
            }
            return leftPtr;
        }
        void swap(int dex1, int dex2) {
            long temp = theArray[dex1];
            theArray[dex1] = theArray[dex2];
            theArray[dex2] = temp;
        }
};

class PartitionApp {
    public:
        static void main() {
            int maxSize = 16;
            ArrayPar* arr = new ArrayPar(maxSize);
            for (int j = 0; j < maxSize; j++)
                arr->insert(rand() % 100);
            
            arr->display();
            long pivot = 55;
            cout << "Pivot is " << pivot;
            int size = arr->size();
            int partDex = arr->partitionIt(0, size - 1, pivot);
            cout << ". Partition is at index " << partDex << endl;
            arr->display();
        }
};

int main() {
    PartitionApp::main();
    return 0;
}