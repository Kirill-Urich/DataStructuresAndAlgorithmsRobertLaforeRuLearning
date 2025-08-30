// hashChain.cpp
// Реализация хеш-таблицы с использованием метода цепочек

#include <iostream>
#include <experimental/random>
using namespace std;

class Node {
    public:
        int iData;
        Node* leftChild = nullptr;
        Node* rightChild = nullptr;
    public:
        Node() = default;
        Node(int it) : iData(it) {}
        int getKey() {
            return iData;
        }
        void displayNode() {
            cout << iData << " ";
        }
};

class Stack {
    private:
        int maxSize;
        Node** nodeArray;
        int top;
    public:
        Stack() {
            maxSize = 128;
            nodeArray = new Node*[maxSize];
            top = -1;
        }
        Stack(int s) {
            maxSize = s;
            nodeArray = new Node*[maxSize];
            top = -1;
        }
        void push(Node* j) {
            nodeArray[++top] = j;
        }
        Node* pop() {
            return nodeArray[top--];
        }
        Node* peek() {
            return nodeArray[top];
        }
        bool isEmpty() {
            return top == -1;
        }
        bool isFull() {
            return (top == maxSize - 1);
        }
};

class Tree {
    private:
        Node* root;
    private:
        Node* getSuccessor(Node* delNode) {
            Node* successorParent = delNode;
            Node* successor = delNode;
            Node* current = delNode->rightChild;
            while (current != nullptr) {
                successorParent = successor;
                successor = current;
                current = current->leftChild;
            }
            if (successor != delNode->rightChild) {
                successorParent->leftChild = successor->rightChild;
                successor->rightChild = delNode->rightChild;
            }
            return successor;
        }
        void preOrder(Node* localRoot) {
            if (localRoot != nullptr) {
                cout << localRoot->iData << " ";
                preOrder(localRoot->leftChild);
                preOrder(localRoot->rightChild);
            }
        }
        void inOrder(Node* localRoot) {
            if (localRoot != nullptr) {
                inOrder(localRoot->leftChild);
                cout << localRoot->iData << " ";
                inOrder(localRoot->rightChild);
            }
        }
        void postOrder(Node* localRoot) {
            if (localRoot != nullptr) {
                postOrder(localRoot->leftChild);
                postOrder(localRoot->rightChild);
                cout << localRoot->iData << " ";
            }
        }
    public:
        Tree() : root(nullptr) {}
        Node* find(int key) {
            Node* current = root;
            while (current != nullptr && current->iData != key) {
                if (key < current->iData)
                    current = current->leftChild;
                else
                    current = current->rightChild;
            }
            return current;
        }
        void insert(int id) {
            Node* newNode = new Node();
            newNode->iData = id;
            if (root == nullptr)
                root = newNode;
            else {
                Node* current = root;
                Node* parent;
                while (true) {
                    parent = current;
                    if (id < current->iData) {
                        current = current->leftChild;
                        if (current == nullptr) {
                            parent->leftChild = newNode;
                            return;
                        }
                    }
                    else if (id > current->iData){
                        current = current->rightChild;
                        if (current == nullptr) {
                            parent->rightChild = newNode;
                            return;
                        }
                    } else
                        return;
                }
            }
        }
        bool Delete(int key) {
            Node* current = root;
            Node* parent = root;
            bool isLeftChild = true;
            while (current->iData != key) {
                parent = current;
                if (key < current->iData) {
                    isLeftChild = true;
                    current = current->leftChild;
                } else {
                    isLeftChild = false;
                    current = current->rightChild;
                }
                if (current == nullptr)
                    return false;
            }

            if (current->leftChild == nullptr && current->rightChild == nullptr) {
                if (current == root)
                    root = nullptr;
                else if (isLeftChild)
                    parent->leftChild = nullptr;
                else
                    parent->rightChild = nullptr;
            } else if (current->rightChild == nullptr) {
                if (current == root)
                    root = current->leftChild;
                else if (isLeftChild)
                    parent->leftChild = current->leftChild;
                else
                    parent->rightChild = current->leftChild;
            } else if (current->leftChild == nullptr) {
                if (current == root)
                    root = current->rightChild;
                else if (isLeftChild)
                    parent->leftChild = current->rightChild;
                else
                    parent->rightChild = current->rightChild;
            } else {
                Node* successor = getSuccessor(current);
                successor->leftChild = current->leftChild;
                if (current == root) 
                    root = successor;
                else if (isLeftChild)
                    parent->leftChild = successor;
                else 
                    parent->rightChild = successor;
            }
            return true;
        }
        void traverse(int traverseType) {
            switch(traverseType) {
                case 1:
                    cout << "\nPreorder traversal: ";
                    preOrder(root);
                    break;
                case 2:
                    cout << "\nInorder traversal: ";
                    inOrder(root);
                    break;
                case 3:
                    cout << "\nPostorder traversal: ";
                    postOrder(root);
                    break;
            }
        }
        void displayTree() {
            Stack* globalStack = new Stack();
            globalStack->push(root);
            int nBlanks = 32;
            bool isRowEmpty = false;
            cout << "............................................" << endl;
            while (isRowEmpty == false) {
                Stack* localStack = new Stack();
                isRowEmpty = true;
                for (int j = 0; j < nBlanks; j++)
                    cout << ' ';
                
                while (globalStack->isEmpty() == false) {
                    Node* temp = reinterpret_cast<Node*>(globalStack->pop());
                    if (temp != nullptr) {
                        cout << temp->iData;
                        localStack->push(temp->leftChild);
                        localStack->push(temp->rightChild);
                        if (temp->leftChild != nullptr || temp->rightChild != nullptr)
                            isRowEmpty = false;
                    } else {
                        cout << "--";
                        localStack->push(nullptr);
                        localStack->push(nullptr);
                    }
                    for (int j = 0; j < nBlanks * 2 - 2; j++)
                        cout << ' ';
                }
                cout << endl;
                nBlanks /= 2;
                while (localStack->isEmpty() == false)
                    globalStack->push(localStack->pop());
            }
            cout << "............................................" << endl;
        }
};

class HashTable {
    private:
        Tree** hashArray;
        int arraySize;
    public:
        HashTable(int size) {
            arraySize = size;
            hashArray = new Tree*[arraySize];
            for (int j = 0; j < arraySize; j++)
                hashArray[j] = new Tree();
        }
        void displayTable() {
            for (int j = 0; j < arraySize; j++) {
                cout << j << ". ";
                hashArray[j]->displayTree();
            }
        }
        int hashFunc(int key) {
            return key % arraySize;
        }
        void insert(Node* theNode) {
            int key = theNode->getKey();
            int hashVal = hashFunc(key);
            hashArray[hashVal]->insert(key);
        }
        void Delete(int key) {
            int hashVal = hashFunc(key);
            hashArray[hashVal]->Delete(key);
        }
        Node* find(int key) {
            int hashVal = hashFunc(key);
            Node* theNode = hashArray[hashVal]->find(key);
            return theNode;
        }
};

class HashChainApp {
    public:
        static void main() {
            int aKey;
            Node* aDataItem;
            int size, n, keysPerCell = 100;

            cout << "Enter size of hash table: ";
            cin >> size;
            cout << "Enter initial number of items: ";
            cin >> n;

            HashTable* theHashTable = new HashTable(size);

            for (int j = 0; j < n; j++) {
                aKey = experimental::randint(0, 100);
                aDataItem = new Node(aKey);
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
                        aDataItem = new Node(aKey);
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