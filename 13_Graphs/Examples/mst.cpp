// mst.cpp
// Построение минимального остовного дерева

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
            adjMat[end][start] = 1;
        }
        void displayVertex(int v) {
            cout << vertexList[v]->label;
        }
        void mst() {
            vertexList[0]->wasVisited = true;
            theStack->push(0);
            while (!theStack->isEmpty()) {
                int currentVertex = theStack->peek();

                int v = getAdjUnvisitedVertex(currentVertex);
                if (v == -1)
                    theStack->pop();
                else {
                    vertexList[v]->wasVisited = true;
                    theStack->push(v);
                    displayVertex(currentVertex);
                    displayVertex(v);
                    cout << " ";
                }
            }

            for (int j = 0; j < nVerts; j++)
                vertexList[j]->wasVisited = false;
        }
};

class MSTApp {
    public:
        static void main() {
            Graph* theGraph = new Graph();
            theGraph->addVertex('A');
            theGraph->addVertex('B');
            theGraph->addVertex('C');
            theGraph->addVertex('D');
            theGraph->addVertex('E');
            theGraph->addEdge(0, 1);
            theGraph->addEdge(0, 2);
            theGraph->addEdge(0, 3);
            theGraph->addEdge(0, 4);
            theGraph->addEdge(1, 2);
            theGraph->addEdge(1, 3);
            theGraph->addEdge(1, 4);
            theGraph->addEdge(2, 3);
            theGraph->addEdge(2, 4);
            theGraph->addEdge(3, 4);

            cout << "Minimum spanning tree: ";
            theGraph->mst();
            cout << endl;
        }
};

int main() {
    MSTApp::main();
    return 0;
}