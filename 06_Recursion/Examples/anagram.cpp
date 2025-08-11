// anagram.cpp
// Построение списка анаграмм

#include <iostream>
using namespace std;

class AnagramApp {
    private:
        int size;
        int count;
        char arrChar[100];
    public:
        void main() {
            cout << "Enter a word: ";
            string input;
            cin >> input;
            size = input.length();
            count = 0;
            for (int j = 0; j < size; j++)
                arrChar[j] = input[j];
            doAnagram(size);
        }
        void doAnagram(int newSize) {
            if (newSize == 1)
                return;
            for (int j = 0; j < newSize; j++) {
                doAnagram(newSize - 1);
                if (newSize == 2)
                    displayWord();
                rotate(newSize);
            }
        }
        void rotate(int newSize) {
            int j;
            int position = size - newSize;
            char temp = arrChar[position];
            for (j = position + 1; j < size; j++)
                arrChar[j - 1] = arrChar[j];
            arrChar[j - 1] = temp;
        }
        void displayWord() {
            if (count < 99)
                cout << " ";
            if (count < 9)
                cout << " ";
            cout << ++count << " ";
            for (int j = 0; j < size; j++)
                cout << arrChar[j];
            cout << "  ";
            cout.flush();
            if (count % 6 == 0)
                cout << endl;
        }
};

int main() {
    AnagramApp aa;
    aa.main();
    return 0;
}