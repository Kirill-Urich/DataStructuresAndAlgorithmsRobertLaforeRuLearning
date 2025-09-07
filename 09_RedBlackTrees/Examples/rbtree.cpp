// rbtree.cpp
// Работа с красно-чёрным деревом

#include <iostream>
using namespace std;

enum Color { red, black };

class Node {
    public:
        int iData;
        Node* leftChild;
        Node* rightChild;
        Node* parent;
        Color color;
    public:
        Node() = default;
        Node(int id, Color c, Node* lc, Node* rc) {
            iData = id;
            color = c;
            leftChild = lc;
            rightChild = rc;
        }
        ~Node() {
            if (leftChild != nullptr)
                delete leftChild;
            if (rightChild != nullptr)
                delete rightChild;
        }
        void displayNode() {
            cout << iData << ' ';
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

class RBTree {
    private:
        Node* root;
    private:
        void RoL(Node* theNode) {
            if (theNode->rightChild == nullptr)
                return;
            
            Node* successor = theNode->rightChild;
            theNode->rightChild = successor->leftChild;
            if (successor->leftChild != nullptr)
                successor->leftChild->parent = theNode;
            successor->leftChild = theNode;
            successor->parent = theNode->parent;
            theNode->parent = successor;

            if (root == theNode) {
                root = successor;
                return;
            }
            if (successor->parent->leftChild == theNode)
                successor->parent->leftChild = successor;
            else
                successor->parent->rightChild = successor;
        }
        void RoR(Node* theNode) {
            if (theNode->leftChild == nullptr)
                return;
            
            Node* successor = theNode->leftChild;
            theNode->leftChild = successor->rightChild;
            if (successor->rightChild != nullptr)
                successor->rightChild->parent = theNode;
            successor->rightChild = theNode;
            successor->parent = theNode->parent;
            theNode->parent = successor;

            if (root == theNode) {
                root = successor;
                return;
            }
            if (successor->parent->leftChild == theNode)
                successor->parent->leftChild = successor;
            else
                successor->parent->rightChild = successor;
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
        RBTree() : root(nullptr) {}
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
            Node* newNode = new Node(id, red, nullptr, nullptr);

            if (root == nullptr) {
                root = newNode;
                newNode->parent = nullptr;
            }
            
            else {
                Node* current = root;
                Node* parent = nullptr;
                while (current != nullptr) {
                    parent = current;
                    if (current->iData < id)
                        current = current->rightChild;
                    else
                        current = current->leftChild;
                }
                newNode->parent = parent;
                if (parent->iData < id)
                    parent->rightChild = newNode;
                else
                    parent->leftChild = newNode;
            }

            balanceAfterInsert(newNode);
        }
        void balanceAfterInsert(Node* node) {
            if (node == root) {
                node->color = black;
                return;
            }
            Node* parent = node->parent;
            Node* grandparent = nullptr;
            Node* uncle = nullptr;
            while (parent->color == red) {
                parent = node->parent;
                grandparent = parent->parent;
                if (grandparent->leftChild == parent)
                    uncle = grandparent->rightChild;
                else
                    uncle = grandparent->leftChild;

                if (parent == grandparent->leftChild) {
                    if (uncle != nullptr && uncle->color == red) {
                        parent->color = black;
                        uncle->color = black;
                        grandparent->color = red;
                        node = grandparent;
                    } else {
                        if (node == parent->rightChild) {
                            node = node->parent;
                            RoL(node);
                        }
                        parent->color = black;
                        grandparent->color = red;
                        RoR(grandparent);
                    }
                } else {
                    if (uncle != nullptr && uncle->color == red) {
                        parent->color = black;
                        uncle->color = black;
                        grandparent->color = red;
                        node = grandparent;
                    } else {
                        if (node == parent->leftChild) {
                            node = node->parent;
                            RoR(node);
                        }
                        parent->color = black;
                        grandparent->color = red;
                        RoL(grandparent);
                    }
                }
            }
            root->color = black;
        }
        bool Delete(int key) {
            Node* current = root;
            while (current->iData != key) {
                if (current->iData < key)
                    current = current->rightChild;
                else
                    current = current->leftChild;
            }

            if (current == nullptr)
                return false;

            if (current->leftChild == nullptr && current->rightChild == nullptr) {
                if (current == root)
                    root = nullptr;
                else
                    if (current->parent->leftChild == current)
                        current->parent->leftChild = nullptr;
                    else
                        current->parent->rightChild = nullptr;
                    delete current;
                    return true;
            }

            Node* replace = nullptr;
            Node* balance = nullptr;

            if (current->leftChild == nullptr || current->rightChild == nullptr) {
                replace = current;
                Node* child = (replace->leftChild != nullptr) ? replace->leftChild : replace->rightChild;

                if (replace == root) {
                    root = child;
                    if (child != nullptr)
                        child->parent = nullptr;
                } else {
                    if (replace->parent->leftChild == replace)
                        replace->parent->leftChild = child;
                    else
                        replace->parent->rightChild = child;

                    if (child != nullptr)
                        child->parent = replace->parent;
                }
                balance = child;
            } 
            else {
                replace = current->rightChild;
                while (replace->leftChild != nullptr)
                    replace = replace->leftChild;

                if (replace->rightChild != nullptr)
                    replace->rightChild->parent = replace->parent;

                if (replace == root) {
                    root = replace->rightChild;
                    if (root != nullptr)
                        root->parent = nullptr;
                } else {
                    if (replace->parent->leftChild == replace)
                        replace->parent->leftChild = replace->rightChild;
                    else
                        replace->parent->rightChild = replace->rightChild;

                    if (replace->rightChild != nullptr)
                        replace->rightChild->parent = replace->parent;
                }

                balance = replace->rightChild;

                current->iData = replace->iData;
                current->color = replace->color;
            }

            if (replace != nullptr && replace->color == black && balance != nullptr)
                fixDeleting(balance);

            if (replace != current)
                delete replace;
            
            return true;
        }

        void fixDeleting(Node* node) {
            while (node->color == black && node != root) {
                Node* parent = node->parent;
                if (parent != nullptr && node == parent->leftChild) {
                    Node* brother = parent->rightChild;
                    if (brother != nullptr && brother->color == red) {
                        brother->color = black;
                        parent->color = red;
                        RoL(parent);
                    }
                    if (brother != nullptr && brother->leftChild != nullptr &&
                        brother->rightChild != nullptr && brother->leftChild->color == black &&
                        brother->rightChild->color == black)
                        brother->color = red;
                    else {
                        if (brother != nullptr && brother->rightChild != nullptr &&
                            brother->rightChild->color == black) {
                            brother->leftChild->color = black;
                            brother->color = red;
                            RoL(brother);
                        }
                        brother->color = parent->color;
                        parent->color = black;
                        brother->rightChild->color = black;
                        RoL(parent);
                        node = root;
                    }
                } else {
                    Node* brother = parent->leftChild;
                    if (brother != nullptr && brother->color == red) {
                        brother->color = black;
                        parent->color = red;
                        RoR(parent);
                    }
                    if (brother != nullptr && brother->leftChild != nullptr &&
                        brother->rightChild != nullptr && brother->leftChild->color == black &&
                        brother->rightChild->color == red)
                        brother->color = red;
                    else {
                        if (brother != nullptr && brother->leftChild != nullptr &&
                            brother->leftChild->color == black) {
                            brother->rightChild->color = black;
                            brother->color = red;
                            RoL(brother);
                        }
                        brother = parent;
                        parent->color = black;
                        brother->leftChild->color = black;
                        RoR(parent);
                        node = root;
                    }
                }
            }
            node->color = black;
            root->color = black;
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
            if (root == nullptr) {
                cout << "Tree is empty!" << endl;
                return;
            }

            int screenWidth = 160;
            int nodeWidth = 6;
            
            Stack* globalStack = new Stack();
            globalStack->push(root);
            int nBlanks = screenWidth / 2;
            bool isRowEmpty = false;
            
            cout << "\n";
            cout << string(screenWidth, '=') << endl;
            cout << "RED-BLACK TREE STRUCTURE" << endl;
            cout << string(screenWidth, '=') << endl;
            
            while (isRowEmpty == false) {
                Stack* localStack = new Stack();
                isRowEmpty = true;
                
                for (int j = 0; j < nBlanks; j++)
                    cout << ' ';
                
                while (globalStack->isEmpty() == false) {
                    Node* temp = globalStack->pop();
                    if (temp != nullptr) {
                        cout << temp->iData;
                        switch(temp->color) {
                            case black: cout << "(B)"; break;
                            case red: cout << "(R)"; break;
                        }
                        
                        localStack->push(temp->leftChild);
                        localStack->push(temp->rightChild);
                        
                        if (temp->leftChild != nullptr || temp->rightChild != nullptr)
                            isRowEmpty = false;
                    } else {
                        cout << "----";
                        localStack->push(nullptr);
                        localStack->push(nullptr);
                    }
                    
                    for (int j = 0; j < nBlanks * 2 - nodeWidth; j++)
                        cout << ' ';
                }
                cout << endl;
                
                nBlanks /= 2;
                
                while (localStack->isEmpty() == false)
                    globalStack->push(localStack->pop());
                
                delete localStack;
            }
            
            cout << string(screenWidth, '=') << endl;
            delete globalStack;
        }
};

class TreeApp {
    public:
        static void main() {
            int value;
            RBTree* theTree = new RBTree();
                
            theTree->insert(50);
            theTree->insert(75);
            theTree->insert(25);
            theTree->insert(12);
            theTree->insert(6);
            theTree->insert(83);
            theTree->insert(87);
            theTree->insert(15);
            theTree->insert(1);

            theTree->displayTree();

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
                        theTree->insert(value);
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