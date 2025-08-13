// project_7_5.cpp

#include <iostream>
#include <experimental/random>
#include <string>
#include <chrono>
using namespace std;

class Link {
    public:
        string sData;
        Link* next;
    public:
        Link(string s) : sData(s), next(nullptr) {}
        void displayLink() {
            cout << sData << " ";
        }
};

class FirstLastList {
    private:
        Link* first;
        Link* last;
    public:
        FirstLastList() {
            first = nullptr;
            last = nullptr;
        }
        ~FirstLastList() {
            while (!isEmpty())
                deleteFirst();
        }
        bool isEmpty() {
            return first == nullptr;
        }
        void insertLast(string ss) {
            Link* newLink = new Link(ss);
            if (isEmpty())
                first = newLink;
            else
                last->next = newLink;
            last = newLink;
        }
        string deleteFirst() {
            if (isEmpty())
                return "";

            Link* temp = first;
            string data = temp->sData;
            first = first->next;
            if (first == nullptr)
                last = nullptr;
            
            delete temp;
            return data; 
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

class LinkQueue {
    private:
        FirstLastList* theList;
    public:
        LinkQueue() {
            theList = new FirstLastList();
        }
        ~LinkQueue() {
            delete theList;
        }
        bool isEmpty() {
            return theList->isEmpty();
        }
        void insert(string s) {
            theList->insertLast(s);
        }
        string remove() {
            return theList->deleteFirst();
        }
        void displayQueue() {
            cout << "Queue (front-->rear): ";
            theList->displayList();
        }
};

class arrBitWise {
    private:
        string* arr;
        int nElems;
        int maxSize;
    public:
        arrBitWise(int max) {
            arr = new string[max];
            nElems = 0;
            maxSize = max;
        }
        ~arrBitWise() {
            delete[] arr;
        }
        void insert(long p) {
            if (nElems < maxSize)
                arr[nElems++] = to_string(p);
        }
        int size() {
            return nElems;
        }
        void display() {
            for (int i = 0; i < nElems; i++)
                cout << atol(arr[i].c_str()) << " ";
            cout << endl;
        }
        void bitWiseSort() {
            if (nElems == 0)
                return;

            int maxLength = 0;
            // поиск максимальной длины числа
            for (int i = 0; i < nElems; i++) {
                int tempLength = arr[i].length();
                if (tempLength > maxLength)
                    maxLength = tempLength;
            }

            // заполнение числа недостающими ведущими нулями
            for (int i = 0; i < nElems; i++) {
                int tempLength = arr[i].length();
                if (tempLength < maxLength) {
                    arr[i] = string(maxLength - tempLength, '0') + arr[i];
                }
            }
            // инициализация очередей
            LinkQueue** newLinkQueue = new LinkQueue*[10];
            for (int i = 0; i < 10; i++)
                newLinkQueue[i] = new LinkQueue;

            // поразрядная сортировка
            for (int digitPos = maxLength - 1; digitPos >= 0; digitPos--) {
                // распределение чисел по очередям
                for (int j = 0; j < nElems; j++) {
                    char currentChar = arr[j][digitPos];
                    if (currentChar < '0' || currentChar > '9')
                        continue;
                    int digit = currentChar - '0';
                    newLinkQueue[digit]->insert(arr[j]);
                }
                // сбор чисел из очередей обратно в массив
                int index = 0;
                for (int j = 0; j < 10; j++) {
                    while (!newLinkQueue[j]->isEmpty()) {
                        string numStr = newLinkQueue[j]->remove();
                        arr[index++] = numStr;
                    }
                }
            }
            
            for (int i = 0; i < 10; i++)
                delete newLinkQueue[i];
            delete[] newLinkQueue;
        }
};

class arrBitWiseApp {
    public:
        static void main() {
            int maxSize = 10'000'000;
            arrBitWise* newArr = new arrBitWise(maxSize);
            for (int i = 0; i < maxSize; i++)
                newArr->insert(experimental::randint(0l, 2'147'483'648));

            // newArr->display();
            auto start = chrono::high_resolution_clock::now();
            newArr->bitWiseSort();
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            cout << "Время выполнения " << duration.count() << " микросекунд" << endl;
            // newArr->display();
        }
};

int main() {
    arrBitWiseApp::main();
    return 0;
}