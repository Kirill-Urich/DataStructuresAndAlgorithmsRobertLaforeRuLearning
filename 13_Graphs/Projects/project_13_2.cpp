// project_13_2.cpp

#include <iostream>
using namespace std;

class Vertex;
class LinkList;

class Link {
    public:
        Vertex* vData;
        Link* next;
    public:
        Link(Vertex* vd) : vData(vd), next(nullptr) { }
        void displayLink() const;
};

class LinkList {
    private:
        Link* first;
    public:
        LinkList() {
            first = nullptr;
        }
        void insert(Vertex* vert) {
            Link* newLink = new Link(vert);

            if (first == nullptr) {
                first = newLink;
                return;
            }

            Link* current = first;
            while (current->next != nullptr)
                current = current->next;

            current->next = newLink;
        }
        Link* findUnvisitedLink() const;
        void displayList() const;
};

class Vertex {
    public:
        char label;
        bool wasVisited;
        LinkList* arrVertex;
    public:
        Vertex() {
            label = ' ';
            wasVisited = false;
            arrVertex = nullptr;
        }
        Vertex(char lab) {
            label = lab;
            wasVisited = false;
            arrVertex = nullptr;
        }
};

void Link::displayLink() const {
    if (vData != nullptr)
        cout << vData->label << " ";
}

void LinkList::displayList() const {
    Link* current = first;
    cout << "List (first-->last): ";
    while (current != nullptr) {
        current->displayLink();
        current = current->next;
    }
    cout << endl;
}

Link* LinkList::findUnvisitedLink() const  {
    Link* current = first;
    while (current != nullptr) {
        if (current->vData != nullptr && !current->vData->wasVisited)
            return current;
        current = current->next;
    }
    return nullptr;
}

class StackX {
    private:
        const int SIZE = 20;
        Vertex** st;
        int top;
    public:
        StackX() {
            st = new Vertex*[SIZE];
            top = -1;
        }
        void push(Vertex* j) {
            st[++top] = j;
        }
        Vertex* pop() {
            return st[top--];
        }
        Vertex* peek() const {
            return st[top];
        }
        bool isEmpty() const {
            return top == -1;
        }
};

class Graph {
    private:
        const int MAX_VERTS = 20;
        Vertex** vertexList;
        int nVerts;
        StackX* theStack;
    private:
        Vertex* getAdjUnvisitedVertex(Vertex* vert) const {
            if (vert == nullptr || vert->arrVertex == nullptr)
                return nullptr;

            Link* foundLink = vert->arrVertex->findUnvisitedLink();
            if (foundLink == nullptr)
                return nullptr;
               
            return foundLink->vData;
        }
    public:
        Graph() {
            vertexList = new Vertex*[MAX_VERTS];
            for (int i = 0; i < MAX_VERTS; i++)
                vertexList[i] = nullptr;

            nVerts = 0;
            theStack = new StackX();
        }
        ~Graph() {
            for (int i = 0; i < nVerts; i++) {
                delete vertexList[i]->arrVertex;
                delete vertexList[i];
            }
            delete[] vertexList;
            delete theStack;
        }
        void addVertex(char lab) {
            if (nVerts < MAX_VERTS) {
                vertexList[nVerts] = new Vertex(lab);
                vertexList[nVerts]->arrVertex = new LinkList();
                nVerts++;
            }
        }
        void addEdge(int start, int end) {
            Vertex* startVertex = vertexList[start];
            Vertex* endVertex   = vertexList[end];

            startVertex->arrVertex->insert(endVertex);
            endVertex->arrVertex->insert(startVertex);
        }
        void displayVertex(Vertex* vert) const {
            if (vert == nullptr)
                return;
            cout << vert->label;
        }
        void displayGraph() const {
            for (int i = 0; i < MAX_VERTS; i++) {
                if (vertexList[i] != nullptr) {
                    cout << vertexList[i]->label << ": ";
                    vertexList[i]->arrVertex->displayList();
                }
            }
        }
        void dfs() {
            vertexList[0]->wasVisited = true;
            displayVertex(vertexList[0]);
            theStack->push(vertexList[0]);

            while (!theStack->isEmpty()) {
                Vertex* vert = getAdjUnvisitedVertex(theStack->peek());
                if (vert == nullptr)
                    theStack->pop();
                else {
                    vert->wasVisited = true;
                    displayVertex(vert);
                    theStack->push(vert);
                }
            }

            for (int j = 0; j < nVerts; j++) {
                vertexList[j]->wasVisited = false;
            }
        }
};

class DFSApp {
    public:
        static void main() {
            Graph* theGraph = new Graph();
            theGraph->addVertex('A');
            theGraph->addVertex('B');
            theGraph->addVertex('C');
            theGraph->addVertex('D');
            theGraph->addVertex('E');

            theGraph->addEdge(0, 1);
            theGraph->addEdge(1, 2);
            theGraph->addEdge(0, 3);
            theGraph->addEdge(3, 4);

            theGraph->displayGraph();

            cout << "Visits: ";
            theGraph->dfs();
            cout << endl;
        }
};

int main() {
    DFSApp::main();
    return 0;
}