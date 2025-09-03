// bfs.cpp
// Обход в ширину

#include <iostream>
using namespace std;

class Queue {
    private:
        const int SIZE = 20;
        int* queArray;
        int front;
        int rear;
    public:
        Queue() {
            queArray = new int[SIZE];
            front = 0;
            rear = -1;
        }
        void insert(int j) {
            if (rear == SIZE - 1)
                rear = -1;
            queArray[++rear] = j;
        }
        int remove() {
            int temp = queArray[front++];
            if (front == SIZE)
                front = 0;
            return temp;
        }
        bool isEmpty() {
            return (rear + 1 == front || (front + SIZE - 1 == rear));
        }
};

class Vertex {
    public:
        char label;
        bool wasVisited;
    public:
        Vertex() = default;
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
        Queue* theQueue;
    private:
        int getAdjUnvisitedVertex(int v) {
            for (int j = 0; j < nVerts; j++) {
                if (adjMat[v][j] == 1 && vertexList[j]->wasVisited == false)
                    return j;
            }
            return -1;
        }
    public:
        Graph() {
            vertexList = new Vertex*[MAX_VERTS];
            adjMat = new int*[MAX_VERTS];

            for (int i = 0; i < MAX_VERTS; i++)
                adjMat[i] = new int[MAX_VERTS];

            for (int j = 0; j < MAX_VERTS; j++)
                for (int k = 0; k < MAX_VERTS; k++)
                    adjMat[j][k] = 0;

            theQueue = new Queue();
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
        void bfs() {
            vertexList[0]->wasVisited = true;
            displayVertex(0);
            theQueue->insert(0);
            int v2;

            while (!theQueue->isEmpty()) {
                int v1 = theQueue->remove();
                v2 = getAdjUnvisitedVertex(v1);
                while (v2 != -1) {
                    vertexList[v2]->wasVisited = true;
                    displayVertex(v2);
                    theQueue->insert(v2);
                    v2 = getAdjUnvisitedVertex(v1);
                }
            }

            for (int j = 0; j < nVerts; j++)
                vertexList[j]->wasVisited = false;
        }
};

class BFSApp {
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

            cout << "Visits: ";
            theGraph->bfs();
            cout << endl;
        }
};

int main() {
    BFSApp::main();
    return 0;
}