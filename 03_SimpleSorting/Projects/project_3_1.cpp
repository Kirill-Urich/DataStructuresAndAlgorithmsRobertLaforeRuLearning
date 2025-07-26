// project_3_1.cpp

#include <iostream>
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
            int out_left = 0, out_right, in;
            for (out_right = nElems - 1; out_right > out_left; out_right--) {
                for (in = out_left; in < out_right; in++)
                    if (a[in] > a[in + 1])
                        swap(in, in + 1);
                for (in = out_right; in > out_left; in--)
                    if (a[in] < a[in - 1])
                        swap(in, in - 1);
            }
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
            int maxSize = 100;
            ArrayBub arr(maxSize);

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

            arr.bubbleSort();
            arr.display();
        }
};

int main() {
    BubbleSortApp::main();
    return 0;
}