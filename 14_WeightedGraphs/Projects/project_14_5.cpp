// project_14_5.cpp

#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAX_VERTS = 20;

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
        const int INFINITY = 1'000'000;
        Vertex** vertexList;
        int** adjMat;
        int size;

        vector<vector<int>> paths;
        int pathSize;
    private:
        void doAnagram(int newSize, vector<int>& seq) {
            if (newSize == 1)
                return;
            for (int j = 0; j < newSize; j++) {
                doAnagram(newSize - 1, seq);
                if (newSize == 2) {
                    paths.push_back(seq);
                    pathSize++;
                }
                rotate(newSize, seq);
            }
        }
        void rotate(int newSize, vector<int>& seq) {
            int j;
            int position = size - newSize;
            char temp = seq[position];
            for (j = position + 1; j < size; j++)
                seq[j - 1] = seq[j];
            seq[j - 1] = temp;
        }
    public:
        Graph() {
            vertexList = new Vertex*[MAX_VERTS];
            adjMat = new int*[MAX_VERTS];

            for (int i = 0; i < MAX_VERTS; i++)
                adjMat[i] = new int[MAX_VERTS];

            for (int j = 0; j < MAX_VERTS; j++)
                for (int k = 0; k < MAX_VERTS; k++)
                    adjMat[j][k] = INFINITY;

            size = 0;
        }
        void addVertex(char lab) {
            vertexList[size++] = new Vertex(lab);
        }
        void addEdge(int start, int end, int weight) {
            adjMat[start][end] = weight;
            adjMat[end][start] = weight;
        }
        void SolveTheProblem() {
            vector<int> sequence;
            pathSize = 0;
            for (int i = 0; i < size; i++)
                sequence.push_back(i);
            doAnagram(size, sequence);
            
            string Path;

            for (int i = 0; i < pathSize; i++) {
                vector<int> seq = paths[i];
                bool validPath = true;
                for (int j = 1; j < size; j++) {
                    int weight = adjMat[seq[j - 1]][seq[j]];
                    if (weight == INFINITY)
                        validPath = false;
                }

                if (!validPath)
                    continue;

                Path = "";
                for (int i = 0; i < size; i++)
                    Path += vertexList[seq[i]]->label;
                cout << Path << endl;
            }
        }
};

class ProblemApp {
    public:
        static void main() {
            Graph* theGraph = new Graph();

            theGraph->addVertex('A');
            theGraph->addVertex('B');
            theGraph->addVertex('C');
            theGraph->addVertex('D');
            theGraph->addVertex('E');

            theGraph->addEdge(0, 1, 50);
            theGraph->addEdge(1, 3, 60);
            theGraph->addEdge(1, 4, 10);
            theGraph->addEdge(2, 3, 70);
            theGraph->addEdge(2, 4, 40);

            cout << "Shortest path" << endl;
            theGraph->SolveTheProblem();
        }
};

int main() {
    ProblemApp::main();
    return 0;
}