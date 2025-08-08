// task_3_1.cpp

// bubbleSort.cpp
// Пузырьковая сортировка

#include <iostream>
#include <random>
using namespace std;

class ArrayBub {
    private:
        long* a;
        int nElems;
    public:
        ArrayBub(int max) {
            a = new long[max];
            nElems = 0;
        }
        void insert(long value) {
            a[nElems] = value;
            nElems++;
        }
        void display() {
            for (int j = 0; j < nElems; j++)
                cout << a[j] << " ";
            cout << endl;
        }
        void bubbleSort() {
            int out, in;
            for (out = nElems - 1; out > 1; out--)
                for (in = 0; in < out; in++)
                    if (a[in] > a[in + 1])
                        swap(in, in + 1);
        }
        void swap(int one, int two) {
            long temp = a[one];
            a[one] = a[two];
            a[two] = temp;
        }
};

class BubbleSortApp {
    public:
        static void main() {
            int maxSize = 100'000;
            ArrayBub arr(maxSize);

            int start = 0;
            int end = 1'000'000;
            for (int j = 0; j < maxSize; j++) {
                long n = rand() % (end - start + 1) + start;
                arr.insert(n);
            }

            // arr.display();

            arr.bubbleSort();
            // arr.display();
        }
};

int main() {
    BubbleSortApp::main();
    return 0;
}