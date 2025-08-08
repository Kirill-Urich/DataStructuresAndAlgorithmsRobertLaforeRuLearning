// task_5_2.cpp

// linklist.cpp
// Работа со связанным списком

#include <iostream>
using namespace std;

class Link {
    public:
        int iData;
        double dData;
        Link* next;
    public:
        Link(int id, double dd) {
            iData = id;
            dData = dd;
        }
        void displayLink() {
            cout << "{" << iData << ", " << dData << "} ";
        }
};

class LinkList {
    private:
        Link* first;
    public:
        LinkList() {
            first = nullptr;
        }
        bool isEmpty() {
            return first == nullptr;
        }
        void insertFirst(int id, double dd) {
            Link* newLink = new Link(id, dd);
            newLink->next = first;
            first = newLink;
        }
        Link* deleteFirst() {
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

class LinkListApp {
    public:
        static void main() {
            LinkList* theList = new LinkList();

            unsigned long i = 0;
            while (true) {
                theList->insertFirst(i, i);
                i++;
                if (i % 1'000'000 == 0)
                    cout << i << endl;
            }

            theList->displayList();
            while (!theList->isEmpty()) {
                Link* aLink = theList->deleteFirst();
                cout << "Deleted ";
                aLink->displayLink();
                cout << endl;
            }
            theList->displayList();
        }
};

int main() {
    LinkListApp::main();
    return 0;
}