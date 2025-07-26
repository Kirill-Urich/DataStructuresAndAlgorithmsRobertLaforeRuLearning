// task_2_5.cpp

#include <iostream>
using namespace std;

class OrdArray {
    private:
        long* a;
        int nElems;
    public:
        OrdArray(int max) {
            a = new long[max];
            nElems = 0;
        }
        int size() {
            return nElems;
        }
        int find(long searchKey) {
            int lowerBound = 0;
            int upperBound = nElems - 1;
            int curIn;

            while(true) {
                curIn = (lowerBound + upperBound) / 2;
                if (a[curIn] == searchKey)
                    return curIn;
                else if (lowerBound > upperBound)
                    return nElems;
                else {
                    if (a[curIn] < searchKey)
                        lowerBound = curIn + 1;
                    else
                        upperBound = curIn - 1;
                }
            }
        }
        void insert(long value) {
            int j;
            for (j = 0; j < nElems; j++)
                if (a[j] > value)
                    break;
            for (int k = nElems; k > j; k--)
                a[k] = a[k - 1];
            a[j] = value;
            nElems++;
        }
        bool Delete(long value) {
            int j = find(value);
            if (j == nElems)
                return false;
            else {
                for (int k = j; k < nElems; k++)
                    a[k] = a[k + 1];
                nElems--;
                return true;
            }
        }
        void merge(OrdArray temp1, OrdArray temp2) {
            int count1 = temp1.nElems;
            int count2 = temp2.nElems;
            int n = count1 + count2;
            int i = 0, j = 0;
            nElems = 0;
            while (nElems < n) {
                if (i < count1 && j < count2) {
                    if (temp1.a[i] < temp2.a[j])
                        a[nElems++] = temp1.a[i++];
                    else
                        a[nElems++] = temp2.a[j++];
                } 
                else if (i < count1 && j == count2)
                    a[nElems++] = temp1.a[i++];
                else if (i == count1 && j < count2)
                    a[nElems++] = temp2.a[j++];
            }
        }
        void display() {
            for (int j = 0; j < nElems; j++)
                cout << a[j] << " ";
            cout << endl;
        }
};

class OrderedApp {
    public:
        static void main() {
            int maxSize = 100;
            OrdArray arr1(maxSize);
            OrdArray arr2(maxSize);
            OrdArray arr3(maxSize * 2);

            arr1.insert(77);
            arr1.insert(99);
            arr1.insert(44);
            arr1.insert(55);
            arr1.insert(22);
            arr2.insert(88);
            arr2.insert(11);
            arr2.insert(00);
            arr2.insert(66);
            arr2.insert(33);

            arr1.display();
            arr2.display();

            arr3.merge(arr1, arr2);
            arr3.display();
        }
};

int main() {
    OrderedApp::main();
    return 0;
}