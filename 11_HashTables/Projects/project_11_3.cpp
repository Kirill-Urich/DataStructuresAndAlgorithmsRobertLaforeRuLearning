// project_11_3.cpp

#include <iostream>
#include <experimental/random>
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
            nonItem = new DataItem("(0)");
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
        int hashFunc(string tempKey) {
            int size = tempKey.size();
            int length = 0;
            string key;
            for (int i = 0; i < size; i++) {
                if (tempKey[i] >= '0' && tempKey[i] <= '9') {
                    key += tempKey[i];
                    length++;
                }
            }

            int dec = 1;
            int tempSize = -1;
            while (dec <= arraySize) {
                dec *= 10;
                ++tempSize;
            }
            dec /= 10;

            int hashVal = 0;
            int count = 0;
            int tempDec = dec;
            for (int i = 0; i < length; i++) {
                tempDec /= 10;
                hashVal += (key[i] - '0') * tempDec;
                ++count;
                if (count == tempSize) {
                    if (i + count < length)
                        tempDec = dec;
                    else
                        tempDec = dec / 10;
                    count = 0;
                }
            }
            
            return hashVal % arraySize;
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

string makeKey() {
    string word;
    int size = 11;
    char ch;
    for (int i = 0; i < size; i++) {
        if (i == 3 || i == 6)
            ch = '-';
        else
            ch = experimental::randint(48, 57);
        word += ch;
    }
    return word;
}

class HashTableApp {
    public:
        static void main() {
            int size, n;
            DataItem* aDataItem;
            string aKey;
            cout << "Enter size of hash table: ";
            cin >> size;
            cout << "Enter initial number of items: ";
            cin >> n;

            HashTable* theHashTable = new HashTable(size);
            for (int j = 0; j < n; j++) {
                aKey = makeKey();
                aDataItem = new DataItem(aKey);
                theHashTable->insert(aDataItem);
                theHashTable->displayTable();
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