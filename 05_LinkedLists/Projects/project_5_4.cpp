// project_5_4.cpp

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
        Link* remove() {
            int count = 0;
            Link* previous = current;
            while (count != nItems) {
                previous = current;
                current = current->next;
                ++count;
            }
            previous->next = current->next;
            current = previous;
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
};

class StackX {
    private:
        int maxSize;
        CycleList* stackList;
        int top;
    public:
        StackX(int s) {
            maxSize = s;
            stackList = new CycleList();
            top = 0;
        }
        void push(long j) {
            stackList->insert(j);
            ++top;
        }
        long pop() {
            --top;
            return stackList->remove()->dData;
        }
        // long peek() {
        // }
        bool isEmpty() {
            return stackList->isEmpty();
        }
        bool isFull() {
            return top == maxSize;
        }
        void displayStack() {
            stackList->displayList();
        }
};

class StackApp {
    public:
        static void main() {
            StackX* theStack = new StackX(10);
            theStack->push(20);
            theStack->push(40);
            theStack->push(60);
            theStack->push(80);

            theStack->displayStack();

            while (!theStack->isEmpty()) {
                long value = theStack->pop();
                cout << value << " ";
            }
            cout << endl;
        }
};

int main() {
    StackApp::main();
    return 0;
}