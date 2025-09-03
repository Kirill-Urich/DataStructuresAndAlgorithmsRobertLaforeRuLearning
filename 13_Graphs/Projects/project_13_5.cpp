// project_13_5.cpp

#include <iostream>
#include <vector>
using namespace std;

const int SIZE = 6;

class Vertex {
    public:
        bool wasVisited;
        pair<int, int> field;
        Vertex** availableFields;
        int numPairs;
    public:
        Vertex(int x, int y) {
            if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
                throw out_of_range("x and y are out of range");
            }
            field = make_pair(x, y);
            wasVisited = false;
            availableFields = nullptr;
        }
        void connectVertices(Vertex** allVertices) {
            numPairs = countAvailableMoves();
            availableFields = new Vertex*[numPairs];

            int index = 0;
            int x = field.first;
            int y = field.second;

            const vector<pair<int, int>> moves { 
                {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                {1, -2}, {1, 2}, {2, -1}, {2, 1} };
            
            for (auto& move : moves) {
                int newX = x + move.first;
                int newY = y + move.second;

                if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE) {
                    Vertex* target = allVertices[newX * SIZE + newY];
                    availableFields[index++] = target;
                }
            }
        }
        void display() {
            cout << "{" << field.first << ", " << field.second << "} ";
        }
    private:
        int countAvailableMoves() const {
            int count = 0;
            int x = field.first;
            int y = field.second;
            
            const vector<pair<int, int>> moves { 
                {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                {1, -2}, {1, 2}, {2, -1}, {2, 1} };
            
            for (const auto& move : moves) {
                int newX = x + move.first;
                int newY = y + move.second;

                if (newX >= 0 && newX < SIZE && newY >= 0 && newY < SIZE) {
                    count++;
                }
            }
            return count;
        }
};

class StackX {
    private:
        const int size = SIZE * SIZE;
        Vertex** st;
        int top;
    public:
        StackX() {
            st = new Vertex*[size];
            top = -1;
        }
        void push(Vertex* j) {
            st[++top] = j;
        }
        Vertex* pop() {
            return st[top--];
        }
        Vertex* peek() {
            return st[top];
        }
        bool isEmpty() {
            return top == -1;
        }
};

class KnightGraph {
    private:
        const int MAX_VERTS = SIZE * SIZE;
        Vertex** vertexList;
        StackX* theStack;
    private:
        Vertex* getAdjUnvisitedVertex(const Vertex* v) {
            Vertex** tempFields = v->availableFields;
            for (int i = 0; i < v->numPairs; i++) {
                if (!tempFields[i]->wasVisited)
                    return tempFields[i];
            }
            return nullptr;
        }
        bool findTour(Vertex* current, int moveCount) {
            if (moveCount == SIZE * SIZE)
                return true;

            for (int i = 0; i < current->numPairs; i++) {
                Vertex* next = current->availableFields[i];
                if (!next->wasVisited) {
                    next->wasVisited = true;
                    if (findTour(next, moveCount + 1)) {
                        next->display();
                        return true;
                    }
                    next->wasVisited = false;
                }
            }

            return false;
        }
        void makeVerticesVisitedFalse() {
            for (int i = 0; i < MAX_VERTS; i++)
                vertexList[i]->wasVisited = false;
        }
    public:
        KnightGraph() {
            vertexList = new Vertex*[MAX_VERTS];
            
            for (int x = 0; x < SIZE; x++)
                for (int y = 0; y < SIZE; y++)
                    vertexList[x * SIZE + y] = new Vertex(x, y);
                    
            for (int i = 0; i < MAX_VERTS; i++)
                vertexList[i]->connectVertices(vertexList);
                
            theStack = new StackX();
        }
        void KnightGame() {
            for (int i = 0; i < MAX_VERTS; i++) {
                Vertex* current = vertexList[i];
                if (findTour(current, 0) == true) {
                    cout << endl;
                    current->display();
                    cout << endl << endl;
                }
                makeVerticesVisitedFalse();
            }
        }
};

class KnightGraphApp {
    public:
        static void main() {
            KnightGraph* theKnightGraph = new KnightGraph();
            theKnightGraph->KnightGame();
        }
};


int main() {
    KnightGraphApp::main();
    return 0;
}