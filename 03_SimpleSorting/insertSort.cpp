// insertSort.cpp
// Сортировка методом вставки

#include <iostream>
using namespace std;

class ArrayIns {
    private:
        long* a;
        int nElems;
    public:
        ArrayIns(int max) {
            a = new long[max];
            nElems = 0;
        }
        void insert(long value) {
            a[nElems++] = value;
        }
        void display() {
            for (int j = 0; j < nElems; j++)
                cout << a[j] << " ";
            cout << endl;
        }
        void insertionSort() {
            int in, out;
            for (out = 1; out < nElems; out++) {
                long temp = a[out];
                in = out;
                while (in > 0 && a[in - 1] >= temp) {
                    a[in] = a[in - 1];
                    --in;
                }
                a[in] = temp;
            }
        }
};

class InsertSortApp {
    public:
        static void main() {
            int maxSize = 100;
            ArrayIns arr(maxSize);

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

            arr.insertionSort();

            arr.display();
        }
};

int main() {
    InsertSortApp::main();
    return 0;
}