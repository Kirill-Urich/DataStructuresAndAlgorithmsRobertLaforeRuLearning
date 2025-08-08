// project_3_3.cpp

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
        void noDups() {
            int k = 0;
            long* b = new long[nElems];
            for (int i = 0; i < nElems; i++) {
                if (a[i] != a[i + 1])
                    b[k++] = a[i];
            }
            delete[] a;
            a = b;
            nElems = k;
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
            arr.insert(44);
            arr.insert(88);
            arr.insert(11);
            arr.insert(11);
            arr.insert(66);
            arr.insert(77);

            arr.display();

            arr.insertionSort();

            arr.display();

            arr.noDups();
            arr.display();
        }
};

int main() {
    InsertSortApp::main();
    return 0;
}