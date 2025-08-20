// postfix.cpp
// Разбор постфиксных арифметических выражений

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
                cout << localRoot->cData;
                preOrder(localRoot->leftChild);
                preOrder(localRoot->rightChild);
            }
        }
        void inOrder(Node* localRoot) {
            if (localRoot != nullptr) {
                cout << "(";
                inOrder(localRoot->leftChild);
                cout << localRoot->cData;
                inOrder(localRoot->rightChild);
                cout << ")";
            }
        }
        void postOrder(Node* localRoot) {
            if (localRoot != nullptr) {
                postOrder(localRoot->leftChild);
                postOrder(localRoot->rightChild);
                cout << localRoot->cData;
            }
        }
    public:
        Tree() : root(nullptr) {}
        Tree(char c) {
            root = new Node(c);
        }
        Tree(char c, Tree* left, Tree* right) {
            root = new Node(c);
            if (left  != nullptr) root->leftChild  = left->root;
            if (right != nullptr) root->rightChild = right->root;
        }
        void traverse(int traverseType) {
            switch(traverseType) {
                case 1:
                    cout << "Preorder traversal: ";
                    preOrder(root);
                    cout << endl;
                    break;
                case 2:
                    cout << "Inorder traversal: ";
                    inOrder(root);
                    cout << endl;
                    break;
                case 3:
                    cout << "Postorder traversal: ";
                    postOrder(root);
                    cout << endl;
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

class StackX {
    private:
        int maxSize;
        Tree** stackArray;
        int top;
    public:
        StackX(int size) {
            maxSize = size;
            stackArray = new Tree*[maxSize];
            top = -1;
        }
        void push(Tree* j) {
            stackArray[++top] = j;
        }
        Tree* pop() {
            return stackArray[top--];
        }
        Tree* peek() {
            return stackArray[top];
        }
        bool isEmpty() {
            return top == -1;
        }
        bool isFull() {
            return top == maxSize - 1;
        }
        int size() {
            return top + 1;
        }
        Tree* peekN(int n) {
            return stackArray[n];
        }
        void displayStack(string s) {
            cout << s;
            cout << "Stack (bottom-->top): ";
            for (int j = 0; j < size(); j++)
                peekN(j)->displayTree();
            cout << endl;
        }
};


class ParsePost {
    private:
        StackX* theStack;
        string input;
    public:
        ParsePost(string s) {
            input = s;
        }
        Tree* doParse() {
            theStack = new StackX(20);
            char ch;
            Tree* interAns;
            for (size_t j = 0; j < input.length(); j++) {
                ch = input[j];
                // string temp = ch + " ";
                // theStack->displayStack(temp);
                if (ch >= 'A' && ch <= 'Z') {
                    Tree* newTree = new Tree(ch);
                    theStack->push(newTree);
                }
                else {
                    Tree* num2 = theStack->pop();
                    Tree* num1 = theStack->pop();
                    interAns = new Tree(ch, num1, num2);
                    theStack->push(interAns);
                }
            }
            interAns = theStack->pop();
            return interAns;
        }
};

class TreeApp {
    public:
        static void main() {
            string value = "ABC*+DEF*-/G+";
            ParsePost* theParsePost = new ParsePost(value);
            Tree* theTree = theParsePost->doParse();
            theTree->displayTree();
            
            theTree->traverse(1);
            theTree->traverse(2);
            theTree->traverse(3);
        }
};

int main() {
    TreeApp::main();
    return 0;
}