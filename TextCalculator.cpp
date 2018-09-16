#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

enum SymbolType {
    add, sub, mul, left, right, eql, num
};

struct Symbol {
    SymbolType symbolType;
    int value;
    Symbol(SymbolType st): symbolType(st), value(0) {}
    Symbol(int v): symbolType(SymbolType::num), value(v) {}
};

inline bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

inline int parseInt(string &text, unsigned int &i) {
    int num = 0;
    do {
        num = num * 10 + text[i++] - '0';
    } while(i < text.size() && isDigit(text[i]));
    return num;
}

void parse(string& text, vector<Symbol>& parsed) {
    unsigned int i = 0;
    while(i < text.size()) {
        switch(text[i]) {
        case '+':
            parsed.emplace_back(SymbolType::add);
            i++;
            break;
        case '-':
            parsed.emplace_back(SymbolType::sub);
            i++;
            break;
        case '*':
            parsed.emplace_back(SymbolType::mul);
            i++;
            break;
        case '(':
            parsed.emplace_back(SymbolType::left);
            i++;
            break;
        case ')':
            parsed.emplace_back(SymbolType::right);
            i++;
            break;
        default:
            if(isDigit(text[i])) {
                parsed.emplace_back(parseInt(text, i));
            } else {
                stringstream msg;
                msg << "Invalid Character: " << text[i] << " at " << i;
                throw msg.str();
            }
        }
        if(parsed.empty()) {
            throw "Empty Expression";
        }
        parsed.emplace_back(SymbolType::eql);
    }
}

inline void operate(vector<int>& operandStack, vector<SymbolType>& operatorStack) {
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
        throw "Invalid Operation";
    }
}

int calculate(vector<Symbol>& parsed) {
    vector<int> operandStack;
    vector<SymbolType> operatorStack;
    bool end = false;
    auto i = parsed.begin();
    while(!end) {
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
                cout << "Unmatch Bracket" << endl;
                return;
            } else if(SymbolType::left == operatorStack.back()) {
                operatorStack.pop_back();
                i++;
                return;
            } else {
                operate(operandStack, operatorStack);
            }
            break;
        case SymbolType::eql:
            if(operatorStack.empty()) {
                end = true;
            } else if(SymbolType::left == operatorStack.back()) {
                cout << "Invalid Expression." << endl;
                return;
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

void main() {
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
        return;
    }
}