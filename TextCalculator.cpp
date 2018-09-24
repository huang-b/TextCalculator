#include<iostream>
#include<vector>
#include<sstream>

#include"TextCalculator.h"

using namespace std;

int parseExpression(vector<Symbol>& symbols, int &i) {
    int value = parseItem(symbols, i);
    while(true) {
        if(SymbolType::add == symbols[i].symbolType) {
            value += parseItem(symbols, ++i);
        } else if(SymbolType::sub == symbols[i].symbolType) {
            value -= parseItem(symbols, ++i);
        } else {
            break;
        }
    }
    return value;
}

int parseItem(vector<Symbol>& symbols, int &i) {
    int value = parseFactor(symbols, i);
    while(SymbolType::mul == symbols[i].symbolType) {
        value *= parseFactor(symbols, ++i);
    }
    return value;
}
int parseFactor(vector<Symbol>& symbols, int &i) {
    if(SymbolType::num == symbols[i].symbolType) {
        return symbols[i++].value;
    }
    if(SymbolType::left != symbols[i].symbolType) {
        throw string("Expect '('");
    }
    int value = parseExpression(symbols, ++i);
    if(SymbolType::right != symbols[i].symbolType) {
        throw string("Expect ')'");
    }
    ++i;
    return value;
}

void main() {
    // input
    string text;
    getline(cin, text);
    try {
        vector<Symbol> symbols;
        // parse
        parse(text, symbols);
        // calculate
        int i = 0;
        cout << parseExpression(symbols, i) << endl;
    } catch(string msg) {
        cout << msg << endl;
        return;
    }
}