// project_5_3.cpp

#include <iostream>
using namespace std;

class Link {
    public:
        long dData;
        Link* next;
    public:
        Link(long d) {
            dData = d;
            next = nullptr;
        }
        void displayLink() {
            cout << dData << " ";
        }
};

class CycleList {
    private:
        Link* first;
        Link* current;
        int nItems;
    public:
        CycleList() {
            first = nullptr;
            current = nullptr;
            nItems = 0;
        }
        bool isEmpty() {
            return nItems == 0;
        }
        void insert(long d) {
            Link* newLink = new Link(d);
            if (isEmpty()) {
                first = newLink;
                current = first;
                newLink->next = first;
            } else {
                newLink->next = first;
                current->next = newLink;
                current = newLink;
            }
            ++nItems;
        }
        Link* find(long d) {
            int count = 0;
            while (count != nItems && current->dData != d) {
                current = current->next;
                count++;
            }
            return (count == nItems) ? nullptr : current;
        }
        Link* remove(long key) {
            if (isEmpty())
                return nullptr;

            int count = 0;
            Link* previous = nullptr;
            while (current->dData != key && count < nItems) {
                previous = current;
                current = current->next;
                ++count;
            }
            if (count == nItems)
                return nullptr;
            previous->next = current->next;
            current = current->next;
            --nItems;
            return current;
        }
        void displayList() {
            if (isEmpty()) {
                cout << "List is empty" << endl;
                return;
            }

            int count = 0;
            while (count != nItems) {
                current->displayLink();
                current = current->next;
                count++;
            }
            cout << endl;
        }
        void step() {
            current = current->next;
        }
};

class CycleListApp {
    public:
        static void main() {
            CycleList* theList = new CycleList();

            for (int i = 0; i < 20; i++)
                theList->insert(i);

            theList->displayList();

            long key = 7;
            Link* temp = theList->find(key);
            if (temp != nullptr)
                cout << "The " << key << " is found" << endl;
            else
                cout << "The " << key << " is not found" << endl;

            theList->displayList();

            key = 2;
            temp = theList->remove(key);
            if (temp != nullptr)
                cout << "The " << key << " is removed" << endl;
            else
                cout << "The " << key << " is not removed" << endl;
            cout << temp->dData << endl;
            theList->displayList();
        }
};

int main() {
    CycleListApp::main();
    return 0;
}