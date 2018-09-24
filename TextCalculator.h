#include<string>
using namespace std;
#ifndef TEXT_CALCULATOR
#define TEXT_CALCULATOR
enum SymbolType {
    add, sub, mul, left, right, eql, num
};

struct Symbol {
    SymbolType symbolType;
    int value;
    Symbol(SymbolType st): symbolType(st), value(0) {}
    Symbol(int v): symbolType(SymbolType::num), value(v) {}
};

void parse(string &text, vector<Symbol>& parsed);
int parseExpression(vector<Symbol>& symbols, int &i);
int parseItem(vector<Symbol>& symbols, int &i);
int parseFactor(vector<Symbol>& symbols, int &i);


#endif