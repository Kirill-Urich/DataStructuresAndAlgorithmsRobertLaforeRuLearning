// interIterator.cpp
// Использование итератора связанного списка

#include <iostream>
using namespace std;

class Link {
    public:
        long dData;
        Link* next;
    public:
        Link(long dd) {
            dData = dd;
            next = nullptr;
        }
        void displayLink() {
            cout << dData << " ";
        }
};

class LinkList;

class ListIterator {
    private:
        Link* current;
        Link* previous;
        LinkList* ourList;
    public:
        ListIterator(LinkList*);
        void reset();
        bool atEnd();
        void nextLink();
        Link* getCurrent();
        void insertAfter(long);
        void insertBefore(long);
        long deleteCurrent();
};

class LinkList {
    private:
        Link* first;
    public:
        LinkList() {
            first = nullptr;
        }
        Link* getFirst() {
            return first;
        }
        void setFirst(Link* f) {
            first = f;
        }
        bool isEmpty() {
            return first == nullptr;
        }
        ListIterator* getIterator() {
            ListIterator* temp = new ListIterator(this);
            return temp;
        }
        void displayList() {
            Link* current = first;
            while (current != nullptr) {
                current->displayLink();
                current = current->next;
            }
            cout << endl;
        }
};


ListIterator::ListIterator(LinkList* list) {
    ourList = list;
    reset();
}

void ListIterator::reset() {
    current = ourList->getFirst();
    previous = nullptr;
}

bool ListIterator::atEnd() {
    return current->next == nullptr;
}

void ListIterator::nextLink() {
    previous = current;
    current = current->next;
}

Link* ListIterator::getCurrent() {
    return current;
}

void ListIterator::insertAfter(long dd) {
    Link* newLink = new Link(dd);
    if (ourList->isEmpty()) {
        ourList->setFirst(newLink);
        current = newLink;
    } else {
        newLink->next = current->next;
        current->next = newLink;
        nextLink();
    }
}

void ListIterator::insertBefore(long dd) {
    Link* newLink = new Link(dd);
    if (previous == nullptr) {
        newLink->next = ourList->getFirst();
        ourList->setFirst(newLink);
        reset();
    } else {
        newLink->next = previous->next;
        previous->next = newLink;
        current = newLink;
    }
}

long ListIterator::deleteCurrent() {
    long value = current->dData;
    if (previous == nullptr) {
        ourList->setFirst(current->next);
        reset();
    } else {
        previous->next = current->next;
        if (atEnd())
            reset();
        else
            current = current->next;
    }
    return value;
}

class InterIterApp {
    public:
        static void main() {
            LinkList* theList = new LinkList();
            ListIterator* iter1 = theList->getIterator();
            long value;

            iter1->insertAfter(20);
            iter1->insertAfter(40);
            iter1->insertAfter(80);
            iter1->insertBefore(60);

            char choice;
            while (true) {
                cout << "Enter first letter of show, reset, "
                     << "next, get, before, after, delete: ";
                cout.flush();
                cin >> choice;

                switch(choice) {
                    case 's':
                        if (!theList->isEmpty())
                            theList->displayList();
                        else
                            cout << "List is empty" << endl;
                        break;
                    case 'r':
                        iter1->reset();
                        break;
                    case 'n':
                        if (!theList->isEmpty() && !iter1->atEnd())
                            iter1->nextLink();
                        else
                            cout << "Can't go to next link" << endl;
                        break;
                    case 'g':
                        if (!theList->isEmpty()) {
                            value = iter1->getCurrent()->dData;
                            cout << "Returned " << value << endl;
                        } else
                            cout << "List is empty" << endl;
                        break;
                    case 'b':
                        cout << "Enter value to insert: ";
                        cout.flush();
                        cin >> value;
                        iter1->insertBefore(value);
                        break;
                    case 'a':
                        cout << "Enter value to insert: ";
                        cout.flush();
                        cin >> value;
                        iter1->insertAfter(value);
                        break;
                    case 'd':
                        if (!theList->isEmpty()) {
                            value = iter1->deleteCurrent();
                            cout << "Deleted " << value << endl;
                        } else
                            cout << "Can't delete" << endl;
                        break;
                    default:
                        cout << "Invalid entry" << endl;
                }
            }
        }
};

int main() {
    InterIterApp::main();
    return 0;
}