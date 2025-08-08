// project_5_5.cpp

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
        Link* remove() {
            if (isEmpty())
                return nullptr;

            Link* removed = nullptr;
            if (current->next == current) {
                removed = current;
                current = nullptr;
            } else {
                Link* previous = current;
                for (int count = 0; count < nItems - 1; count++)
                    previous = previous->next;
                removed = previous->next;
                previous->next = removed->next;
                current = removed->next;
            }
            --nItems;
            return removed;
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
        void displayPeek() {
            cout << current->dData << endl;
        }
        void step() {
            if (isEmpty())
                return;
            current = current->next;
        }
};

class FlaviusJosephusApp {
    public:
        static void main() {

            CycleList* newList = new CycleList();

            int all = 7;
            int count = 3;
            int human = 1;

            for (int i = 1; i <= all; i++) {
                newList->insert(i);
            }

            // newList->displayList();

            for (int j = 0; j < human; j++)
                newList->step();

            // newList->displayPeek();
            long num;

            while (!newList->isEmpty()) {
                for (int k = 0; k < count; k++)
                    newList->step();
                num = newList->remove()->dData;
                cout << num << " ";
            }

            cout << endl;
        }
};

int main() {
    FlaviusJosephusApp::main();
    return 0;
}