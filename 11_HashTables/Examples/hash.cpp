// hash.cpp
// Реализация хеш-таблицы с линейным пробированием

#include <iostream>
#include <experimental/random>
using namespace std;

class DataItem {
    private:
        int iData;
    public:
        DataItem() = default;
        DataItem(int ii) : iData(ii) {}
        int getKey() {
            return iData;
        }
};

class HashTable {
    private:
        DataItem** hashArray;
        DataItem* nonItem;
        int arraySize;
    public:
        HashTable(int size) {
            arraySize = size;
            hashArray = new DataItem*[arraySize];
            for (int i = 0; i < size; i++)
                hashArray[i] = nullptr;
            nonItem = new DataItem(-1);
        }
        void displayTable() {
            cout << "Table: ";
            for (int j = 0; j < arraySize; j++) {
                if (hashArray[j] != nullptr)
                    cout << hashArray[j]->getKey() << " ";
                else
                    cout << "** ";
            }
            cout << endl;
        }
        int hashFunc(int key) {
            return key % arraySize;
        }
        void insert(DataItem* item) {
            int key = item->getKey();
            int hashVal = hashFunc(key);

            while (hashArray[hashVal] != nullptr && hashArray[hashVal]->getKey() != -1) {
                ++hashVal;
                hashVal %= arraySize;
            }
            hashArray[hashVal] = item;
        }
        DataItem* Delete(int key) {
            int hashVal = hashFunc(key);
            while (hashArray[hashVal] != nullptr) {
                if (hashArray[hashVal]->getKey() == key) {
                    DataItem* temp = hashArray[hashVal];
                    hashArray[hashVal] = nonItem;
                    return temp;
                }
                ++hashVal;
                hashVal %= arraySize;
            }
            return nullptr;
        }
        DataItem* find(int key) {
            int hashVal = hashFunc(key);
            while (hashArray[hashVal] != nullptr) {
                if (hashArray[hashVal]->getKey() == key)
                    return hashArray[hashVal];
                ++hashVal;
                hashVal %= arraySize;
            }
            return nullptr;
        }
};

class HashTableApp {
    public:
        static void main() {
            DataItem* aDataItem;
            int aKey, size, n, keysPerCell;
            cout << "Enter size of hash table: ";
            cin >> size;
            cout << "Enter initial number of items: ";
            cin >> n;
            keysPerCell = 10;

            HashTable* theHashTable = new HashTable(size);
            for (int j = 0; j < n; j++) {
                aKey = experimental::randint(0, 100) * keysPerCell * size;
                aDataItem = new DataItem(aKey);
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
                        aDataItem = new DataItem(aKey);
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
    HashTableApp::main();
    return 0;
}