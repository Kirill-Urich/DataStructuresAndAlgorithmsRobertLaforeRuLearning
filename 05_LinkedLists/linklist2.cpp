// linklist2.cpp
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
        void insertFirst(int id, double dd) {
            Link* newLink = new Link(id, dd);
            newLink->next = first;
            first = newLink;
        }
        Link* find(int key) {
            Link* current = first;
            while (current->iData != key) {
                if (current->next == nullptr)
                    return nullptr;
                else
                    current = current->next;
            }
            return current;
        }
        Link* Delete(int key) {
            Link* current = first;
            Link* previous = first;
            while (current->iData != key) {
                if (current->next == nullptr)
                    return nullptr;
                else {
                    previous = current;
                    current = current->next;
                }
            }
            if (current == first)
                first = first->next;
            else
                previous->next = current->next;
            return current;
        }
        void displayList() {
            Link* current = first;
            cout << "List (first-->last): ";
            while (current != nullptr) {
                current->displayLink();
                current = current->next;
            }
            cout << endl;
        }
};

class LinkList2App {
    public:
        static void main() {
            LinkList* theList = new LinkList();

            theList->insertFirst(22, 2.99);
            theList->insertFirst(44, 4.99);
            theList->insertFirst(66, 6.99);
            theList->insertFirst(88, 8.99);

            theList->displayList();

            Link* f = theList->find(44);
            if (f != nullptr)
                cout << "Found link with key " << f->iData << endl;
            else
                cout << "Can't find link" << endl;

            Link* d = theList->Delete(66);
            if (d != nullptr)
                cout << "Deleted link with key " << d->iData << endl;
            else
                cout << "Can't delete link";

            theList->displayList();
        }
};

int main() {
    LinkList2App::main();
    return 0;
}