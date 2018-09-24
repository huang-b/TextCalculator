#ifndef TEXT_CALCULATOR
#define TEXT_CALCULATOR

#include<string>

using namespace std;

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

string parse(string &text);

#endif