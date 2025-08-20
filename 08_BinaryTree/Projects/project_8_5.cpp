// project_8_5.cpp

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Node {
    public:
        char cData;
        int fData;
        Node* leftChild = nullptr;
        Node* rightChild = nullptr;
    public:
        Node(char c, int f) : cData(c), fData(f) {}
        void displayNode() {
            cout << "{" << cData << ": " << fData << "}";
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
        Tree(Node* node) : root(node) {}
        Tree(Tree* left, Tree* right, int sumFreq) {
            root = new Node('+', sumFreq);
            root->leftChild = left->root;
            root->rightChild = right->root;
        }
        Node* getRoot() { return root; }
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
                    Node* temp = globalStack->pop();
                    if (temp != nullptr) {
                        if (temp->cData == '\n')
                            cout << "/n";
                        else if (temp->cData != '+')
                            temp->displayNode();
                        else {
                            cout << "+";
                        }
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
        Tree** queArray;
        int nItems;
    public:
        PriorityQ(int s) {
            maxSize = s;
            queArray = new Tree*[maxSize];
            nItems = 0;
        }
        void insert(Tree* item) {
            int j;
            
            if (nItems == 0)
                queArray[nItems++] = item;
            else {
                Node* root = item->getRoot();
                int frequence = root->fData;
                for (j = nItems - 1; j >= 0; j--) {
                    Node* curRoot = queArray[j]->getRoot();
                    int curFrequence = curRoot->fData;
                    if (frequence > curFrequence)
                        queArray[j + 1] = queArray[j];
                    else
                        break;
                }
                queArray[j + 1] = item;
                nItems++;
            }
        }
        Tree* remove() {
            return queArray[--nItems];
        }
        Tree* peekMin() {
            return queArray[--nItems];
        }
        bool isEmpty() {
            return nItems == 0;
        }
        bool isFull() {
            return nItems == maxSize;
        }
        int size() {
            return nItems;
        }
};

class HuffmanAlgorithm {
    private:
        string sequence;
        string encodedSequence;
        map<char, int> frequencyTable;
        map<char, string> encodedTable;
        Tree* HuffmanTree;
    private:
        map<char, int> buildFrequencyTable(string seq) {
            map<char, int> tempTable;
            for (char c : seq)
                tempTable[c]++;
            tempTable['\n']++;
            return tempTable;
        }

        Tree* buildHuffmanTree(map<char, int> freqTable) {
            int size = freqTable.size();
            PriorityQ* thePriorityQueue = new PriorityQ(size);
            // cout << "buildHuffmanTree in action: " << endl;
            for (auto iter : freqTable) {
                // cout << iter.first << " " << iter.second << endl;
                Node* curNode;
                curNode = new Node(iter.first, iter.second);
                Tree* curTree = new Tree(curNode);
                thePriorityQueue->insert(curTree);
            }

            while (thePriorityQueue->size() != 1) {
                Tree* tree1 = thePriorityQueue->remove();
                Tree* tree2 = thePriorityQueue->remove();
                int freq1 = tree1->getRoot()->fData;
                int freq2 = tree2->getRoot()->fData;
                int sumFreq = freq1 + freq2;
                Tree* tempTree = new Tree(tree1, tree2, sumFreq);
                thePriorityQueue->insert(tempTree);
            }
            Tree* result = thePriorityQueue->remove();
            return result;
        }

        void buildEncodedTable(Node* root, const string& code) {
            if (!root) return;

            if (!root->leftChild && !root->rightChild) {
                encodedTable[root->cData] = code;
                return;
            }

            if (root->leftChild)
                buildEncodedTable(root->leftChild, code + "0");
            if (root->rightChild)
                buildEncodedTable(root->rightChild, code + "1");
        }

    public:
        HuffmanAlgorithm() {
            sequence = "";
            HuffmanTree = nullptr;
        }
        HuffmanAlgorithm(string s) {
            sequence = s;
            frequencyTable = buildFrequencyTable(sequence);
            HuffmanTree = buildHuffmanTree(frequencyTable);
            buildEncodedTable(HuffmanTree->getRoot(), "");
        }
        void displayHuffmanTree() {
            HuffmanTree->displayTree();
        }
        void displayEncodedTable() {
            for (auto s : encodedTable) {
                if (s.first == '\n')
                    cout << "\\n";
                else cout << s.first;
                cout << ": " << s.second << endl;
            }
        }
        void displayEncodedSequence() {
            encodedSequence.clear();
            for (auto c : sequence) {
                encodedSequence += encodedTable[c] + "";
            }
            cout << encodedSequence << endl;
        }
        void decodeSequence(string seq) {
            Node* root = HuffmanTree->getRoot();
            if (root == nullptr)
                return;

            Node* current = root;
            string s = "";
            for (auto bit : seq) {
                if (bit == '0') {
                    current = current->leftChild;
                    s += "0";
                }
                else if (bit == '1') {
                    current = current->rightChild;
                    s += "1";
                }

                if (current == nullptr) {
                    current = root;
                    s = "";
                    continue;
                }
                
                if (!current->leftChild && !current->rightChild) {
                    cout << current->cData;
                    current = root;
                    s = "";
                }
            }

            if (current != root && !current->leftChild && !current->rightChild)
                cout << current->cData << " (" << s << ")" << endl;
        }
};

class HuffmanAlgorithmApp {
    public:
        static void main() {
            string s = 
            "Tommy returns to Birmingham and goes straight to the "
            "hospital where Ruby is. Lizzie meets him at the entrance "
            "to tell him that the gold salts treatment didn't work, "
            "and that Ruby had died";

            string tempString = "SUSIE SAYS IT IS EASY\n";
            HuffmanAlgorithm* theHuffman = new HuffmanAlgorithm(tempString);
            theHuffman->displayHuffmanTree();
            theHuffman->displayEncodedTable();
            theHuffman->displayEncodedSequence();
            string codeString = "101110010011110000101101111110000111110100011100011001101101111010";
            theHuffman->decodeSequence(codeString);
        }
};

int main() {
    HuffmanAlgorithmApp::main();
    return 0;
}