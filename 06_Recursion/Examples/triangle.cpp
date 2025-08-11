// triangle.cpp
// Вычисление треугольных числе

#include <iostream>
using namespace std;

class TriangleApp {
    private:
        static int theNumber;
    public:
        static void main() {
            cout << "Enter a number: ";
            cin >> theNumber;
            int theAnswer = triangle(theNumber);
            cout << "Triangle = " << theAnswer << endl;
        }
        static int triangle(int n) {
            if (n == 1)
                return 1;
            else
                return n + triangle(n - 1);
        }
};

int TriangleApp::theNumber = 0;

int main() {
    TriangleApp::main();
    return 0;
}