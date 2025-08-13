// shellSort.cpp
// Сортировка Шелла

#include <iostream>
#include <random>
using namespace std;

class ArraySh {
    private:
        long* theArray;
        int nElems;
    public:
        ArraySh(int max) {
            theArray = new long[max];
            nElems = 0;
        }
        void insert(long value) {
            theArray[nElems] = value;
            nElems++;
        }
        void display() {
            cout << "A = ";
            for (int j = 0; j < nElems; j++)
                cout << theArray[j] << " ";
            cout << endl;
        }
        void shellSort() {
            int inner, outer;
            long temp;
            int h = 1;
            while (h <= nElems / 3)
                h = h * 3 + 1;
            
            while (h > 0) {
                for (outer = h; outer < nElems; outer++) {
                    temp = theArray[outer];
                    inner = outer;
                    while (inner > h - 1 && theArray[inner - h] >= temp) {
                        theArray[inner] = theArray[inner - h];
                        inner -= h;
                    }
                    theArray[inner] = temp;
                }
                h = (h - 1) / 3;
            }
        }
};

class ShellSortApp {
    public:
        static void main() {
            int maxSize = 10;
            ArraySh* arr = new ArraySh(maxSize);
            for (int j = 0; j < maxSize; j++) {
                long n = rand() % 100;
                arr->insert(n);
            }
            arr->display();
            arr->shellSort();
            arr->display();
        }
};

int main() {
    ShellSortApp::main();
    return 0;
}
