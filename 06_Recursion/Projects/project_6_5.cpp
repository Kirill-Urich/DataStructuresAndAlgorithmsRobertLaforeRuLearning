// project_6_5.cpp

#include <iostream>
using namespace std;

class TeamsApp {
    private:
        string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    public:
        void main() {
            int groupCount;
            int teamCount;
            cout << "Введите размеры группы: ";  cin >> groupCount;
            cout << "Введите размеры команды: "; cin >> teamCount;
            showTeam(groupCount, teamCount, 0, "");
        }
        void showTeam(int gc, int tc, int count, string word) {
            if (gc == 0 || tc == 0 || tc > gc)
                return;
            if (tc == 1)
                cout << word + alphabet[count] << " ";
            showTeam(gc - 1, tc - 1, count + 1, word + alphabet[count]);
            showTeam(gc - 1, tc, count + 1, word);
        }
};

int main() {
    TeamsApp ta;
    ta.main();
    return 0;
}