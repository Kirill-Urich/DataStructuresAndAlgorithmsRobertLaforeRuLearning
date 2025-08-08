// project_5_2.cpp

#include <iostream>
using namespace std;

class Link {
    public:
        long dData;
        Link* next;
        Link* previous;
    public:
        Link(long d) {
            dData = d;
        }
        void displayLink() {
            cout << dData << " ";
        }
};

class DoublyLinkedList {
    private:
        Link* first;
        Link* last;
    public:
        DoublyLinkedList() {
            first = nullptr;
            last = nullptr;
        }
        bool isEmpty() {
            return first == nullptr;
        }
        void insertFirst(long dd) {
            Link* newLink = new Link(dd);
            if (isEmpty())
                last = newLink;
            else
                first->previous = newLink;
            newLink->next = first;
            first = newLink;
        }
        void insertLast(long dd) {
            Link* newLink = new Link(dd);
            if (isEmpty())
                first = newLink;
            else {
                last->next = newLink;
                newLink->previous = last;
            }
            last = newLink;
        }
        Link* deleteFirst() {
            Link* temp = first;
            if (first->next == nullptr)
                last = nullptr;
            else
                first->next->previous = nullptr;
            first = first->next;
            return temp;
        }
        Link* deleteLast() {
            Link* temp = last;
            if (first->next == nullptr)
                first = nullptr;
            else
                last->previous->next = nullptr;
            last = last->previous;
            return temp;
        }
        bool insertAfter(long key, long dd) {
            Link* current = first;
            while (current->dData != key) {
                current = current->next;
                if (current == nullptr)
                    return false;
            }
            Link* newLink = new Link(dd);
            if (current == last) {
                newLink->next = nullptr;
                last = newLink;
            } else {
                newLink->next = current->next;
                current->next->previous = newLink;
            }
            newLink->previous = current;
            current->next = newLink;
            return true;
        }
        Link* deleteKey(long key) {
            Link* current = first;
            while (current->dData != key) {
                current = current->next;
                if (current == nullptr)
                    return nullptr;
            }
            if (current == first)
                first = current->next;
            else
                current->previous->next = current->next;

            if (current == last)
                last = current->previous;
            else
                current->next->previous = current->previous;
            
            return current;
        }
        void displayForward() {
            cout << "List (first-->last): ";
            Link* current = first;
            while (current != nullptr) {
                current->displayLink();
                current = current->next;
            }
            cout << endl;
        }
        void displayBackward() {
            cout << "List (last-->first): ";
            Link* current = last;
            while (current != nullptr) {
                current->displayLink();
                current = current->previous;
            }
            cout << endl;
        }
};

class Deque {
    private:
        int maxSize;
        DoublyLinkedList* dequeList;
        int nItems;
    public:
        Deque(int s) {
            maxSize = s;
            dequeList = new DoublyLinkedList;
            // front = 0;
            // rear = -1;
            // nItems = 0;
        }
        void insertRight(long j) {
            dequeList->insertLast(j);
            nItems++;
        }
        void insertLeft(long j) {
            dequeList->insertFirst(j);
            nItems++;
        }
        long removeLeft() {
            if (isEmpty())
                throw "The Deque is empty.";
            nItems--;
            return dequeList->deleteFirst()->dData;
        }
        long removeRight() {
            if (isEmpty())
                throw "The Deque is empty.";
            nItems--;
            return dequeList->deleteLast()->dData;
        }
        bool isEmpty() {
            return dequeList->isEmpty();
        }
        bool isFull() {
            return nItems == maxSize;
        }
        int size() {
            return nItems;
        }
        void display() {
            dequeList->displayForward();
        }
};

class DequeApp {
    public:
        static void main() {
            Deque* deque = new Deque(5);

            cout << "Insertion: " << endl;
            deque->insertRight(44);
            deque->insertRight(77);
            deque->insertLeft(66);
            deque->insertRight(55);
            deque->insertLeft(99);
            deque->display();

            cout << "Removing: " << endl;
            deque->removeLeft();
            deque->removeRight();
            deque->display();
        }
};

int main() {
    DequeApp::main();
    return 0;
}