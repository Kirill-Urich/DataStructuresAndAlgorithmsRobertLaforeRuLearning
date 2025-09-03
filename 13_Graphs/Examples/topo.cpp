// topo.cpp
// Топологическая сортировка

#include <iostream>
using namespace std;

class Vertex {
    public:
        char label;
    public:
        Vertex(char lab) : label(lab) {}
};

class Graph {
    private:
        const int MAX_VERTS = 20;
        Vertex** vertexList;
        int** adjMat;
        int nVerts;
        char* sortedArray;
    private:
        int noSuccessors() {
            bool isEdge;
            for (int row = 0; row < nVerts; row++) {
                isEdge = false;
                for (int col = 0; col < nVerts; col++) {
                    if (adjMat[row][col] > 0) {
                        isEdge = true;
                        break;
                    }
                }
                if (!isEdge)
                    return row;
            }
            return -1;
        }
        void deleteVertex(int delVert) {
            if (delVert != nVerts - 1) {
                for (int j = delVert; j < nVerts - 1; j++)
                    vertexList[j] = vertexList[j + 1];
                
                for (int row = delVert; row < nVerts - 1; row++)
                    moveRowUp(row, nVerts);
                
                for (int col = delVert; col < nVerts - 1; col++)
                    moveColLeft(col, nVerts - 1);
            }
            nVerts--;
        }
        void moveRowUp(int row, int length) {
            for (int col = 0; col < length; col++)
                adjMat[row][col] = adjMat[row + 1][col];
        }
        void moveColLeft(int col, int length) {
            for (int row = 0; row < length; row++)
                adjMat[row][col] = adjMat[row][col + 1]; 
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
            sortedArray = new char[MAX_VERTS];
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
        void topo() {
            int orig_nVerts = nVerts;

            while (nVerts > 0) {
                int currentVertex = noSuccessors();
                if (currentVertex == -1) {
                    cout << "ERROR: Graph has cycles" << endl;
                    return;
                }
                sortedArray[nVerts - 1] = vertexList[currentVertex]->label;
                deleteVertex(currentVertex);
            }
            cout << "Topologically sorted order: ";
            for (int j = 0; j < orig_nVerts; j++)
                cout << sortedArray[j];
            cout << endl;
        }
};

class TopoApp {
    public:
        static void main() {
            Graph* theGraph = new Graph();

            theGraph->addVertex('A');
            theGraph->addVertex('B');
            theGraph->addVertex('C');
            theGraph->addVertex('D');
            theGraph->addVertex('E');
            theGraph->addVertex('F');
            theGraph->addVertex('G');
            theGraph->addVertex('H');

            theGraph->addEdge(0, 3);
            theGraph->addEdge(0, 4);
            theGraph->addEdge(1, 4);
            theGraph->addEdge(24, 5);
            theGraph->addEdge(3, 6);
            theGraph->addEdge(4, 6);
            theGraph->addEdge(5, 7);
            theGraph->addEdge(6, 7);
            theGraph->topo();        
        }
};

int main() {
    TopoApp::main();
    return 0;
}