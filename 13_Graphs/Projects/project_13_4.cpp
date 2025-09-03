// project_13_4.cpp

#include <iostream>
using namespace std;

class StackX {
    private:
        const int SIZE = 20;
        int* st;
        int top;
    public:
        StackX() {
            st = new int[SIZE];
            top = -1;
        }
        void push(int j) {
            st[++top] = j;
        }
        int pop() {
            return st[top--];
        }
        int peek() {
            return st[top];
        }
        bool isEmpty() {
            return top == -1;
        }
};

class Vertex {
    public:
        char label;
        bool wasVisited;
    public:
        Vertex(char lab) {
            label = lab;
            wasVisited = false;
        }
};

class Graph {
    private:
        const int MAX_VERTS = 20;
        Vertex** vertexList;
        int** adjMat;
        int nVerts;
        StackX* theStack;
    private:
        int getAdjUnvisitedVertex(int v) const {
            for (int j = 0; j < nVerts; j++)
                if (adjMat[v][j] == 1 && vertexList[j]->wasVisited == false)
                    return j;
            return -1;
        }
    public:
        Graph() {
            vertexList = new Vertex*[MAX_VERTS];
            for (int i = 0; i < MAX_VERTS; i++) {
                vertexList[i] = nullptr;
            }

            adjMat = new int*[MAX_VERTS];
            for (int i = 0; i < MAX_VERTS; i++)
                adjMat[i] = new int[MAX_VERTS];
            nVerts = 0;
            
            for (int j = 0; j < MAX_VERTS; j++)
                for (int k = 0; k < MAX_VERTS; k++)
                    adjMat[j][k] = 0;
            theStack = new StackX();
        }
        void addVertex(char lab) {
            vertexList[nVerts++] = new Vertex(lab);
        }
        void addEdge(int start, int end) {
            adjMat[start][end] = 1;
        }
        void displayVertex(int v) const {
            cout << vertexList[v]->label;
        }
        void dfs() {
            vertexList[0]->wasVisited = true;
            displayVertex(0);
            theStack->push(0);

            while (!theStack->isEmpty()) {
                int v = getAdjUnvisitedVertex(theStack->peek());
                if (v == -1)
                    theStack->pop();
                else {
                    vertexList[v]->wasVisited = true;
                    displayVertex(v);
                    theStack->push(v);
                }
            }

            for (int j = 0; j < nVerts; j++) {
                vertexList[j]->wasVisited = false;
            }
        }
        void dgct() {
            for (int i = 0; i < nVerts; i++) {
                vertexList[i]->wasVisited = true;
                displayVertex(i);
                theStack->push(i);
                while (!theStack->isEmpty()) {
                    int v = getAdjUnvisitedVertex(theStack->peek());
                    if (v == -1)
                        theStack->pop();
                    else {
                        vertexList[v]->wasVisited = true;
                        displayVertex(v);
                        theStack->push(v);
                    }
                }
                for (int i = 0; i < nVerts; i++)
                    vertexList[i]->wasVisited = false;
                
                cout << endl;
            }
        }

        void displayAdjMat() {
            for (int i = 0; i < nVerts; i++) {
                for (int j = 0; j < nVerts; j++)
                    cout << adjMat[i][j] << " ";
                cout << endl;
            }
        }
        int** WarshallMatrix() const {
            int** WarshallMat = new int*[nVerts];
            for (int k = 0; k < nVerts; k++)
                WarshallMat[k] = new int[nVerts];
            for (int i = 0; i < nVerts; i++)
                for (int j = 0; j < nVerts; j++)
                    WarshallMat[i][j] = 0;

            for (int x = 0; x < nVerts; x++)
                for (int y = 0; y < nVerts; y++)
                    if (adjMat[x][y] == 1)
                        for (int z = 0; z < nVerts; z++)
                            if (adjMat[z][x] == 1 || adjMat[z][y] == 1)
                                WarshallMat[z][y] = 1;

            return WarshallMat;
        }
        int getSize() const {
            return nVerts;
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

            theGraph->addEdge(0, 2);
            theGraph->addEdge(1, 0);
            theGraph->addEdge(4, 1);
            theGraph->addEdge(3, 4);
            theGraph->addEdge(2, 4);

            cout << "AdjMat: " << endl;
            theGraph->displayAdjMat();
            cout << endl;

            cout << "WarshMat: " << endl;
            int size = theGraph->getSize();
            int** warshMat = theGraph->WarshallMatrix();
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++)
                    cout << warshMat[i][j] << " ";
                cout << endl;
            }
        }
};

int main() {
    DFSApp::main();
    return 0;
}