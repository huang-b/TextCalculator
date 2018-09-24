#ifndef OPERATOR
#define OPERATOR

#include<vector>

#include"SymbolType.h"

using namespace std;

class Operator {
private:
    SymbolType symbolType;
public:
    Operator(SymbolType st): symbolType(st) {}
    SymbolType getSymbolType() {
        return symbolType;
    }
    virtual void operate(vector<int>& operandStack) = 0;
};

class AddOperator: public Operator {
public:
    AddOperator(): Operator(SymbolType::add) {}
    void operate(vector<int>& operandStack);
};

class SubOperator: public Operator {
public:
    SubOperator(): Operator(SymbolType::sub) {}
    void operate(vector<int>& operandStack);
};

class MulOperator: public Operator {
public:
    MulOperator(): Operator(SymbolType::mul) {}
    void operate(vector<int>& operandStack);
};

class QuietOperator: public Operator {
public:
    QuietOperator(SymbolType st): Operator(st) {}
    void operate(vector<int>& operandStack);
};

#endif
