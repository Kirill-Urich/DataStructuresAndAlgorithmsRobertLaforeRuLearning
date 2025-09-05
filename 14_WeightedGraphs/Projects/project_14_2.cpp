// project_14_2.cpp

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INFINITY = 1'000'000;

class Vertex;

class Edge {
    private:
        int weight;
        Vertex* child;
    public:
        Edge(Vertex* c = nullptr, int w = INFINITY) {
            child = c;
            weight = w;
        }
        Vertex* getChild() const {
            return child;
        }
        int getWeight() const {
            return weight;
        }
};

class Vertex {
    private:
        vector<Vertex*> neighbors;
        vector<Edge*> edges;
        char label;
        int nSize;
        int eSize;
    public:
        bool isInTree;
    public:
        Vertex(char lab) {
            label = lab;
            isInTree = false;
            nSize = 0;
            eSize = 0;
        }
        void addNeighbor(Vertex* newNeighbor) {
            for (auto it : neighbors)
                if (it == newNeighbor)
                    return;
            neighbors.push_back(newNeighbor);
            nSize++;
        }
        void addEdge(Edge* newEdge) {
            for (auto it : edges)
                if (it == newEdge)
                    return;
            edges.push_back(newEdge);
        }
        char getLabel() const {
            return label;
        }
        vector<Edge*>& getEdges() {
            return edges;
        }
};

class DistPar {
    public:
        int weight;
        Vertex* parentVert;
    public:
        DistPar(Vertex* pv = nullptr, int w = INFINITY) {
            weight = w;
            parentVert = pv;
        }
};

Edge* getEdge(Vertex* start, Vertex* end) {
    for (auto it : start->getEdges())
        if (it->getChild() == end)
            return it;
    return nullptr;
}

int getEdgeWeight(Vertex* start, Vertex* end) {
    Edge* edge = getEdge(start, end);
    if (edge == nullptr)
        return INFINITY;
    return edge->getWeight();
}

class Graph {
    private:
        const int MAX_VERTS = 20;
        Vertex** vertexList;
        int nVerts;
        int nTree;
        DistPar** sPath;
        int currentVert;
        int startToCurrent;
    private:
        int getMin() {
            int minWeight = INFINITY;
            int indexMin = 0;
            for (int j = 1; j < nVerts; j++) {
                if (!vertexList[j]->isInTree && sPath[j]->weight < minWeight) {
                    minWeight = sPath[j]->weight;
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

                Vertex* currentVertex = vertexList[currentVert];
                Vertex* columnVertex = vertexList[column];
                int currentToFringe = getEdgeWeight(currentVertex, columnVertex);
                int startToFringe = startToCurrent + currentToFringe;
                int sPathDist = sPath[column]->weight;

                if (startToFringe < sPathDist) {
                    sPath[column]->parentVert = currentVertex;
                    sPath[column]->weight = startToFringe;
                }
                
                column++;
            }
        }
    public:
        Graph() {
            vertexList = new Vertex*[MAX_VERTS];
            for (int i = 0; i < MAX_VERTS; i++)
                vertexList[i] = nullptr;

            nVerts = 0;
            nTree = 0;

            sPath = new DistPar*[MAX_VERTS];
            for (int i = 0; i < MAX_VERTS; i++)
                sPath[i] = nullptr;
        }
        void addVertex(char lab) {
            if (nVerts == MAX_VERTS)
                return;
            vertexList[nVerts++] = new Vertex(lab);
        }
        void addEdge(int start, int end, int weight) {
            Vertex* startVertex = vertexList[start];
            Vertex* endVertex = vertexList[end];

            Edge* newEdge = new Edge(endVertex, weight);
            startVertex->addEdge(newEdge);
            startVertex->addNeighbor(endVertex);
        }
        void path() {
            int startTree = 0;
            vertexList[startTree]->isInTree = true;
            nTree = 1;

            for (int j = 0; j < nVerts; j++) {
                Vertex* theVertex = vertexList[j];
                int tempDist = getEdgeWeight(vertexList[startTree], theVertex);
                sPath[j] = new DistPar(vertexList[startTree], tempDist);
            }

            while (nTree < nVerts) {
                int indexMin = getMin();
                int minDist = sPath[indexMin]->weight;

                if (minDist == INFINITY) {
                    cout << "There are unreachable vertices" << endl;
                    break;
                } else {
                    currentVert = indexMin;
                    startToCurrent = sPath[indexMin]->weight;
                }
                vertexList[currentVert]->isInTree = true;
                nTree++;
                adjust_sPath();
            }

            displayPaths();

            nTree = 0;
            for (int j = 0; j < nVerts; j++)
                vertexList[j]->isInTree = false;
        }
        void displayPaths() const {
            for (int j = 0; j < nVerts; j++) {
                cout << vertexList[j]->getLabel() << " = ";
                if (sPath[j]->weight == INFINITY)
                    cout << "inf";
                else
                    cout << sPath[j]->weight;
                char parent = sPath[j]->parentVert->getLabel();
                cout << "(" << parent << ") ";
            }
            cout << endl;
        }
        void displayConnectivity() const {
            cout << "Connectivity Table:" << endl;
            for (int i = 0; i < nVerts; i++) {
                cout << vertexList[i]->getLabel() << " ";
                for (auto edge : vertexList[i]->getEdges())
                    cout << edge->getChild()->getLabel() << "(" << edge->getWeight() << ") ";
                cout << endl;
            }
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

            theGraph->displayConnectivity();
        }
};

int main() {
    PathApp::main();
    return 0;
}