// project_11_2.cpp
// Хеширование строк открытой адресацией линейным пробированием

#include <iostream>
#include <experimental/random>
#include <string>
using namespace std;

class DataItem {
    private:
        string sData;
    public:
        DataItem() = default;
        DataItem(string s) : sData(s) {}
        string getKey() {
            return sData;
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
            nonItem = new DataItem("-");
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
        int hashFunc(string key) {
            int hashVal = 0;
            int length = key.length();
            for (int j = 0; j < length; j++) {
                int letter = key[j] - 96;
                hashVal = (hashVal * 27 + letter) % arraySize;
            }
            return hashVal;
        }
        void insert(DataItem* item) {
            string key = item->getKey();
            int hashVal = hashFunc(key);

            while (hashArray[hashVal] != nullptr && hashArray[hashVal] != nonItem) {
                ++hashVal;
                hashVal %= arraySize;
            }
            hashArray[hashVal] = item;
        }
        DataItem* Delete(string key) {
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
        DataItem* find(string key) {
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

string makeWord() {
    string word;
    int size = experimental::randint(1, 16);
    for (int i = 0; i < size; i++) {
        char ch = experimental::randint(97, 122);
        word += ch;
    }
    return word;
}

class HashTableApp {
    public:
        static void main() {
            DataItem* aDataItem;
            int size, n;
            string aKey;
            cout << "Enter size of hash table: ";
            cin >> size;
            cout << "Enter initial number of items: ";
            cin >> n;

            HashTable* theHashTable = new HashTable(size);
            for (int j = 0; j < n; j++) {
                aKey = makeWord();
                cout << aKey << " ";
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