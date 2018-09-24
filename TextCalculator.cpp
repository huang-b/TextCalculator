#include<iostream>
#include<vector>
#include<sstream>
#include<map>

#include"TextCalculator.h"

using namespace std;

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mul(int a, int b) {
    return a * b;
}

inline void operate(vector<int>& operandStack, int (*op)(int, int)) {
    int b = operandStack.back();
    operandStack.pop_back();
    int a = operandStack.back();
    operandStack.pop_back();
    operandStack.push_back(op(a, b));
}

int calculate(string& reversePoland) {
    vector<int> operandStack;
    unsigned int i = 0; 
    while(i < reversePoland.size()) {
        switch(reversePoland[i]) {
        case '+':
            operate(operandStack, add);
            i++;
            break;
        case '-':
            operate(operandStack, sub);
            i++;
            break;
        case '*':
            operate(operandStack, mul);
            i++;
            break;
        case ' ':
            i++;
            break;
        default:
            operandStack.push_back(parseInt(reversePoland, i));
        }
    }
    return operandStack.back();
}

void main() {
    // init
    map<char, int> priorities;
    priorities['+'] = 0;
    priorities['-'] = 0;
    priorities['*'] = 1;
    // input
    string text;
    getline(cin, text);
    try {
        // parse
        string parsed = parse(text);
        // calculate
        cout << parsed << "= " << calculate(parsed) << endl;
    } catch(string msg) {
        cout << msg << endl;
        return;
    }
}