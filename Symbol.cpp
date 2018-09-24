#include"Symbol.h"

bool Symbol::isNum() {
        return SymbolType::num == symbolType;
}

Operator* Symbol::toOperator() {
    if(isNum()) {
        throw string("Invalid Operator");
    }
    switch(symbolType) {
    case SymbolType::add:
        return new AddOperator();
    case SymbolType::sub:
        return new SubOperator();
    case SymbolType::mul:
        return new MulOperator();
    default:
        return new QuietOperator(symbolType);
    }
}

int Symbol::toNum() {
    if(!isNum()) {
        throw string("Invalid Number");
    }
    return value;
}
