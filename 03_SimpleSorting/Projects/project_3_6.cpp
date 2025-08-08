// project_3_6.cpp

#include <iostream>
using namespace std;

class ArrayIns {
    private:
        long* a;
        int nElems;
        int max_size;
    public:
        ArrayIns(int max) {
            a = new long[max];
            nElems = 0;
            max_size = max;
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
            int length = 0;
            int in, out;
            for (out = 1; out < nElems; out++) {
                long temp = a[out];
                in = out;

                while (in > 0 && a[in - 1] >= temp) {
                    a[in] = a[in - 1];
                    --in;
                }
                if (a[in] == temp) {
                    length++;
                    a[in + 1] = -1;
                }
                else
                    a[in] = temp;
            }

            for (out = 1; out < nElems; out++) {
                long temp = a[out];
                in = out;
                while (in > 0 && a[in - 1] >= temp) {
                    a[in] = a[in - 1];
                    --in;
                }
                a[in] = temp;
            }
            long* temp_arr = new long[max_size];
            for (int i = 0; i < nElems - length; i++)
                temp_arr[i] = a[i + length];
            nElems -= length;
            delete[] a;
            a = temp_arr;
        }
};

class InsertSortApp {
    public:
        static void main() {
            int maxSize = 100;
            ArrayIns arr(maxSize);

            arr.insert(7);
            arr.insert(3);
            arr.insert(4);
            arr.insert(5);
            arr.insert(2);
            arr.insert(8);
            arr.insert(6);
            arr.insert(0);
            arr.insert(6);
            arr.insert(3);

            arr.display();

            arr.insertionSort();

            arr.display();
        }
};

int main() {
    InsertSortApp::main();
    return 0;
}