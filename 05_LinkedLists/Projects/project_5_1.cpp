// project_5_1.cpp

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

class PriorityQSortedList {
    private:
        SortedList* queList;
    public:
        PriorityQSortedList() {
            queList = new SortedList();
        }
        void insert(long item) {
            queList->insert(item);
        }
        long remove() {
            return queList->remove()->dData;
        }
        bool isEmpty() {
            return queList->isEmpty();
        }
        void displayPriorityQ() {
            queList->displayList();
        }
};

class PriorityQSortedListApp {
    public:
        static void main() {
            PriorityQSortedList* thePQ = new PriorityQSortedList();

            thePQ->insert(30);
            thePQ->insert(50);
            thePQ->insert(10);
            thePQ->insert(40);
            thePQ->insert(20);

            thePQ->displayPriorityQ();

            thePQ->remove();
            thePQ->remove();

            thePQ->displayPriorityQ();
        }
};

int main() {
    PriorityQSortedListApp::main();
    return 0;
}