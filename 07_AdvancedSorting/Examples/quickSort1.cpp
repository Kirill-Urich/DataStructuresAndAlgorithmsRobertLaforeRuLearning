// quickSort1.cpp
// Простая версия быстрой сортировки

#include <iostream>
#include <random>
using namespace std;

class ArrayIns {
    private:
        long* theArray;
        int nElems;
    public:
        ArrayIns(int max) {
            theArray = new long[max];
            nElems = 0;
        }
        void insert(long value) {
            theArray[nElems++] = value;
        }
        void display() {
            cout << "A = ";
            for (int j = 0; j < nElems; j++)
                cout << theArray[j] << " ";
            cout << endl;
        }
        void quickSort() {
            recQuickSort(0, nElems - 1);
        }
        void recQuickSort(int left, int right) {
            if (right - left <= 0)
                return;
            else {
                long pivot = theArray[right];
                int partition = partitionIt(left, right, pivot);
                recQuickSort(left, partition - 1);
                recQuickSort(partition + 1, right);
            }
        }
        int partitionIt(int left, int right, long pivot) {
            int leftPtr  = left - 1;
            int rightPtr = right;
            while (true) {
                while (theArray[++leftPtr] < pivot);
                while (rightPtr > 0 && theArray[--rightPtr] > pivot);
                if (leftPtr >= rightPtr)
                    break;
                else
                    swap(leftPtr, rightPtr);
            }
            swap(leftPtr, right);   // перестановка опорного элемента
            return leftPtr;
        }
        void swap(int dex1, int dex2) {
            long temp = theArray[dex1];
            theArray[dex1] = theArray[dex2];
            theArray[dex2] = temp;
        }
};

class QuickSort1App {
    public:
        static void main() {
            int maxSize = 16;
            ArrayIns* arr = new ArrayIns(maxSize);
            for (int j = 0; j < maxSize; j++) {
                arr->insert(rand() % 100);
            }
            arr->display();
            arr->quickSort();
            arr->display();
        }
};

int main() {
    QuickSort1App::main();
    return 0;
}