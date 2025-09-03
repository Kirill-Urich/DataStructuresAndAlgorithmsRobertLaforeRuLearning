// project_13_3.cpp

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
        int getAdjUnvisitedVertex(int v) {
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
        void displayVertex(int v) {
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
            theGraph->addEdge(1, 4);
            theGraph->addEdge(3, 4);
            theGraph->addEdge(4, 2);

            cout << "Visits: ";
            theGraph->dfs();
            cout << endl;

            theGraph->dgct();
        }
};

int main() {
    DFSApp::main();
    return 0;
}