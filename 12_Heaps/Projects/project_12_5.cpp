// project_12_5.cpp

#include <iostream>
using namespace std;

class Node {
    public:
        int iData;
        Node* parent;
        Node* leftChild;
        Node* rightChild;
    public:
        Node() = default;
        Node(int key) : iData(key) {
            parent = nullptr;
            leftChild = nullptr;
            rightChild = nullptr;
        }
        int getKey() {
            return iData;
        }
        void setKey(int id) {
            iData = id;
        }
        void displayNode() {
            cout << iData << " ";
        }
        bool operator!=(const Node& newNode) {
            if (iData != newNode.iData &&
                parent != newNode.parent &&
                leftChild != newNode.leftChild &&
                rightChild != newNode.rightChild)
                return true;
            return false;
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
        string binPath(int index) {
            if (index == 0)
                return "";

            string path;
            int current = index + 1;
            while (current > 1) {
                path = (current % 2 ? '1' : '0') + path;
                current /= 2;
            }
            return path;
        }
    public:
        Tree() : root(nullptr) {}
        bool addNodeAt(int index, int key) {
            // cout << "Adding node at index " << index << " with key " << key << endl;
            if (index == 0) {
                if (root != nullptr) {
                    // cout << "ERROR: Root already exists!" << endl;
                    return false;
                }
                root = new Node(key);
                // cout << "Created root node" << endl;
                return true;
            }
            
            int parentIndex = (index - 1) / 2;
            // cout << "Parent index: " << parentIndex << endl;

            Node* parent = getNode(parentIndex);
            if (!parent) {
                // cout << "ERROR: Parent not found at index " << parentIndex << endl;
                return false;
            }
            Node* newNode = new Node(key);
            if (index % 2 == 1) {
                parent->leftChild = newNode;
                // cout << "Added as left child" << endl;
            }
            else {
                parent->rightChild = newNode;
                // cout << "Added as right child" << endl;
            }
            newNode->parent = parent;
            return true;
        }
        Node* getNode(int index) {
            // cout << "getNode(" << index << ")" << endl;
            if (index < 0)
                return nullptr;
            if (index == 0)
                return root;

            string path = binPath(index);
            // cout << "Path for " << index << ": " << path << endl;
            Node* current = root;

            for (char c : path) {
                if (current == nullptr) {
                    // cout << "Nullptr at path step " << c << endl;
                    return nullptr;
                }
                if (c == '0')
                    current = current->leftChild;
                else if (c == '1')
                    current = current->rightChild;
                else {
                    // cout << "ERROR: Invalid path character '" << c << "'" << endl;
                    return nullptr;
                }
            }
            return current;
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

class Heap {
    private:
        Tree* heapTree;
        int currentSize;
    private:
        // Node& operator[](int index) {
        //     return heapTree[index];
        // } 
        void trickleUp(int index) {
            if (index == 0)
                return;

            Node* bottom = heapTree->getNode(index);
            int currentIndex = index;

            while (currentIndex > 0) {
                int parentIndex = (currentIndex - 1) / 2;
                Node* parent = heapTree->getNode(parentIndex);

                if (parent == nullptr || bottom == nullptr) {
                    // cout << "ERROR: Null node in trickeUp" << endl;
                    break;
                }

                if (parent->getKey() >= bottom->getKey())
                    break;

                swapNodesValues(heapTree->getNode(currentIndex), heapTree->getNode(parentIndex));
                // swapNodesValues(bottom, parent);
                currentIndex = parentIndex;
                bottom = parent;
            }
        }
        void trickleDown(int index) {
            Node* top = heapTree->getNode(index);
            int currentIndex = index;

            while (currentIndex < currentSize / 2) {
                int leftChildIndex  = 2 * currentIndex + 1;
                int rightChildIndex = 2 * currentIndex + 2;
                int largerChildIndex = leftChildIndex;

                if (rightChildIndex < currentSize) {
                    Node* leftChild = heapTree->getNode(leftChildIndex);
                    Node* rightChild = heapTree->getNode(rightChildIndex);
                    if (rightChild->getKey() > leftChild->getKey())
                        largerChildIndex = rightChildIndex;
                }

                Node* largerChild = heapTree->getNode(largerChildIndex);
                
                if (top->getKey() >= largerChild->getKey())
                    break;

                swapNodesValues(top, largerChild);
                currentIndex = largerChildIndex;
                top = largerChild;
            }
        }
        void swapNodesValues(Node* first, Node* second) {
            int tempKey = first->getKey();
            first->setKey(second->getKey());
            second->setKey(tempKey);
        }
    public:
        Heap() {
            currentSize = 0;
            heapTree = new Tree();
        }
        bool isEmpty() {
            return currentSize == 0;
        }
        bool insert(int key) {
            if (!heapTree->addNodeAt(currentSize, key))
                return false;
            trickleUp(currentSize);
            currentSize++;
            return true;
        }
        Node* remove() {
            if (currentSize == 0)
                return nullptr;
            Node* rootNode = heapTree->getNode(0);
            Node* lastNode = heapTree->getNode(currentSize - 1);

            rootNode->setKey(lastNode->getKey());
            currentSize--;
            trickleDown(0);
            return rootNode;
        }
        bool change(int index, int newValue) {
            if (index < 0 || index >= currentSize)
                return false;
            int oldValue = heapTree->getNode(index)->getKey();
            heapTree->getNode(index)->setKey(newValue);

            if (oldValue < newValue)
                trickleUp(index);
            else
                trickleDown(index);
            return true;
        }
        void displayHeap() {
            cout << "heapArray: ";
            for (int m = 0; m < currentSize; m++) {
                if (heapTree->getNode(m) != nullptr)
                    cout << heapTree->getNode(m)->getKey() << " ";
                else
                    cout << "-- ";
            }
            cout << endl;

            int nBlanks = 32;
            int itemsPerRow = 1;
            int column = 0;
            int j = 0;
            string dots = "...............................";
            cout << dots << dots << endl;

            while (currentSize > 0) {
                if (column == 0)
                    for (int k = 0; k < nBlanks; k++)
                        cout << ' ';
                
                cout << heapTree->getNode(j)->getKey();
                if (++j == currentSize)
                    break;
                
                if (++column == itemsPerRow) {
                    nBlanks /= 2;
                    itemsPerRow *= 2;
                    column = 0;
                    cout << endl;
                } else 
                    for (int k = 0; k < nBlanks * 2 - 2; k++)
                        cout << ' ';
            }
            cout << '\n' << dots << dots << endl;
        }
};

class HeapApp {
    public:
        static void main() {
            int value, value2;
            Heap* theHeap = new Heap();
            bool success;
            cout << "Inserting 70..." << endl; 
            theHeap->insert(70);
            cout << "Inserting 40..." << endl;
            theHeap->insert(40);            
            theHeap->insert(50);
            theHeap->insert(20);
            theHeap->insert(60);
            theHeap->insert(100);
            theHeap->insert(80);
            theHeap->insert(30);
            theHeap->insert(10);
            theHeap->insert(90);

            char choice;
            while (true) {
                cout << "Enter first letter of ";
                cout << "show, insert, remove, change: ";
                cin >> choice;

                switch(choice) {
                    case 's':
                        theHeap->displayHeap();
                        break;
                    case 'i':
                        cout << "Enter value to insert: ";
                        cin >> value;
                        success = theHeap->insert(value);
                        if (!success)
                            cout << "Can't insert: heap full" << endl;
                        break;
                    case 'r':
                        if (!theHeap->isEmpty())
                            theHeap->remove();
                        else
                            cout << "Can't remove: heap empty" << endl;
                        break;
                    case 'c':
                        cout << "Enter current index of item: ";
                        cin >> value;
                        cout << "Enter new key: ";
                        cin >> value2;
                        success = theHeap->change(value, value2);
                        if (!success)
                            cout << "Invalid index" << endl;
                        break;
                    default:
                        cout << "Invalid entry\n" << endl;
                }
            }
        }
};

int main() {
    HeapApp::main();
    return 0;
}