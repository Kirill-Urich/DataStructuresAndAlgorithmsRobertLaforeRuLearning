// hashDouble.cpp
// Реализация хеш-таблицы с двойным хешированием

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
        int arraySize;
        DataItem* nonItem;
    public:
        HashTable(int size) {
            arraySize = size;
            hashArray = new DataItem*[arraySize];
            for (int i = 0; i < arraySize; i++)
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
        int hashFunc1(int key) {
            return key % arraySize;
        }
        int hashFunc2(int key) {
            return 5 - key % 5;
        }
        void insert(int key, DataItem* item) {
            int hashVal = hashFunc1(key);
            int stepSize = hashFunc2(key);
            while (hashArray[hashVal] != nullptr && hashArray[hashVal]->getKey() != -1) {
                hashVal += stepSize;
                hashVal %= arraySize;
            }
            hashArray[hashVal] = item;
        }
        DataItem* Delete(int key) {
            int hashVal = hashFunc1(key);
            int stepSize = hashFunc2(key);

            while (hashArray[hashVal] != nullptr) {
                if (hashArray[hashVal]->getKey() == key) {
                    DataItem* temp = hashArray[hashVal];
                    hashArray[hashVal] = nonItem;
                    return temp;
                }
                hashVal += stepSize;
                hashVal %= arraySize;
            }
            return nullptr;
        }
        DataItem* find(int key) {
            int hashVal = hashFunc1(key);
            int stepSize = hashFunc2(key);

            while (hashArray[hashVal] != nullptr) {
                if (hashArray[hashVal]->getKey() == key)
                    return hashArray[hashVal];
                hashVal += stepSize;
                hashVal %= arraySize;
            }
            return nullptr;
        }
};

class HashDoubleApp {
    public:
        static void main() {
            DataItem* aDataItem;
            int aKey, size, n, keysPerCell;
            cout << "Enter size of hash table: ";
            cin >> size;
            cout << "Enter initial number of items: ";
            cin >> n;
            keysPerCell = 9;

            HashTable* theHashTable = new HashTable(size);
            for (int j = 0; j < n; j++) {
                aKey = experimental::randint(0, 1000);
                aDataItem = new DataItem(aKey);
                theHashTable->insert(aKey, aDataItem);
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
                        theHashTable->insert(aKey, aDataItem);
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
    HashDoubleApp::main();
    return 0;
}