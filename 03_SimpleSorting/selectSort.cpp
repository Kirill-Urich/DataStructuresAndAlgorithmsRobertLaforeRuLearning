// selectSort.cpp
// Сортировка методом выбора

#include <iostream>
using namespace std;

class ArraySel {
    private:
        long* a;
        int nElems;
        
        void swap(int one, int two) {
            long temp = a[one];
            a[one] = a[two];
            a[two] = temp;
        }
    public:
        ArraySel(int max) {
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
        void selectionSort() {
            int out, in, min;
            for (out = 0; out < nElems - 1; out++) {
                min = out;
                for (in = out; in < nElems; in++)
                    if (a[in] < a[min])
                        min = in;
                swap(out, min);
            }
        }
};

class SelectSortApp {
    public:
        static void main() {
            int maxSize = 100;
            ArraySel arr(maxSize);

            arr.insert(77);
            arr.insert(99);
            arr.insert(44);
            arr.insert(55);
            arr.insert(22);
            arr.insert(88);
            arr.insert(11);
            arr.insert(00);
            arr.insert(66);
            arr.insert(33);

            arr.display();

            arr.selectionSort();

            arr.display();
        }
};

int main() {
    SelectSortApp::main();
    return 0;
}