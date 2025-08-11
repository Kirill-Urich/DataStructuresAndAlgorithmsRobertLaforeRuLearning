// project_6_2.cpp

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class BranchesApp {
    private:
        int length;
        int high;
        string* strTree;
    public:
        void main() {
            cout << "Enter length: ";
            cin >> length;
            high = static_cast<int>(log(length) / log(2)) + 1;
            strTree = new string[high];
            for (int i = 0; i < high; i++)
                strTree[i] = "";
            makeBranches(0, length, 0);
            display();
        }
        void makeBranches(int left, int right, int count) {
            if (count == high)
                return;
            string temp = "";
            int mid = (left + right) / 2;
            for (int i = left; i < right; i++) {
                if (i == mid)
                    temp += "X";
                else
                    temp += "-";
            }
            strTree[count] += temp;

            makeBranches(left, mid, count + 1);
            makeBranches(mid, right, count + 1);
        }
        void display() {
            for (int i = 0; i < high; i++)
                cout << strTree[i] << endl;
        }
};

int main() {
    BranchesApp ba;
    ba.main();
    return 0;
}