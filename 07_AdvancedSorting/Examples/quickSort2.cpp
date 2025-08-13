// quickSort2.cpp
// Быстрая сортировка с определением медианы по трем точкам

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
            int size = right - left + 1;
            if (size <= 3)
                manualSort(left, right);
            else {
                long median = medianOf3(left, right);
                int partition = partitionIt(left, right, median);
                recQuickSort(left, partition - 1);
                recQuickSort(partition + 1, right);
            }
        }
        long medianOf3(int left, int right) {
            int center = (left + right) / 2;
            if (theArray[left] > theArray[center])
                swap(left, center);
            if (theArray[left] > theArray[right])
                swap(left, right);
            if (theArray[center] > theArray[right])
                swap(center, right);
            swap(center, right - 1);
            return theArray[right - 1];
        }
        int partitionIt(int left, int right, long pivot) {
            int leftPtr = left;
            int rightPtr = right - 1;
            while (true) {
                while (theArray[++leftPtr] < pivot);
                while (theArray[--rightPtr] > pivot);
                if (leftPtr >= rightPtr)
                    break;
                else
                    swap(leftPtr, rightPtr);
            }
            swap(leftPtr, right - 1);
            return leftPtr;
        }
        void manualSort(int left, int right) {
            int size = right - left + 1;
            if (size <= 1)
                return;
            if (size == 2) {
                if (theArray[left] > theArray[right])
                    swap(left, right);
                return;
            } else {
                if (theArray[left] > theArray[right - 1])
                    swap(left, right - 1);
                if (theArray[left] > theArray[right])
                    swap(left, right);
                if (theArray[right - 1] > theArray[right])
                    swap(right - 1, right);
            }
        }
        void swap(int dex1, int dex2) {
            long temp = theArray[dex1];
            theArray[dex1] = theArray[dex2];
            theArray[dex2] = temp;
        }
};

class QuickSort2App {
    public:
        static void main() {
            int maxSize = 16;
            ArrayIns* arr = new ArrayIns(maxSize);
            for (int j = 0; j < maxSize; j++)
                arr->insert(rand() % 100);
            arr->display();
            arr->quickSort();
            arr->display();
        }
};

int main() {
    QuickSort2App::main();
    return 0;
}