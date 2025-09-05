// mstw.cpp
// Построение минимальное остовного дерева для взвешенного графа

#include <iostream>
using namespace std;

class Edge {
    public:
        int srcVert;
        int destVert;
        int distance;
    public:
        Edge(int sv, int dv, int d) {
            srcVert = sv;
            destVert = dv;
            distance = d;
        }
};

class PriorityQ {
    private:
        const int SIZE = 20;
        Edge** queArray;
        int size;
    public:
        PriorityQ() {
            queArray = new Edge*[SIZE];
            size = 0;
        }
        void insert(Edge* item) {
            int j;
            for (j = 0; j < size; j++)
                if (item->distance >= queArray[j]->distance)
                    break;
            for (int k = size - 1; k >= j; k--)
                queArray[k + 1] = queArray[k];

            queArray[j] = item;
            size++;
        }
        Edge* removeMin() {
            return queArray[--size];
        }
        void removeN(int n) {
            for (int j = n; j < size - 1; j++)
                queArray[j] = queArray[j + 1];
            size--;
        }
        Edge* peekMin() {
            return queArray[size - 1];
        }
        int Size() {
            return size;
        }
        bool isEmpty() {
            return size == 0;
        }
        Edge* peekN(int n) {
            return queArray[n];
        }
        int find(int findDex) {
            for (int j = 0; j < size; j++)
                if (queArray[j]->destVert == findDex)
                    return j;
            return -1;
        }
};

class Vertex {
    public:
        char label;
        bool isInTree;
    public:
        Vertex(char lab) {
            label = lab;
            isInTree = false;
        }
};

class Graph {
    private:
        const int MAX_VERTS = 20;
        const int INFINITY = 1'000'000;
        Vertex** vertexList;
        int** adjMat;
        int nVerts;
        int currentVert;
        PriorityQ* thePQ;
        int nTree;
    private:
        void putInPQ(int newVert, int newDist) {
            int queueIndex = thePQ->find(newVert);
            if (queueIndex != -1) {
                Edge* tempEdge = thePQ->peekN(queueIndex);
                int oldDist = tempEdge->distance;
                if (oldDist > newDist) {
                    thePQ->removeN(queueIndex);
                    Edge* theEdge = new Edge(currentVert, newVert, newDist);
                    thePQ->insert(theEdge);
                }
            } else {
                Edge* theEdge = new Edge(currentVert, newVert, newDist);
                thePQ->insert(theEdge);
            }
        }   
    public:
        Graph() {
            vertexList = new Vertex*[MAX_VERTS];
            for (int i = 0; i < MAX_VERTS; i++)
                vertexList[i] = nullptr;

            adjMat = new int*[MAX_VERTS];
            for (int j = 0; j < MAX_VERTS; j++)
                adjMat[j] = new int[MAX_VERTS];

            nVerts = 0;

            for (int k = 0; k < MAX_VERTS; k++)
                for (int l = 0; l < MAX_VERTS; l++)
                    adjMat[k][l] = INFINITY;
            
            thePQ = new PriorityQ();
        }
        void addVertex(char lab) {
            vertexList[nVerts++] = new Vertex(lab);
        }
        void addEdge(int start, int end, int weight) {
            adjMat[start][end] = weight;
            adjMat[end][start] = weight;
        }
        void displayVertex(int v) {
            cout << vertexList[v]->label;
        }
        void mstw() {
            currentVert = 0;

            while (nTree < nVerts - 1) {
                vertexList[currentVert]->isInTree = true;
                nTree++;

                for (int j = 0; j < nVerts; j++) {
                    if (j == currentVert)
                        continue;
                    else if (vertexList[j]->isInTree)
                        continue;
                    int distance = adjMat[currentVert][j];
                    if (distance == INFINITY)
                        continue;

                    putInPQ(j, distance);
                }

                if (thePQ->Size() == 0) {
                    cout << "GRAPH NOT CONNECTED";
                    return;
                }
                Edge* theEdge = thePQ->removeMin();
                int sourceVert = theEdge->srcVert;
                currentVert = theEdge->destVert;

                cout << vertexList[sourceVert]->label;
                cout << vertexList[currentVert]->label;
                cout << " ";

            }
        }
};

class MSTWApp {
    public:
        static void main() {
            Graph* theGraph = new Graph();
            theGraph->addVertex('A');
            theGraph->addVertex('B');
            theGraph->addVertex('C');
            theGraph->addVertex('D');
            theGraph->addVertex('E');
            theGraph->addVertex('F');

            theGraph->addEdge(0, 1, 6);
            theGraph->addEdge(0, 3, 4);
            theGraph->addEdge(1, 2, 10);
            theGraph->addEdge(1, 3, 7);
            theGraph->addEdge(1, 4, 7);
            theGraph->addEdge(2, 3, 8);
            theGraph->addEdge(2, 4, 5);
            theGraph->addEdge(2, 5, 6);
            theGraph->addEdge(3, 4, 12);
            theGraph->addEdge(4, 5, 7);

            cout << "Minimum spanning tree: ";
            theGraph->mstw();
            cout << endl;
        }
};

int main() {
    MSTWApp::main();
    return 0;
}