// project_5_6.cpp

#include <iostream>
using namespace std;

class Link {
    public:
        long data;
        Link* right;
        Link* under;
    public:
        Link(int n) : data(n) {
            right = nullptr;
            under = nullptr;
        }
        void displayLink() {
            cout << data << " ";
        }
};

class LinkedMatrix {
    private:
        int row;
        int col;
        Link* first;
    public:
        LinkedMatrix(int r, int c) : row(r), col(c) {
            if (row <= 0 || col <= 0) {
                first = nullptr;
                return;
            }

            first = new Link(0);
            Link** col_heads = new Link*[col];
            col_heads[0] = first;

            Link* current = first;
            for (int i = 1; i < col; i++) {
                Link* newLink = new Link(0);
                current->right = newLink;
                col_heads[i] = newLink;
                current = newLink;
            }

            for (int j = 1; j < row; j++) {
                Link* new_row_start = new Link(0);
                col_heads[0]->under = new_row_start;
                col_heads[0] = new_row_start;

                Link* current = new_row_start;
                for (int i = 1; i < col; i++) {
                    Link* newLink = new Link(0);
                    current->right = newLink;
                    col_heads[i]->under = newLink;
                    col_heads[i] = newLink;
                    current = newLink;
                }
            }
            delete[] col_heads;
        }
        ~LinkedMatrix() {
            Link* row_start = first;
            while (row_start != nullptr) {
                Link* col_current = row_start;
                Link* next_row = row_start->under;
                while (col_current != nullptr) {
                    Link* temp = col_current;
                    col_current = col_current->right;
                    delete temp;
                }
                row_start = next_row;
            }
        }
        void displayMatrix() {
            Link* current_row = first;
            while (current_row != nullptr) {
                Link* current_col = current_row;
                while (current_col != nullptr) {
                    current_col->displayLink();
                    current_col = current_col->right;
                }
                cout << endl;
                current_row = current_row->under;
            }
        }
        void insert(int r, int c, long num) {
            Link* current = first;
            for (int i = 0; i < r; i++)
                current = current->under;
            for (int j = 0; j < c; j++)
                current = current->right;
            
            current->data = num;
        }
};

class LinkedMatrixApp {
    public:
        static void main() {
            int col = 3;
            int row = 5;

            LinkedMatrix* newMatrix = new LinkedMatrix(row, col);
            newMatrix->displayMatrix();

            long n = 1;
            for (int i = 0; i < row; i++)
                for (int j = 0; j < col; j++) {
                    newMatrix->insert(i, j, i + j);
                    ++n;
                }

            cout << endl;
            newMatrix->displayMatrix();
        }
};

int main() {
    LinkedMatrixApp::main();
    return 0;
}