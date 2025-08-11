// towers.cpp
// Решение головоломки "Ханойская башня"

#include <iostream>
using namespace std;

class TowersApp {
    private:
        static int nDisks;
    public:
        static void main() {
            doTowers(nDisks, 'A', 'B', 'C');
        }
        static void doTowers(int topN, char from, char inter, char to) {
            if (topN == 1)
                cout << "Disk 1 from " << from << " to " << to << endl;
            else {
                doTowers(topN - 1, from, to, inter);
                cout << "Disk " << topN << " from " << from << " to " << to << endl;
                doTowers(topN - 1, inter, from, to);
            }
        }
};

int TowersApp::nDisks = 3;

int main() {
    TowersApp::main();
    return 0;
}