// project_14_3.cpp

#include <iostream>
#include <iomanip>
using namespace std;

class DistPar {
    public:
        int distance;
        int parentVert;
    public:
        DistPar(int pv, int d) {
            distance = d;
            parentVert = pv;
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
        int nTree;
        DistPar** sPath;    // массив данных кратчайших путей
        int currentVert;
        int startToCurrent; // расстояние до currentVert
    private:
        void adjust_sPath() {
            int column = 1;
            while (column < nVerts) {
                if (vertexList[column]->isInTree) {
                    column++;
                    continue;
                }

                int currentToFringe = adjMat[currentVert][column];
                int startToFringe = startToCurrent + currentToFringe;
                int sPathDist = sPath[column]->distance;

                if (startToFringe < sPathDist) {
                    sPath[column]->parentVert = currentVert;
                    sPath[column]->distance = startToFringe;
                }
                
                column++;
            }
        }
    public:
        Graph() {
            vertexList = new Vertex*[MAX_VERTS];
            for (int i = 0; i < MAX_VERTS; i++)
                vertexList[i] = nullptr;

            adjMat = new int*[MAX_VERTS];
            for (int i = 0; i < MAX_VERTS; i++)
                adjMat[i] = new int[MAX_VERTS];

            for (int i = 0; i < MAX_VERTS; i++)
                for (int j = 0; j < MAX_VERTS; j++)
                    adjMat[i][j] = INFINITY;

            nVerts = 0;
            nTree = 0;

            sPath = new DistPar*[MAX_VERTS];
            for (int i = 0; i < MAX_VERTS; i++) {
                sPath[i] = nullptr;
            }
        }
        void addVertex(char lab) {
            vertexList[nVerts++] = new Vertex(lab);
        }
        void addEdge(int start, int end, int weight) {
            adjMat[start][end] = weight;
        }
        void FloydMatrix() const {
            int** matrix = new int*[nVerts];

            for (int i = 0; i < nVerts; i++) {
                matrix[i] = new int[nVerts];
                for (int j = 0; j < nVerts; j++)
                    matrix[i][j] = (adjMat[i][j] == INFINITY) ? ((i == j) ? 0 : -1) : adjMat[i][j];
            }

            for (int x = 0; x < nVerts; x++)
                for (int y = 0; y < nVerts; y++)
                    if (matrix[x][y] != -1)
                        for (int z = 0; z < nVerts; z++)
                            if (matrix[z][x] != -1)
                                if (z != y && (matrix[z][y] == -1 || matrix[x][y] + matrix[z][x] < matrix[z][y]))
                                    matrix[z][y] = matrix[x][y] + matrix[z][x];
                        

            cout << "Алгоритм Флойда:" << endl;

            cout << "  ";
            for (int i = 0; i < nVerts; i++)
                cout << setw(5) << vertexList[i]->label;
            cout << endl;
            for (int i = 0; i < nVerts; i++) {
                cout << vertexList[i]->label << " ";
                for (int j = 0; j < nVerts; j++)
                    cout << setw(5) << matrix[i][j];
                cout << endl;
            }
        }
        int getNVerts() const {
            return nVerts;
        }
        void displayPaths() {
            for (int j = 0; j < nVerts; j++) {
                cout << vertexList[j]->label << " = ";
                if (sPath[j]->distance == INFINITY)
                    cout << "inf";
                else
                    cout << sPath[j]->distance;
                char parent = vertexList[sPath[j]->parentVert]->label;
                cout << "(" << parent << ") ";
            }
            cout << endl;
        }
};

class FloydApp {
    public:
        static void main() {
            Graph* theGraph = new Graph();

            theGraph->addVertex('A');
            theGraph->addVertex('B');
            theGraph->addVertex('C');
            theGraph->addVertex('D');
            theGraph->addVertex('E');

            theGraph->addEdge(0, 1, 50);
            theGraph->addEdge(0, 3, 80);
            theGraph->addEdge(1, 2, 60);
            theGraph->addEdge(1, 3, 90);
            theGraph->addEdge(2, 4, 40);
            theGraph->addEdge(3, 2, 20);
            theGraph->addEdge(3, 4, 70);
            theGraph->addEdge(4, 1, 50);

            theGraph->FloydMatrix();
        }
};

int main() {
    FloydApp::main();
    return 0;
}