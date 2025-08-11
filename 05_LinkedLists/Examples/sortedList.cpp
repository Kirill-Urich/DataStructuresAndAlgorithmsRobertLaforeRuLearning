// sortedList.cpp
// Работа с сортированным списком

#include <iostream>
using namespace std;

class Link {
    public:
        long dData;
        Link* next;
    public:
        Link(long dd) : dData(dd) {}
        void displayLink() {
            cout << dData << " ";
        }
};

class SortedList {
    private:
        Link* first;
    public:
        SortedList() {
            first = nullptr;
        }
        bool isEmpty() {
            return first == nullptr;
        }
        void insert(long key) {
            Link* newLink = new Link(key);
            Link* previous = nullptr;
            Link* current = first;

            while (current != nullptr && key > current->dData) {
                previous = current;
                current = current->next;
            }
            if (previous == nullptr)
                first = newLink;
            else
                previous->next = newLink;
            newLink->next = current;
        }
        Link* remove() {
            Link* temp = first;
            first = first->next;
            temp->next = nullptr;
            return temp;
        }
        void displayList() {
            cout << "List (first-->last): ";
            Link* current = first;
            while (current != nullptr) {
                current->displayLink();
                current = current->next;
            }
            cout << endl;
        }
};

class SortedListApp {
    public:
        static void main() {
            SortedList* theSortedList = new SortedList();
            theSortedList->insert(20);
            theSortedList->insert(40);

            theSortedList->displayList();

            theSortedList->insert(10);
            theSortedList->insert(30);
            theSortedList->insert(50);

            theSortedList->displayList();

            theSortedList->remove();

            theSortedList->displayList();
        }
};

int main() {
    SortedListApp::main();
    return 0;
}