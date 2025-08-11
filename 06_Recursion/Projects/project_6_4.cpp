// project_6_4.cpp

#include <iostream>
using namespace std;

class BackPackApp {
    private:
        static int theAnswer;
        static int targetWeight;
    public:
        static void main() {
            int size = 5;
            targetWeight = 10;
            int array[size] = { 11, 8, 7, 6, 5 };
            if (knapsack(targetWeight, 0, array, size))
                cout << "Можно набрать сумму " << targetWeight << endl;
            else
                cout << "Нельзя набрать сумму " << targetWeight << endl;
        }
        static bool knapsack(int weight, int ind, int* arr, int size) {
            if (weight == 0) return true;
            if (ind >= size || weight < 0) return false;

            if (knapsack(weight - arr[ind], ind + 1, arr, size))
                return true;
            
            return knapsack(weight, ind + 1, arr, size);
        }
};

int BackPackApp::targetWeight = 0;

int main() {
    BackPackApp::main();
    return 0;
}