// task_2_4.cpp

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
            int lowerBound = 0;
            int upperBound = nElems - 1;
            int curIn;

            while (true) {
                curIn = (lowerBound + upperBound) / 2;
                if (lowerBound > upperBound) {
                    j = lowerBound;
                    break;
                }
                else {
                    if (a[curIn] > value)
                        upperBound = curIn - 1;
                    else
                        lowerBound = curIn + 1;
                }
            }

            for (int k = nElems; k > j; k--)
                a[k] = a[k - 1];
            a[j] = value;
            nElems++;

        }
        bool Delete(long value) {
            int j;
            int lowerBound = 0;
            int upperBound = nElems - 1;
            int curIn;
            while (true) {
                curIn = (lowerBound + upperBound) / 2;
                if (a[curIn] == value) {
                    j = curIn;
                    break;
                }
                else if (lowerBound > upperBound) 
                    return false;
                else {
                    if (a[curIn] > value)
                        upperBound = curIn - 1;
                    else
                        lowerBound = curIn + 1;
                }
            }

            for (int k = j; k < nElems; k++)
                a[k] = a[k + 1];
            nElems--;
            return true;
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
            OrdArray arr(maxSize);

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

            int searchKey = 55;
            if (arr.find(searchKey) != arr.size())
                cout << "Found " << searchKey << endl;
            else
                cout << "Can't find " << searchKey << endl;

            arr.display();

            arr.Delete(00);
            arr.Delete(55);
            arr.Delete(99);

            arr.display();
        }
};

int main() {
    OrderedApp::main();
    return 0;
}