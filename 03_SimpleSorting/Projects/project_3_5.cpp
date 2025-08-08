// project_3_5.cpp

#include <iostream>
#include <random>
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

            int copy_count = 0;
            int compare_count = 0;

            for (out = 1; out < nElems; out++) {
                long temp = a[out];
                copy_count++;
                in = out;
                // while (in > 0 && a[in - 1] >= temp) {
                    // a[in] = a[in - 1];
                    // --in;
                // }
                while (true) {
                    if (in > 0) {
                        if (a[in - 1] >= temp) {
                            a[in] = a[in - 1];
                            --in;
                            copy_count++;
                            compare_count++;
                        }
                        else
                            break;
                    }
                    else
                        break;
                }
                a[in] = temp;
                copy_count++;
            }

            cout << "copy_count = " << copy_count << endl;
            cout << "compare_count = " << compare_count << endl;
        }
};

class InsertSortApp {
    public:
        static void main() {
            int maxSize = 10'000;
            ArrayIns arr(maxSize);

            for (int i = 0; i < 9'999; i++)
                arr.insert(rand() % (10000));
    
            // arr.display();

            arr.insertionSort();

            // arr.display();
        }
};

int main() {
    InsertSortApp::main();
    return 0;
}