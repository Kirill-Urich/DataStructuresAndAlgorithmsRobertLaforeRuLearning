// tree234.cpp
// Работа с 234-деревом

#include <iostream>
#include <limits>
using namespace std;

class DataItem {
    public:
        long dData;
    public:
        DataItem(long dd) : dData(dd) {}
        DataItem() : dData(0) {}
        void displayItem() {
            cout << "/" << dData;
        }
};

class Node {
    private:
        static const int ORDER = 4;
        int numItems;
        Node* parent;
        Node** childArray = new Node*[ORDER];
        DataItem** itemArray = new DataItem*[ORDER - 1];
    public:
        void connectChild(int childNum, Node* child) {
            childArray[childNum] = child;
            if (child != nullptr)
                child->parent = this;
        }
        Node* disconnectChild(int childNum) {
            Node* tempNode = childArray[childNum];
            childArray[childNum] = nullptr;
            return tempNode;
        }
        Node* getChild(int childNum) {
            return childArray[childNum];
        }
        Node* getParent() {
            return parent;
        }
        bool isLeaf() {
            return childArray[0] == nullptr;
        }
        int getNumItems() {
            return numItems;
        }
        DataItem* getItem(int index) {
            return itemArray[index];
        }
        bool isFull() {
            return numItems == ORDER - 1;
        }
        int findItem(long key) {
            for (int j = 0; j < ORDER - 1; j++) {
                if (itemArray[j] == nullptr)
                    break;
                else if (itemArray[j]->dData == key)
                    return j;
            }
            return - 1;
        }
        int insertItem(DataItem* newItem) {
            numItems++;
            long newKey = newItem->dData;

            for (int j = ORDER - 2; j >= 0; j--) {
                if (itemArray[j] == nullptr)
                    continue;
                else {
                    long itsKey = itemArray[j]->dData;
                    if (newKey < itsKey)
                        itemArray[j + 1] = itemArray[j];
                    else {
                        itemArray[j + 1] = newItem;
                        return j + 1;
                    }
                }
            }
            itemArray[0] = newItem;
            return 0;
        }
        DataItem* removeItem() {
            DataItem* temp = itemArray[numItems - 1];
            itemArray[numItems - 1] = nullptr;
            numItems--;
            return temp;
        }
        void displayNode() {
            for (int j = 0; j < numItems; j++)
                itemArray[j]->displayItem();
            cout << "/" << endl;
        }
};

class Tree234 {
    private:
        Node* root = new Node();
    private:
        void recDisplayTree(Node* thisNode, int level, int childNumber) {
            cout << "level = " << level << " child = " << childNumber << " ";
            thisNode->displayNode();

            int numItems = thisNode->getNumItems();
            for (int j = 0; j < numItems + 1; j++) {
                Node* nextNode = thisNode->getChild(j);
                if (nextNode != nullptr)
                    recDisplayTree(nextNode, level + 1, j);
                else
                    return;
            }
        }
    public:
        int find(long key) {
            Node* curNode = root;
            int childNumber;
            while (true) {
                childNumber = curNode->findItem(key);
                if (childNumber != -1)
                    return childNumber;
                else if (curNode->isLeaf())
                    return -1;
                else
                    curNode = getNextChild(curNode, key);
            }
        }
        void insert(long dValue) {
            Node* curNode = root;
            DataItem* tempItem = new DataItem(dValue);
            
            while (true) {
                if (curNode->isFull()) {
                    split(curNode);
                    curNode = curNode->getParent();
                    curNode = getNextChild(curNode, dValue);
                }
                else if (curNode->isLeaf())
                    break;
                else
                    curNode = getNextChild(curNode, dValue);
            }
            curNode->insertItem(tempItem);
        }
        void split(Node* thisNode) {
            DataItem* itemB;
            DataItem* itemC;
            Node* parent;
            Node* child2;
            Node* child3;
            int itemIndex;

            itemC = thisNode->removeItem();
            itemB = thisNode->removeItem();
            child2 = thisNode->disconnectChild(2);
            child3 = thisNode->disconnectChild(3);
            Node* newRight = new Node();

            if (thisNode == root) {
                root = new Node();
                parent = root;
                root->connectChild(0, thisNode);
            }
            else
                parent = thisNode->getParent();
            
            itemIndex = parent->insertItem(itemB);
            int n = parent->getNumItems();

            for (int j = n - 1; j > itemIndex; j--) {
                Node* temp = parent->disconnectChild(j);
                parent->connectChild(j + 1, temp);
            }

            parent->connectChild(itemIndex + 1, newRight);
            newRight->insertItem(itemC);
            newRight->connectChild(0, child2);
            newRight->connectChild(1, child3);
        }
        Node* getNextChild(Node* theNode, long theValue) {
            int j;
            int numItems = theNode->getNumItems();
            for (j = 0; j < numItems; j++)
                if (theValue < theNode->getItem(j)->dData)
                    return theNode->getChild(j);
            return theNode->getChild(j);
        }
        void displayTree() {
            recDisplayTree(root, 0, 0);
        }
};

class Tree234App {
    public:
        static void main() {
            long value;
            Tree234* theTree = new Tree234();
            theTree->insert(50);            
            theTree->insert(40);
            theTree->insert(60);            
            theTree->insert(30);
            theTree->insert(70);
            
            while (true) {
                cout << "Enter first letter of ";
                cout << "show, insert of find: ";

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
                        int found = theTree->find(value);
                        if (found != -1)
                            cout << "Found " << value << endl;
                        else {
                            cout << "Could not find " << value << endl;
                            break;
                        }
                        break;
                    }
                    default:
                        cout << "Ivalid entry\n";
                }
            }
        }
};

int main() {
    Tree234App::main();
    return 0;
}

