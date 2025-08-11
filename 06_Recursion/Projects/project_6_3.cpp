// project_6_3.cpp

#include <iostream>
using namespace std;

class PowerApp {
    private:
        static int theAnswer;
    public:
        static void main() {
            int x, y;
            cout << "Enter x: ";
            cin >> x;
            cout << "Enter y: ";
            cin >> y;
            theAnswer = power(x, y);
            cout << x << " powered by " << y << " is equal to " << theAnswer << endl;
        }
        static int power(int x, int y) {
            if (y == 0) return 1;
            if (y == 1) return x;

            int half = power(x, y / 2);
            if (y % 2 == 0)
                return half * half;
            else
                return x * half * half;
        }
};

int PowerApp::theAnswer = 0;

int main() {
    PowerApp::main();
    return 0;
}