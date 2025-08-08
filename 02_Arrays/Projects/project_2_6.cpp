// task_2_6.cpp

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
        void noDups() {
            int count = 0;
            int uniq_elem = -1;
            for (int i = 0; i < nElems; i++)
                for (int j = i + 1; j < nElems; j++)
                    if (a[j] == a[i]) {
                        a[j] = uniq_elem;
                        count++;
                    }
            while (count != 0) {
                this->Delete(uniq_elem);
                count--;
            }
            
        }
        void display() {
            for (int j = 0; j < nElems; j++)
                cout << a[j] << " ";
            cout << endl;
        }
};

class HighArrayApp {
    public:
        static void main() {
            int maxSize = 100;
            HighArray arr(maxSize);

            arr.insert(77);
            arr.insert(99);
            arr.insert(44);
            arr.insert(77);
            arr.insert(22);
            arr.insert(88);
            arr.insert(11);
            arr.insert(11);
            arr.insert(66);
            arr.insert(88);

            arr.display();

            arr.noDups();

            arr.display();
        }
};

int main() {
    HighArrayApp::main();
    return 0;
}