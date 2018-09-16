#include<iostream>
#include<vector>
#include<sstream>

#include"TextCalculator.h"

using namespace std;

void operate(vector<int>& operandStack, vector<SymbolType>& operatorStack) throw (string) {
    if(operandStack.size() < 2 || operatorStack.empty()) {
        throw string("Invalid Expression");
    }
    int b = operandStack.back();
    operandStack.pop_back();
    int a = operandStack.back();
    operandStack.pop_back();
    SymbolType symbolType = operatorStack.back();
    operatorStack.pop_back();
    if(SymbolType::add == symbolType) {
        operandStack.push_back(a + b);
    } else if(SymbolType::sub == symbolType) {
        operandStack.push_back(a - b);
    } else if(SymbolType::mul == symbolType) {
        operandStack.push_back(a * b);
    } else {
        throw string("Invalid Operation");
    }
}

int calculate(vector<Symbol>& parsed) throw (string) {
    vector<int> operandStack;
    vector<SymbolType> operatorStack;
    auto i = parsed.begin();
    while(true) {
        switch(i->symbolType) {
        case SymbolType::add:
        case SymbolType::sub:
            if(operatorStack.empty() || SymbolType::left == operatorStack.back()) {
                operatorStack.push_back(i->symbolType);
                i++;
            } else {
                operate(operandStack, operatorStack);
            }
            break;
        case SymbolType::mul:
            if(!operatorStack.empty() && SymbolType::mul == operatorStack.back()) {
                operate(operandStack, operatorStack);
            } else {
                operatorStack.push_back(i->symbolType);
                i++;
            }
            break;
        case SymbolType::left:
            operatorStack.push_back(i->symbolType);
            i++;
            break;
        case SymbolType::right:
            if(operatorStack.empty()) {
                throw string("Unmatch Bracket");
            } else if(SymbolType::left == operatorStack.back()) {
                operatorStack.pop_back();
                i++;
            } else {
                operate(operandStack, operatorStack);
            }
            break;
        case SymbolType::eql:
            if(operatorStack.empty()) {
                return operandStack.back();
            } else if(SymbolType::left == operatorStack.back()) {
                throw string("Invalid Expression.");
            } else {
                operate(operandStack, operatorStack);
            }
            break;
        case num:
            operandStack.push_back(i->value);
            i++;
            break;
        }
    }
}

int main() {
    // input
    string text;
    getline(cin, text);
    try {
        vector<Symbol> parsed;
        // parse
        parse(text, parsed);
        // calculate
        cout << calculate(parsed) << endl;
    } catch(string msg) {
        cout << msg << endl;
        return 0;
    }
}
