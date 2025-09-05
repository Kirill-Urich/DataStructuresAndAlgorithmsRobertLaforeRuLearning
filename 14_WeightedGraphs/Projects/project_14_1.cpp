// project_14_1.cpp

#include <iostream>
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
        int getMin(int curIndex) {
            int minDist = INFINITY;
            int indexMin = 0;
            for (int j = 0; j < nVerts; j++) {
                if (j == curIndex)
                    continue;
                if (!vertexList[j]->isInTree && sPath[j]->distance < minDist) {
                    minDist = sPath[j]->distance;
                    indexMin = j;
                }
            }
            return indexMin;
        }
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
        void clearPaths() {
            for (int i = 0; i < MAX_VERTS; i++) {
                sPath[i] = nullptr;
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
        void path() {
            for (int startTree = 0; startTree < nVerts; ++startTree) {
                vertexList[startTree]->isInTree = true;
                nTree = 1;

                for (int j = 0; j < nVerts; j++) {
                    int tempDist = adjMat[startTree][j];
                    sPath[j] = new DistPar(startTree, tempDist);
                }

                while (nTree < nVerts) {
                    int indexMin = getMin(startTree);
                    int minDist = sPath[indexMin]->distance;

                    if (minDist == INFINITY) {
                        cout << "There are unreachable vertice" << endl;
                        break;
                    } else {
                        currentVert = indexMin;
                        startToCurrent = sPath[indexMin]->distance;
                    }
                    vertexList[currentVert]->isInTree = true;
                    nTree++;
                    adjust_sPath();
                }

                displayPaths();
                clearPaths();

                nTree = 0;
                for (int j = 0; j < nVerts; j++)
                    vertexList[j]->isInTree = false;
            }
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

class PathApp {
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

            cout << "Shortest paths" << endl;
            theGraph->path();
            cout << endl;
        }
};

int main() {
    PathApp::main();
    return 0;
}