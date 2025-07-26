// task_2_3.cpp

#include <iostream>
using namespace std;

class HighArray {
    private:
        long* a;
        int nElems;
    public:
        HighArray(int max) {
            a = new long[max];
            nElems = 0;
        }
        bool find(long searchKey) {
            int j;
            for (j = 0; j < nElems; j++)
                if (a[j] == searchKey)
                    break;
            if (j == nElems)
                return false;
            else
                return true;
        }
        void insert(long value) {
            a[nElems] = value;
            nElems++;
        }
        bool Delete(long value) {
            int j;
            for (j = 0; j < nElems; j++)
                if (value == a[j])
                    break;
            if (j == nElems)
                return false;
            else {
                for (int k = j; k < nElems; k++)
                    a[k] = a[k + 1];
                nElems--;
                return true;
            }
        }
        void display() {
            for (int j = 0; j < nElems; j++)
                cout << a[j] << " ";
            cout << endl;
        }
        long removeMax() {
            if (nElems == 0)
                return -1;
            else {
                int max_el = a[0];
                for (int i = 0; i < nElems; i++)
                    if (max_el < a[i])
                        max_el = a[i];
                this->Delete(max_el);
                return max_el;
            }
        }
};

class HighArrayApp {
    public:
        static void main() {
            int maxSize = 100;
            HighArray arr(maxSize);
            HighArray brr(maxSize);

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

            while (true) {
                int elem = arr.removeMax();
                if (elem == -1)
                    break;
                brr.insert(elem);
            }
            
            brr.display();
        }
};

int main() {
    HighArrayApp::main();
    return 0;
}