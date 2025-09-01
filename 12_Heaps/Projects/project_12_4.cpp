// project_12_4.cpp
// Приоритетная очередь на базе пирамиды = двоичного дерева

#include <iostream>
#include <experimental/random>
using namespace std;

class Node {
    public:
        int iData;
        Node* leftChild = nullptr;
        Node* rightChild = nullptr;
    public:
        void displayNode() {
            cout << iData << " ";
        }
        int getKey() {
            return iData;
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
                    else {
                        current = current->rightChild;
                        if (current == nullptr) {
                            parent->rightChild = newNode;
                            return;
                        }
                    }
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
        Node* removeMax() {
            Node* current = root;
            Node* parent = current;
            while (current->rightChild != nullptr) {
                parent = current;
                current = current->rightChild;
            }
            if (current == root)
                root = current->leftChild;
            else
                parent->rightChild = current->leftChild;
            return current;
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

class PriorityQ {
    private:
        int maxSize;
        Tree* queArray;
        int nItems;
    public:
        PriorityQ(int s) {
            maxSize = s;
            queArray = new Tree();
            nItems = 0;
        }
        void insert(int item) {
            queArray->insert(item);
            nItems++;
        }
        int remove() {
            Node* temp = queArray->removeMax();
            nItems--;
            return temp->getKey();
        }
        // int peekMin() {
        //     return queArray[--nItems];
        // }
        bool isEmpty() {
            return nItems == 0;
        }
        bool isFull() {
            return nItems == maxSize;
        }
        void displayQueue() {
            queArray->displayTree();
        }
};

class PriorityQApp {
    public:
        static void main() {
            int size = experimental::randint(5, 10);
            PriorityQ* thePQ = new PriorityQ(size);
            for (int i = 0; i < size; i++) {
                int num = experimental::randint(0, 100);
                thePQ->insert(num);
            }

            while (!thePQ->isEmpty()) {
                thePQ->displayQueue();
                int item = thePQ->remove();
                cout << item << " ";
            }
            cout << endl;
        }
};

int main() {
    PriorityQApp::main();
    return 0;
}