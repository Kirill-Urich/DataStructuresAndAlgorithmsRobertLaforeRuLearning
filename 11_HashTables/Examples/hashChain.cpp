// hashChain.cpp
// Реализация хеш-таблицы с использованием метода цепочек

#include <iostream>
#include <experimental/random>
using namespace std;

class Link {
    private:
        int iData;
    public:
        Link* next;
        Link(int it) : iData(it) {}
        int getKey() {
            return iData;
        }
        void displayLink() {
            cout << iData << " ";
        }
};

class SortedList {
    private:
        Link* first;
    public:
        SortedList() {
            first = nullptr;
        }
        void insert(Link* theLink) {
            int key = theLink->getKey();
            Link* previous = nullptr;
            Link* current = first;
            while (current != nullptr && key > current->getKey()) {
                previous = current;
                current = current->next;
            }
            if (previous == nullptr)
                first = theLink;
            else
                previous->next = theLink;
            theLink->next = current;
        }
        void Delete(int key) {
            Link* previous = nullptr;
            Link* current = first;
            while (current != nullptr && key != current->getKey()) {
                previous = current;
                current = current->next;
            }
            if (previous == nullptr)
                first = first->next;
            else
                previous->next = current->next;
            delete current;
        }
        Link* find(int key) {
            Link* current = first;
            while (current != nullptr && current->getKey() <= key) {
                if (current->getKey() == key)
                    return current;
                current = current->next;
            }
            return nullptr;
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

class HashTable {
    private:
        SortedList** hashArray;
        int arraySize;
    public:
        HashTable(int size) {
            arraySize = size;
            hashArray = new SortedList*[arraySize];
            for (int j = 0; j < arraySize; j++)
                hashArray[j] = new SortedList();
        }
        void displayTable() {
            for (int j = 0; j < arraySize; j++) {
                cout << j << ". ";
                hashArray[j]->displayList();
            }
        }
        int hashFunc(int key) {
            return key % arraySize;
        }
        void insert(Link* theLink) {
            int key = theLink->getKey();
            int hashVal = hashFunc(key);
            hashArray[hashVal]->insert(theLink);
        }
        void Delete(int key) {
            int hashVal = hashFunc(key);
            hashArray[hashVal]->Delete(key);
        }
        Link* find(int key) {
            int hashVal = hashFunc(key);
            Link* theLink = hashArray[hashVal]->find(key);
            return theLink;
        }
};

class HashChainApp {
    public:
        static void main() {
            int aKey;
            Link* aDataItem;
            int size, n, keysPerCell = 100;

            cout << "Enter size of hash table: ";
            cin >> size;
            cout << "Enter initial number of items: ";
            cin >> n;

            HashTable* theHashTable = new HashTable(size);

            for (int j = 0; j < n; j++) {
                aKey = experimental::randint(0, 100);
                aDataItem = new Link(aKey);
                theHashTable->insert(aDataItem);
            }

            char choice;
            while (true) {
                cout << "Enter first letter of ";
                cout << "show, insert, delete or find: ";
                cin >> choice;

                switch(choice) {
                    case 's':
                        theHashTable->displayTable();
                        break;
                    case 'i':
                        cout << "Enter key value to insert: ";
                        cin >> aKey;
                        aDataItem = new Link(aKey);
                        theHashTable->insert(aDataItem);
                        break;
                    case 'd':
                        cout << "Enter key value to delete: ";
                        cin >> aKey;
                        theHashTable->Delete(aKey);
                        break;
                    case 'f':
                        cout << "Enter key value to find: ";
                        cin >> aKey;
                        aDataItem = theHashTable->find(aKey);
                        if (aDataItem != nullptr)
                            cout << "Found " << aKey << endl;
                        else
                            cout << "Could not find " << aKey << endl;
                        break;
                    default:
                        cout << "Invalid entry\n";
                }
            }
        }
};

int main() {
    HashChainApp::main();
    return 0;
}