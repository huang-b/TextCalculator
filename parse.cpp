#include<iostream>
#include<sstream>
#include<vector>

#include"TextCalculator.h"

using namespace std;

string parse(string& text) {
    stringstream parsedStream;
    vector<char> operatorStack;
    unsigned int i = 0;
    while(i < text.size()) {
        switch(text[i]) {
        case '+':
        case '-':
            if(operatorStack.empty() || '(' == operatorStack.back()) {
                operatorStack.push_back(text[i++]);
            } else {
                parsedStream << operatorStack.back() << ' ';
                operatorStack.pop_back();
            }
            break;
        case '*':
            if(!operatorStack.empty() && '*' == operatorStack.back()) {
                parsedStream << operatorStack.back() << ' ';
                operatorStack.pop_back();
            } else {
                operatorStack.push_back(text[i++]);
            }
            break;
        case '(':
            operatorStack.push_back(text[i++]);
            break;
        case ')':
            if(operatorStack.empty()) {
                throw string("Unmatch ')'");
            }
            if('(' == operatorStack.back()) {
                i++;
            } else {
                 parsedStream << operatorStack.back() << ' ';
            }
            operatorStack.pop_back();
            break;
        case ' ':
            i++;
            break;
        default:
             if(!isDigit(text[i])) {
                stringstream msg;
                msg << "Invalid Character: " << text[i] << " at " << i;
                throw msg.str();
            }
            do {
                parsedStream << text[i++];
            } while(i < text.size() && isDigit(text[i]));
            parsedStream << ' ';
        }
    }
    while(!operatorStack.empty()) {
        if('(' == operatorStack.back()) {
            throw string("Unmatch '('");
        }
        parsedStream << operatorStack.back() << ' ';
        operatorStack.pop_back();
    }
    string parsed = parsedStream.str();
    if(parsed.empty()) {
        throw "Empty Expression";
    }
    return parsed;
}
