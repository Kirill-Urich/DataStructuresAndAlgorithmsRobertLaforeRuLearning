// project_6_1.cpp

#include <iostream>
using namespace std;

class MultApp {
    private:
        static int theAnswer;
    public:
        static void main() {
            int x, y;
            cout << "Enter x: ";
            cin >> x;
            cout << "Enter y: ";
            cin >> y;
            theAnswer = mult(x, y);
            cout << x << " multiplied by " << y << " is equal to " << theAnswer << endl;
        }
        static int mult(int x, int y) {
            if (y == 1)
                return x;
            else
                return x + mult(x, y - 1);
        }
};

int MultApp::theAnswer = 0;

int main() {
    MultApp::main();
    return 0;
}