// postfix.cpp
// Разбор постфиксных арифметических выражений

#include <iostream>
using namespace std;

class StackX {
    private:
        int maxSize;
        int* stackArray;
        int top;
    public:
        StackX(int size) {
            maxSize = size;
            stackArray = new int[maxSize];
            top = -1;
        }
        void push(int j) {
            stackArray[++top] = j;
        }
        int pop() {
            return stackArray[top--];
        }
        int peek() {
            return stackArray[top];
        }
        bool isEmpty() {
            return top == -1;
        }
        bool isFull() {
            return top == maxSize - 1;
        }
        int size() {
            return top + 1;
        }
        int peekN(int n) {
            return stackArray[n];
        }
        void displayStack(string s) {
            cout << s;
            cout << "Stack (bottom-->top): ";
            for (int j = 0; j < size(); j++)
                cout << peekN(j) << " ";
            cout << endl;
        }
};

class ParsePost {
    private:
        StackX* theStack;
        string input;
    public:
        ParsePost(string s) {
            input = s;
        }
        int doParse() {
            theStack = new StackX(20);
            char ch;
            int num1, num2, interAns;
            for (size_t j = 0; j < input.length(); j++) {
                ch = input[j];
                string temp = ch + " ";
                theStack->displayStack(temp);
                if (ch >= '0' && ch <= '9')
                    theStack->push(ch - '0');
                else {
                    num2 = theStack->pop();
                    num1 = theStack->pop();
                    switch(ch) {
                        case '+':
                            interAns = num1 + num2;
                            break;
                        case '-':
                            interAns = num1 - num2;
                            break;
                        case '*':
                            interAns = num1 * num2;
                            break;
                        case '/':
                            interAns = num1 / num2;
                            break;
                        default:
                            interAns = 0;
                    }
                    theStack->push(interAns);
                }
            }
            interAns = theStack->pop();
            return interAns;
        }
};

class PostfixApp {
    public:
        static void main() {
            string input;
            int output;

            while (true) {
                cout << "Enter postfix: ";
                cout.flush();
                getline(cin, input);
                if (input == "")
                    break;
                ParsePost* aParser = new ParsePost(input);
                output = aParser->doParse();
                cout << "Evaluates to " << output << endl;
            }
        }
};

int main() {
    PostfixApp::main();
    return 0;
}
