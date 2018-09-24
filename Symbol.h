#ifndef SYMBOL
#define SYMBOL

#include"Operator.h"

class Symbol {
private:
    SymbolType symbolType;
    int value;
public:
    Symbol(SymbolType st): symbolType(st), value(0) {}
    Symbol(int v): symbolType(SymbolType::num), value(v) {}
    bool isNum();
    Operator* toOperator();
    int toNum();
};
#endif