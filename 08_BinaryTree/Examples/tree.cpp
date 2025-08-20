// tree.cpp
// Работа с двоичным деревом

#include <iostream>
using namespace std;

class Node {
    public:
        int iData;
        double dData;
        Node* leftChild = nullptr;
        Node* rightChild = nullptr;
    public:
        void displayNode() {
            cout << "{" << iData << ", " << dData << "} ";
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
        void insert(int id, double dd) {
            Node* newNode = new Node();
            newNode->iData = id;
            newNode->dData = dd;
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
            while (current != nullptr && current->iData != key) {
                parent = current;
                if (key < current->iData) {
                    isLeftChild = true;
                    current = current->leftChild;
                } else {
                    isLeftChild = false;
                    current = current->rightChild;
                }
            }

            if (current == nullptr)
                return false;

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
                delete current;
            } else if (current->leftChild == nullptr) {
                if (current == root)
                    root = current->rightChild;
                else if (isLeftChild)
                    parent->leftChild = current->rightChild;
                else
                    parent->rightChild = current->rightChild;
                delete current;
            } else {
                Node* successor = getSuccessor(current);

                if (current == root) 
                    root = successor;
                else if (isLeftChild)
                    parent->leftChild = successor;
                else 
                    parent->rightChild = successor;
                delete current;
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

class TreeApp {
    public:
        static void main() {
            int value;
            Tree* theTree = new Tree();
            theTree->insert(50, 1.5);
            theTree->insert(25, 1.2);
            theTree->insert(75, 1.7);        
            theTree->insert(12, 1.5);
            theTree->insert(37, 1.2);
            theTree->insert(43, 1.7);
            theTree->insert(30, 1.5);
            theTree->insert(33, 1.2);
            theTree->insert(87, 1.7);
            theTree->insert(93, 1.5);
            theTree->insert(97, 1.5);

            while (true) {
                cout << "Enter first letter of show, ";
                cout << "insert, find, delete or traverse: ";
                char choice;
                cin >> choice;
                switch(choice) {
                    case 's':
                        theTree->displayTree();
                        break;
                    case 'i':
                        cout << "Enter value to insert: ";
                        cin >> value;
                        theTree->insert(value, value + 0.9);
                        break;
                    case 'f': {
                            cout << "Enter value to find: ";
                            cin >> value;
                            Node* found = theTree->find(value);
                            if (found != nullptr) {
                                cout << "Found: ";
                                found->displayNode();
                                cout << "\n";
                            } else
                                cout << "This not is not exist.";
                            break;
                        }
                    case 'd': {
                        cout << "Enter value to delete: ";
                        cin >> value;
                        bool Deleted = theTree->Delete(value);
                        if (Deleted)
                            cout << value << " is deleted. ";
                        else
                            cout << "The " << value << " is not exist in the Tree";
                        cout << "\n";
                        }
                        break;
                    case 't':
                        cout << "Enter 1, 2 or 3 to traverse the Tree \
                                 \nto preOrder, inOrder or postOrder accordingly";
                        cin >> value;
                        theTree->traverse(value);
                        break;
                    default:
                        cout << "Try again\n";
                        continue;
                }
            }
        }
};

int main() {
    TreeApp::main();
    return 0;
}