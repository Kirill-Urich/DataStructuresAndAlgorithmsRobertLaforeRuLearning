// project_8_3.cpp

#include <iostream>
using namespace std;

class Node {
    public:
        char cData;
        Node* leftChild = nullptr;
        Node* rightChild = nullptr;
    public:
        Node(char c) : cData(c) {}
        void displayNode() {
            cout << cData;
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
        void preOrder(Node* localRoot) {
            if (localRoot != nullptr) {
                cout << localRoot->cData << " ";
                preOrder(localRoot->leftChild);
                preOrder(localRoot->rightChild);
            }
        }
        void inOrder(Node* localRoot) {
            if (localRoot != nullptr) {
                inOrder(localRoot->leftChild);
                cout << localRoot->cData << " ";
                inOrder(localRoot->rightChild);
            }
        }
        void postOrder(Node* localRoot) {
            if (localRoot != nullptr) {
                postOrder(localRoot->leftChild);
                postOrder(localRoot->rightChild);
                cout << localRoot->cData << " ";
            }
        }
    public:
        Tree() : root(nullptr) {}
        Tree(char c) {
            root = new Node(c);
        }
        Tree(Node* node) : root(node) {}
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
                        cout << temp->cData;
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
            string sequence = "ABCDEFGH";
            Tree*  theTree  = buildTree(sequence);
            theTree->displayTree();
        }

        static Tree* buildTree(const string& sequence) {
            if (sequence.empty()) return nullptr;
            int size = sequence.size();
            Node** nodes = new Node*[size];

            for (int i = 0; i < size; i++)
                nodes[i] = new Node(sequence[i]);

            for (int i = 0; i < size; i++) {
                int left  = 2 * i + 1;
                int right = 2 * i + 2;
                if (left  < size) nodes[i]->leftChild  = nodes[left];
                if (right < size) nodes[i]->rightChild = nodes[right];
            }

            Tree* result = new Tree(nodes[0]);
            delete[] nodes;
            return result;
        }
};

int main() {
    TreeApp::main();
    return 0;
}