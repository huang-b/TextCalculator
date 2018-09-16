#include<iostream>
#include<sstream>
#include<vector>
#include"TextCalculator.h"

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
        case ' ':
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
    }
    parsed.emplace_back(SymbolType::eql);
}
