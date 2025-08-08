// listInsertionSort.cpp
// Применение сортированного списка для сортировки массива

#include <iostream>
#include <random>
using namespace std;

const int SIZE = 10;

class Link {
    public:
        long dData;
        Link* next;
    public:
        Link(long dd) {
            dData = dd;
        }
};

class SortedList {
    private:
        Link* first;
    public:
        SortedList() {
            first = nullptr;
        }
        SortedList(Link** linkArr) {
            first = nullptr;
            for (int j = 0; j < SIZE; j++)
                insert(linkArr[j]);
        }
        void insert(Link* k) {
            Link* previous = nullptr;
            Link* current = first;
            
            while (current != nullptr && k->dData > current->dData) {
                previous = current;
                current = current->next;
            }
            if (previous == nullptr)
                first = k;
            else
                previous->next = k;
            k->next = current;
        }
        Link* remove() {
            Link* temp = first;
            first = first->next;
            return temp;
        }
};

class ListInsertionSortApp {
    public:
        static void main() {
            Link** linkArray = new Link*[SIZE];

            for (int j = 0; j < SIZE; j++) {
                int n = rand() % 100;
                Link* newLink = new Link(n);
                linkArray[j] = newLink;
            }
            cout << "Unsorted array: ";
            for (int j = 0; j < SIZE; j++)
                cout << linkArray[j]->dData << " ";
            cout << endl;

            SortedList* theSortedList = new SortedList(linkArray);

            for (int j = 0; j < SIZE; j++)
                linkArray[j] = theSortedList->remove();

            cout << "Sorted Array: ";
            for (int j = 0; j < SIZE; j++)
                cout << linkArray[j]->dData << " ";
            cout << endl;
        }
};

int main() {
    ListInsertionSortApp::main();
    return 0;
}