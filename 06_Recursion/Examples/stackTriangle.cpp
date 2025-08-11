// stackTriangle.cpp
// Вычисление треугольных чисел с заменой рекурсии стеком

#include <iostream>
using namespace std;

class Params {
    public:
        int n;
        int returnAddress;
    public:
        Params() : n(0), returnAddress(0) {}
        Params(int nn, int ra) : n(nn), returnAddress(ra) {}
};

class StackX {
    private:
        int maxSize;
        Params* stackArray;
        int top;
    public:
        StackX(int s) {
            maxSize = s;
            stackArray = new Params[maxSize];
            top = -1;
        }
        void push(Params p) {
            stackArray[++top] = p;
        }
        Params pop() {
            return stackArray[top--];
        }
        Params peek() {
            return stackArray[top];
        }
};

class StackTriangleApp {
    private:
        int theNumber;
        int theAnswer;
        StackX* theStack;
        int codePart;
        Params theseParams;
    public:
        void main() {
            cout << "Enter a number: ";
            cin >> theNumber;
            recTriangle();
            cout << "Triangle = " << theAnswer << endl;
        }
        void recTriangle() {
            theStack = new StackX(10'000);
            codePart = 1;
            while (step() == false) {}
        }
        bool step() {
            switch(codePart) {
                case 1:
                    theseParams = Params(theNumber, 6);
                    theStack->push(theseParams);
                    codePart = 2;
                    break;
                case 2:
                    theseParams = theStack->peek();
                    if (theseParams.n == 1) {
                        theAnswer = 1;
                        codePart = 5;
                    }
                    else
                        codePart = 3;
                    break;
                case 3: 
                    {
                    Params newParams(theseParams.n - 1, 4);
                    theStack->push(newParams);
                    codePart = 2;
                    }
                    break;
                case 4: 
                    theseParams = theStack->peek();
                    theAnswer += theseParams.n;
                    codePart = 5;
                    break;
                case 5:
                    theseParams = theStack->peek();
                    codePart = theseParams.returnAddress;
                    theStack->pop();
                    break;
                case 6:
                    delete theStack;
                    theStack = nullptr;
                    return true;
            }
            return false;
        }
};

int main() {
    StackTriangleApp sta;
    sta.main();
    return 0;
}