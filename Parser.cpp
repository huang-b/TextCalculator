#include<sstream>
#include<string>

#include"Parser.h"

bool Parser::hasNext() {
    return index <= text.size();
}

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

Symbol Parser::next() {
    if(index == text.size()) {
        index++;
        return Symbol(SymbolType::eql);
    }
    while(text[index] == ' ') {
        index++;
    }
    switch(text[index]) {
    case '+':
        index++;
        return Symbol(SymbolType::add);
    case '-':
        index++;
        return Symbol(SymbolType::sub);
    case '*':
        index++;
        return Symbol(SymbolType::mul);
    case '(':
        index++;
        return Symbol(SymbolType::left);
    case ')':
        index++;
        return Symbol(SymbolType::right);
    default:
        if(isDigit(text[index])) {
            return Symbol(parseInt(text, index));
        } else {
            stringstream msg;
            msg << "Invalid Character: " << text[index] << " at " << index;
            throw msg.str();
        }
    }
}
